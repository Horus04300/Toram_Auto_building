use serde::Serialize;
use std::sync::{
    atomic::{AtomicBool, Ordering},
    Mutex,
};
use std::time::{Duration, Instant};
use tauri_plugin_updater::{Update, UpdaterExt};

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct UpdateInfo {
    pub current_version: String,
    pub version: String,
    pub notes: Option<String>,
    pub published_at: Option<String>,
}

impl From<&Update> for UpdateInfo {
    fn from(update: &Update) -> Self {
        Self {
            current_version: update.current_version.clone(),
            version: update.version.clone(),
            notes: update.body.clone(),
            published_at: update
                .raw_json
                .get("pub_date")
                .and_then(|v| v.as_str())
                .map(str::to_owned),
        }
    }
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct UpdateFailure {
    code: &'static str,
    message: &'static str,
}

fn failure(code: &'static str, message: &'static str) -> UpdateFailure {
    UpdateFailure { code, message }
}

#[derive(Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct UpdateProgress {
    downloaded: u64,
    total: Option<u64>,
}

#[derive(Default)]
struct Pending {
    update: Option<Update>,
    verified_bytes: Option<Vec<u8>>,
}

#[derive(Default)]
pub struct UpdateService {
    busy: AtomicBool,
    pending: Mutex<Pending>,
}

struct Operation<'a>(&'a AtomicBool);
impl Drop for Operation<'_> {
    fn drop(&mut self) {
        self.0.store(false, Ordering::Release);
    }
}

impl UpdateService {
    fn begin(&self) -> Result<Operation<'_>, UpdateFailure> {
        self.busy
            .compare_exchange(false, true, Ordering::AcqRel, Ordering::Acquire)
            .map_err(|_| failure("BUSY", "업데이트 작업이 이미 진행 중입니다."))?;
        Ok(Operation(&self.busy))
    }

    fn pending(&self) -> Result<std::sync::MutexGuard<'_, Pending>, UpdateFailure> {
        self.pending.lock().map_err(|_| {
            failure(
                "STATE",
                "업데이트 상태를 읽지 못했습니다. 앱을 다시 실행해 주세요.",
            )
        })
    }

    pub async fn check(&self, app: tauri::AppHandle) -> Result<Option<UpdateInfo>, UpdateFailure> {
        let _operation = self.begin()?;
        *self.pending()? = Pending::default();
        let updater = app
            .updater_builder()
            .timeout(Duration::from_secs(15))
            .version_comparator(|current, release| {
                release.version.pre.is_empty() && release.version > current
            })
            .build()
            .map_err(|_| failure("CONFIG", "업데이트 설정을 읽지 못했습니다."))?;
        let update = updater.check().await.map_err(|_| {
            failure(
                "CHECK",
                "업데이트를 확인하지 못했습니다. 네트워크 연결을 확인하고 다시 시도해 주세요.",
            )
        })?;
        let info = update.as_ref().map(UpdateInfo::from);
        self.pending()?.update = update;
        Ok(info)
    }

    pub async fn download(
        &self,
        version: String,
        progress: tauri::ipc::Channel<UpdateProgress>,
    ) -> Result<(), UpdateFailure> {
        let _operation = self.begin()?;
        let mut update = {
            let mut pending = self.pending()?;
            pending.verified_bytes = None;
            pending
                .update
                .as_ref()
                .filter(|u| u.version == version)
                .cloned()
                .ok_or_else(|| failure("STALE", "업데이트를 다시 확인해 주세요."))?
        };
        update.timeout = Some(Duration::from_secs(600));
        let mut downloaded = 0u64;
        let mut last_sent = Instant::now();
        let bytes = update.download(|chunk, total| {
            downloaded += chunk as u64;
            if last_sent.elapsed() >= Duration::from_millis(100) || total == Some(downloaded) {
                let _ = progress.send(UpdateProgress { downloaded, total });
                last_sent = Instant::now();
            }
        }, || {}).await.map_err(|_| failure("DOWNLOAD_OR_SIGNATURE", "다운로드 또는 서명 검증에 실패했습니다. 설치하지 않았습니다. 다시 시도해 주세요."))?;
        let _ = progress.send(UpdateProgress {
            downloaded,
            total: Some(downloaded),
        });
        // Only the plugin's signature-verified bytes may cross the install boundary.
        self.pending()?.verified_bytes = Some(bytes);
        Ok(())
    }

    pub fn install(&self, version: String) -> Result<(), UpdateFailure> {
        let _operation = self.begin()?;
        let (update, bytes) = {
            let mut pending = self.pending()?;
            let update = pending
                .update
                .as_ref()
                .filter(|u| u.version == version)
                .cloned()
                .ok_or_else(|| failure("STALE", "업데이트를 다시 확인해 주세요."))?;
            let bytes = pending.verified_bytes.take().ok_or_else(|| {
                failure(
                    "NOT_VERIFIED",
                    "서명 검증을 마친 다운로드가 없습니다. 다시 시도해 주세요.",
                )
            })?;
            (update, bytes)
        };
        // On Windows the plugin launches NSIS, exits, and asks NSIS to restart the app.
        update.install(bytes).map_err(|_| {
            failure(
                "INSTALL",
                "설치 프로그램을 실행하지 못했습니다. 다시 시도해 주세요.",
            )
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn install_without_checked_and_verified_update_is_rejected() {
        let service = UpdateService::default();
        assert_eq!(service.install("99.0.0".into()).unwrap_err().code, "STALE");
        assert!(
            service.begin().is_ok(),
            "failed operation releases the busy guard"
        );
    }
    #[test]
    fn concurrent_operations_are_rejected_and_guard_releases() {
        let service = UpdateService::default();
        let operation = service.begin().unwrap();
        assert!(matches!(
            service.begin(),
            Err(UpdateFailure { code: "BUSY", .. })
        ));
        drop(operation);
        assert!(service.begin().is_ok());
    }
    #[test]
    fn ipc_metadata_and_errors_use_application_fields() {
        let info = UpdateInfo {
            current_version: "0.6.3".into(),
            version: "0.6.4".into(),
            notes: None,
            published_at: None,
        };
        let dto = serde_json::to_value(info).unwrap();
        assert_eq!(dto["currentVersion"], "0.6.3");
        assert!(dto["notes"].is_null());
        assert!(serde_json::to_value(failure("CHECK", "연결 실패"))
            .unwrap()
            .get("message")
            .is_some());
    }
}
