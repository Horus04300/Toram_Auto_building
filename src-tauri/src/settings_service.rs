use crate::settings_repository::{SettingFile, SettingsRepository};

/// Application service: commands use this API instead of filesystem details.
pub struct SettingsService;
impl SettingsService {
    pub fn directory() -> Result<String, String> {
        SettingsRepository::directory()
    }
    pub fn list() -> Result<Vec<SettingFile>, String> {
        SettingsRepository::list()
    }
    pub fn save(name: String, content: String) -> Result<(), String> {
        SettingsRepository::save(name, content)
    }
    pub fn load(name: String) -> Result<String, String> {
        SettingsRepository::load(name)
    }
    pub fn overwrite(name: String, content: String) -> Result<(), String> {
        SettingsRepository::overwrite(name, content)
    }
    pub fn delete(name: String) -> Result<(), String> {
        SettingsRepository::delete(name)
    }
}
