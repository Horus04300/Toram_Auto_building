//! Release gate: verify the actual installer against the application's public key.
use base64::{engine::general_purpose::STANDARD, Engine};
use minisign_verify::{PublicKey, Signature};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 4 {
        return Err("usage: verify_updater_artifact CONFIG INSTALLER SIGNATURE".into());
    }
    let config: serde_json::Value = serde_json::from_slice(&std::fs::read(&args[1])?)?;
    let key = config["plugins"]["updater"]["pubkey"]
        .as_str()
        .ok_or("missing public key")?;
    let public_key = PublicKey::decode(&String::from_utf8(STANDARD.decode(key.trim())?)?)?;
    let encoded_signature = std::fs::read_to_string(&args[3])?;
    let signature = Signature::decode(&String::from_utf8(
        STANDARD.decode(encoded_signature.trim())?,
    )?)?;
    public_key.verify(&std::fs::read(&args[2])?, &signature, true)?;
    println!("Updater artifact signature: PASS");
    Ok(())
}
