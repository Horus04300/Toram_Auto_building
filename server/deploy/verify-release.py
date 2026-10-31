"""Validate the complete upload before extracting any deployable code as root."""
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import sys
import tarfile


def verify_release(archive, release_id, destination):
    if not re.fullmatch(r"[a-f0-9]{64}", release_id):
        raise ValueError("Invalid release ID")
    with tarfile.open(archive, "r:gz") as bundle:
        members = bundle.getmembers()
        if len(members) > 5000 or sum(item.size for item in members) > 150 * 1024 * 1024:
            raise ValueError("Release exceeds size limit")
        files = {}
        for member in members:
            path = PurePosixPath(member.name)
            if path.is_absolute() or ".." in path.parts or "\\" in member.name:
                raise ValueError("Unsafe archive path")
            if not (member.isfile() or member.isdir()):
                raise ValueError("Archive links and special files are forbidden")
            if member.isfile():
                name = str(path)
                if name in files:
                    raise ValueError("Duplicate archive file")
                files[name] = member
        if "release.json" not in files or files["release.json"].size > 1024 * 1024:
            raise ValueError("Release manifest is missing or too large")
        manifest_bytes = bundle.extractfile(files["release.json"]).read()
        manifest = json.loads(manifest_bytes)
        hashes = manifest.get("files", {})
        digest = hashlib.sha256(json.dumps(hashes, ensure_ascii=False, separators=(",", ":")).encode()).hexdigest()
        if manifest.get("schema") != 1 or manifest.get("id") != release_id or digest != release_id:
            raise ValueError("Release identity mismatch")
        if set(files) != set(hashes) | {"release.json"}:
            raise ValueError("Archive/manifest file mismatch")
        required = {"package.json", ".dockerignore", "server/Dockerfile", "server/account-server.mjs", "build/web/index.html", "build/web/assets/wasm/crysta_bg.wasm"}
        if not required <= set(hashes):
            raise ValueError("Required runtime files are missing")
        for name, expected in hashes.items():
            if not (name in required or name.startswith(("server/", "web/src/", "build/web/"))):
                raise ValueError("Unexpected deployment file")
            if name.endswith(".env") or "/data/accounts.sqlite" in name:
                raise ValueError("Private data cannot be deployed")
            if hashlib.sha256(bundle.extractfile(files[name]).read()).hexdigest() != expected:
                raise ValueError("File checksum mismatch: " + name)
        # All paths, types, membership and bytes passed before the first write.
        for name, member in files.items():
            output = Path(destination) / name
            output.parent.mkdir(parents=True, exist_ok=True)
            with output.open("xb") as target:
                target.write(bundle.extractfile(member).read())
    return len(files)


if __name__ == "__main__":
    count = verify_release(*sys.argv[1:])
    print(f"Verified release: {count} files")
