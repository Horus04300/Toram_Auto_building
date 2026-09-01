use serde::Serialize;
use serde_json::Value;
use std::fs::{self, OpenOptions};
use std::io::Write;
use std::path::{Path, PathBuf};
use std::time::UNIX_EPOCH;

pub const SETTING_FORMAT: &str = "toram-auto-build-document";
pub const SETTING_SCHEMA_VERSION: u64 = 2;
const LEGACY_SETTING_SCHEMA_VERSION: u64 = 1;
const APP_STORAGE_DIRECTORY: &str = "ToramOnlineAutoBuildCalculator";

#[derive(Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SettingFile {
    name: String,
    last_modified: u64,
}

/// Native filesystem implementation for the R6 saved-build document only.
pub struct SettingsRepository;
impl SettingsRepository {
    pub fn directory() -> Result<String, String> {
        Ok(Self::ensure_directory()?.to_string_lossy().into_owned())
    }
    fn storage_directory() -> Result<PathBuf, String> {
        let local = std::env::var_os("LOCALAPPDATA")
            .filter(|value| !value.is_empty())
            .ok_or_else(|| "LOCALAPPDATA 환경 변수를 찾을 수 없습니다.".to_string())?;
        Ok(PathBuf::from(local).join(APP_STORAGE_DIRECTORY))
    }
    fn ensure_directory() -> Result<PathBuf, String> {
        let directory = Self::storage_directory()?;
        fs::create_dir_all(&directory)
            .map_err(|error| format!("세팅 저장 폴더를 만들 수 없습니다: {error}"))?;
        if !directory.is_dir() {
            return Err("세팅 저장 경로가 폴더가 아닙니다.".to_string());
        }
        Ok(directory)
    }
    fn stem(name: &str) -> Result<&str, String> {
        let stem = name.trim();
        if stem.is_empty() {
            return Err("세팅 이름을 입력하세요.".to_string());
        }
        if stem.chars().count() > 80 {
            return Err("세팅 이름은 80자 이하여야 합니다.".to_string());
        }
        if stem == "." || stem == ".." || stem.ends_with('.') || stem.ends_with(' ') {
            return Err("세팅 이름의 끝에는 점이나 공백을 사용할 수 없습니다.".to_string());
        }
        if stem
            .chars()
            .any(|character| character.is_control() || r#"\/:*?\"<>|"#.contains(character))
        {
            return Err("세팅 이름에 Windows 금지 문자를 사용할 수 없습니다.".to_string());
        }
        let base = stem.split('.').next().unwrap_or(stem).to_ascii_uppercase();
        let reserved = matches!(base.as_str(), "CON" | "PRN" | "AUX" | "NUL")
            || base.strip_prefix("COM").is_some_and(|number| {
                matches!(number, "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
            })
            || base.strip_prefix("LPT").is_some_and(|number| {
                matches!(number, "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
            });
        if reserved {
            return Err("Windows 예약 장치 이름은 사용할 수 없습니다.".to_string());
        }
        Ok(stem)
    }
    fn new_path(directory: &Path, name: &str) -> Result<PathBuf, String> {
        Ok(directory.join(format!("{}.json", Self::stem(name)?)))
    }
    fn existing_path(directory: &Path, file_name: &str) -> Result<PathBuf, String> {
        let name = file_name.trim();
        let stem = name
            .strip_suffix(".json")
            .ok_or_else(|| "JSON 세팅 파일만 사용할 수 있습니다.".to_string())?;
        Self::stem(stem)?;
        Ok(directory.join(format!("{stem}.json")))
    }
    fn validate_with_schema(content: &str, allow_legacy_schema: bool) -> Result<(), String> {
        let value: Value = serde_json::from_str(content)
            .map_err(|error| format!("세팅 JSON을 해석할 수 없습니다: {error}"))?;
        let root = value
            .as_object()
            .ok_or_else(|| "세팅 JSON의 최상위 값은 객체여야 합니다.".to_string())?;
        let schema_version = root.get("schemaVersion").and_then(Value::as_u64);
        if root.get("format").and_then(Value::as_str) != Some(SETTING_FORMAT)
            || (schema_version != Some(SETTING_SCHEMA_VERSION)
                && (!allow_legacy_schema || schema_version != Some(LEGACY_SETTING_SCHEMA_VERSION)))
        {
            return Err("이 계산기의 세팅 JSON 형식이 아닙니다.".to_string());
        }
        if root.get("documentType").and_then(Value::as_str) != Some("saved-build") {
            return Err("저장 가능한 빌드 문서가 아닙니다.".to_string());
        }
        if root.get("name").and_then(Value::as_str).is_none()
            || root.get("createdAt").and_then(Value::as_str).is_none()
            || root.get("updatedAt").and_then(Value::as_str).is_none()
        {
            return Err("빌드 문서의 메타데이터 형식이 올바르지 않습니다.".to_string());
        }
        let build = root
            .get("build")
            .and_then(Value::as_object)
            .ok_or_else(|| "세팅 JSON에 build 객체가 없습니다.".to_string())?;
        if !build.contains_key("character")
            || !build.contains_key("equipment")
            || !build.contains_key("skillLevels")
            || !build.contains_key("activeBuffs")
            || !build.contains_key("externalOptions")
            || !build.contains_key("combo")
        {
            return Err("빌드 문서의 필수 항목이 없습니다.".to_string());
        }
        root.get("scenario")
            .and_then(Value::as_object)
            .and_then(|scenario| scenario.get("target"))
            .and_then(Value::as_object)
            .ok_or_else(|| "세팅 JSON에 scenario.target 객체가 없습니다.".to_string())?;
        Ok(())
    }
    pub fn validate(content: &str) -> Result<(), String> {
        Self::validate_with_schema(content, false)
    }
    fn validate_for_load(content: &str) -> Result<(), String> {
        Self::validate_with_schema(content, true)
    }
    fn reject_link(path: &Path) -> Result<(), String> {
        let metadata = fs::symlink_metadata(path)
            .map_err(|error| format!("세팅 파일 정보를 읽을 수 없습니다: {error}"))?;
        if metadata.file_type().is_symlink() || !metadata.is_file() {
            return Err("일반 JSON 세팅 파일만 사용할 수 있습니다.".to_string());
        }
        Ok(())
    }
    pub fn list() -> Result<Vec<SettingFile>, String> {
        let directory = Self::ensure_directory()?;
        let mut files = Vec::new();
        for entry in fs::read_dir(&directory)
            .map_err(|error| format!("세팅 파일 목록을 읽을 수 없습니다: {error}"))?
        {
            let entry =
                entry.map_err(|error| format!("세팅 파일 항목을 읽을 수 없습니다: {error}"))?;
            let path = entry.path();
            let metadata = fs::symlink_metadata(&path)
                .map_err(|error| format!("세팅 파일 정보를 읽을 수 없습니다: {error}"))?;
            if metadata.file_type().is_symlink() || !metadata.is_file() {
                continue;
            }
            let name = entry.file_name().to_string_lossy().into_owned();
            if !name.to_ascii_lowercase().ends_with(".json") {
                continue;
            }
            let Ok(content) = fs::read_to_string(path) else {
                continue;
            };
            if Self::validate_for_load(&content).is_err() {
                continue;
            }
            let last_modified = metadata
                .modified()
                .ok()
                .and_then(|value| value.duration_since(UNIX_EPOCH).ok())
                .map(|duration| duration.as_millis().min(u128::from(u64::MAX)) as u64)
                .unwrap_or(0);
            files.push(SettingFile {
                name,
                last_modified,
            });
        }
        files.sort_by(|left, right| {
            right
                .last_modified
                .cmp(&left.last_modified)
                .then_with(|| left.name.cmp(&right.name))
        });
        Ok(files)
    }
    pub fn save(name: String, content: String) -> Result<(), String> {
        Self::validate(&content)?;
        let path = Self::new_path(&Self::ensure_directory()?, &name)?;
        let mut file = OpenOptions::new()
            .write(true)
            .create_new(true)
            .open(&path)
            .map_err(|error| {
                if error.kind() == std::io::ErrorKind::AlreadyExists {
                    "같은 이름의 세팅이 이미 있습니다. 덮어쓰기를 사용하세요.".to_string()
                } else {
                    format!("세팅 파일을 만들 수 없습니다: {error}")
                }
            })?;
        file.write_all(content.as_bytes())
            .map_err(|error| format!("세팅 파일을 저장할 수 없습니다: {error}"))
    }
    pub fn load(name: String) -> Result<String, String> {
        let path = Self::existing_path(&Self::ensure_directory()?, &name)?;
        Self::reject_link(&path)?;
        let content = fs::read_to_string(&path)
            .map_err(|error| format!("세팅 파일을 읽을 수 없습니다: {error}"))?;
        Self::validate_for_load(&content)?;
        Ok(content)
    }
    pub fn overwrite(name: String, content: String) -> Result<(), String> {
        Self::validate(&content)?;
        let path = Self::existing_path(&Self::ensure_directory()?, &name)?;
        Self::reject_link(&path)?;
        let mut file = OpenOptions::new()
            .write(true)
            .truncate(true)
            .open(&path)
            .map_err(|error| format!("덮어쓸 세팅 파일을 열 수 없습니다: {error}"))?;
        file.write_all(content.as_bytes())
            .map_err(|error| format!("세팅 파일을 덮어쓸 수 없습니다: {error}"))
    }
    pub fn delete(name: String) -> Result<(), String> {
        let path = Self::existing_path(&Self::ensure_directory()?, &name)?;
        Self::reject_link(&path)?;
        fs::remove_file(&path).map_err(|error| format!("세팅 파일을 삭제할 수 없습니다: {error}"))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn valid_document() -> String {
        serde_json::json!({
            "format": SETTING_FORMAT, "schemaVersion": SETTING_SCHEMA_VERSION,
            "documentType": "saved-build", "name": "test",
            "createdAt": "2026-09-01T00:00:00.000Z", "updatedAt": "2026-09-01T00:00:00.000Z",
            "build": {"character":{},"equipment":{},"skillLevels":{},"activeBuffs":{},"externalOptions":[],"combo":[]},
            "scenario": {"target":{}}
        }).to_string()
    }

    #[test]
    fn accepts_valid_names_and_rejects_path_or_windows_names() {
        assert_eq!(SettingsRepository::stem("내 세팅").unwrap(), "내 세팅");
        for invalid in [
            "",
            "..",
            "a/b",
            r"a\b",
            "a:b",
            "CON",
            "com1.txt",
            "trailing.",
        ] {
            assert!(
                SettingsRepository::stem(invalid).is_err(),
                "{invalid} must be rejected"
            );
        }
    }

    #[test]
    fn requires_json_extension_for_existing_files() {
        let directory = Path::new("C:/example");
        assert!(SettingsRepository::existing_path(directory, "valid.json").is_ok());
        assert!(SettingsRepository::existing_path(directory, "valid.txt").is_err());
        assert!(SettingsRepository::existing_path(directory, "../escape.json").is_err());
    }

    #[test]
    fn validates_saved_build_contract() {
        assert!(SettingsRepository::validate(&valid_document()).is_ok());
        assert!(SettingsRepository::validate("{}").is_err());
        assert!(SettingsRepository::validate("not json").is_err());
    }
}
