#!/usr/bin/env bash
set -euo pipefail
umask 077
base=/srv/compose/toram
data=/srv/data/toram/db
backups=/srv/backups/toram
proxy=/srv/compose/proxy
[[ $EUID == 0 ]] || { echo 'Use sudo for the Toram deployment command.' >&2; exit 1; }
[[ $# == 1 && ( $1 == --check || $1 =~ ^[a-f0-9]{64}$ ) ]] || { echo 'Expected --check or a SHA-256 release ID.' >&2; exit 1; }
exec 9>"$base/deploy.lock"
flock -n 9 || { echo 'Another Toram deployment is running.' >&2; exit 1; }
docker info >/dev/null
docker network inspect proxy >/dev/null
[[ -s $base/.env && -s $base/compose.yaml ]]
[[ -s /srv/data/toram/cloudflared/token && -s /srv/data/toram/cloudflared/origin-ca.pem ]] || { echo 'Apply the Tunnel setup first.' >&2; exit 1; }
openssl x509 -in /srv/data/toram/tls/cert.pem -checkend 2592000 -noout
if [[ $1 == --check ]]; then
    echo 'Toram deployment access, Docker, network, environment and TLS: ready'
    exit 0
fi
release=$1
archive=$base/incoming/$release.tar.gz
[[ -f $archive && ! -L $archive ]]
work=$(mktemp -d "$base/releases/.verify.XXXXXXXX")
trap 'rm -rf -- "$work"' EXIT
cp -- "$archive" "$work/upload.tar.gz"
mkdir "$work/files"
python3 /usr/local/lib/toram-deploy/verify-release.py "$work/upload.tar.gz" "$release" "$work/files"
if [[ ! -d $base/releases/$release ]]; then mv -- "$work/files" "$base/releases/$release"; fi
export TORAM_RELEASE=$release
compose=(docker compose --project-directory "$base" -f "$base/compose.yaml")
"${compose[@]}" config --quiet
"${compose[@]}" build calculator
previous=
if [[ -f $base/current ]]; then previous=$(cat "$base/current"); [[ $previous =~ ^[a-f0-9]{64}$ ]]; fi
stamp=$(date -u +%Y%m%dT%H%M%SZ)-${release:0:12}
if [[ -f $data/accounts.sqlite ]]; then
    python3 - "$data/accounts.sqlite" "$backups/$stamp.sqlite" <<'PY'
import sqlite3,sys
with sqlite3.connect('file:'+sys.argv[1]+'?mode=ro',uri=True) as source, sqlite3.connect(sys.argv[2]) as target:
    source.backup(target)
    if target.execute('PRAGMA integrity_check').fetchone()[0] != 'ok':
        raise SystemExit('Database backup integrity check failed')
print('Consistent SQLite backup saved')
PY
fi
cp -- "$proxy/Caddyfile" "$work/Caddyfile.previous"
proxy_changed=false
rollback() {
    status=$?
    trap - ERR
    echo 'Deployment failed; restoring previous code/proxy. Database is preserved.' >&2
    if [[ $proxy_changed == true ]]; then
        cat "$work/Caddyfile.previous" > "$proxy/Caddyfile"
        docker compose -f "$proxy/compose.yaml" exec -T caddy caddy reload --config /etc/caddy/Caddyfile --adapter caddyfile || true
    fi
    if [[ -n $previous ]]; then
        TORAM_RELEASE=$previous "${compose[@]}" up -d --no-build --wait --wait-timeout 120 calculator tunnel || echo 'Rollback failed; inspect Toram container logs.' >&2
    else
        "${compose[@]}" stop calculator || true
    fi
    exit "$status"
}
trap rollback ERR
"${compose[@]}" up -d --no-build --wait --wait-timeout 120 calculator tunnel
python3 - "$proxy/Caddyfile" /usr/local/lib/toram-deploy/Caddyfile.toram "$work/Caddyfile" <<'PY'
import re,sys
text=open(sys.argv[1]).read()
site=open(sys.argv[2]).read().rstrip()
if site not in text:
    pattern=r'(?m)^toram\.nimp\.dev \{\s*\n\s*tls /etc/caddy/certs/origin\.pem /etc/caddy/certs/origin\.key\s*\n\}'
    text,count=re.subn(pattern,lambda _:site,text)
    if count != 1: raise SystemExit('Toram Caddy block differs from the inspected configuration; refusing to overwrite it.')
open(sys.argv[3],'w').write(text)
PY
proxy_id=$(docker compose -f "$proxy/compose.yaml" ps -q caddy)
[[ -n $proxy_id ]]
docker cp "$work/Caddyfile" "$proxy_id:/tmp/toram-deploy.Caddyfile"
docker exec "$proxy_id" caddy validate --config /tmp/toram-deploy.Caddyfile --adapter caddyfile
if ! cmp -s "$work/Caddyfile" "$proxy/Caddyfile"; then
    cp -- "$work/Caddyfile.previous" "$backups/$stamp.Caddyfile"
    proxy_changed=true
    # Preserve the inode of Caddy's file bind mount.
    cat "$work/Caddyfile" > "$proxy/Caddyfile"
fi
docker exec "$proxy_id" caddy reload --config /etc/caddy/Caddyfile --adapter caddyfile
curl --fail --silent --show-error --retry 3 --retry-delay 2 --max-time 15 https://toram.nimp.dev/api/session > "$work/session.json"
python3 - "$work/session.json" <<'PY'
import json,sys
if json.load(open(sys.argv[1])).get('configured') is not True:
    raise SystemExit('Public OAuth configuration check failed')
PY
printf '%s\n' "$release" > "$base/current.next"
mv -- "$base/current.next" "$base/current"
trap - ERR
rm -f -- "$archive"
echo "Toram deployed over HTTPS 443: $release"
