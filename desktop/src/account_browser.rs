fn login_url(value: &str) -> Result<tauri::Url, String> {
    let url = tauri::Url::parse(value).map_err(|_| "올바르지 않은 로그인 주소입니다.")?;
    if url.scheme() != "https"
        || url.host_str().is_none()
        || !url.username().is_empty()
        || url.password().is_some()
        || url.path() != "/api/auth/google"
        || url.fragment().is_some()
        || url.query_pairs().count() != 1
        || !url.query_pairs().all(|(key, value)| {
            key == "desktop"
                && value.len() == 43
                && value
                    .bytes()
                    .all(|byte| byte.is_ascii_alphanumeric() || byte == b'-' || byte == b'_')
        })
    {
        return Err("허용되지 않은 로그인 주소입니다.".into());
    }
    Ok(url)
}

pub fn open(value: &str) -> Result<(), String> {
    let url = login_url(value)?;
    #[cfg(target_os = "windows")]
    {
        use std::os::windows::process::CommandExt;
        std::process::Command::new("rundll32.exe")
            .args(["url.dll,FileProtocolHandler", url.as_str()])
            .creation_flags(0x08000000)
            .spawn()
            .map_err(|_| "기본 브라우저를 열지 못했습니다.".to_string())?;
        Ok(())
    }
    #[cfg(not(target_os = "windows"))]
    {
        let _ = url;
        Err("현재 계정 로그인은 Windows 앱에서 지원합니다.".into())
    }
}

#[cfg(test)]
mod tests {
    use super::login_url;

    #[test]
    fn accepts_only_https_account_login_with_a_pairing_id() {
        let id = "a".repeat(43);
        assert!(login_url(&format!(
            "https://calculator.example/api/auth/google?desktop={id}"
        ))
        .is_ok());
        for value in [
            format!("http://calculator.example/api/auth/google?desktop={id}"),
            format!("https://calculator.example/api/auth/google?desktop={id}&redirect=bad"),
            format!("https://user:pass@calculator.example/api/auth/google?desktop={id}"),
            format!("https://calculator.example/other?desktop={id}"),
            "file:///C:/Windows/System32/cmd.exe".into(),
            "https://calculator.example/api/auth/google?desktop=x%22%20bad".into(),
        ] {
            assert!(login_url(&value).is_err());
        }
    }
}
