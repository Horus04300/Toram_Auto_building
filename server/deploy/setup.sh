#!/usr/bin/env bash
set -euo pipefail
umask 077
[[ $EUID == 0 && ${SUDO_USER:-} =~ ^[a-z_][a-z0-9_-]*$ ]] || { echo 'Run this script through sudo as the SSH user.' >&2; exit 1; }
source_dir=$(cd -- "$(dirname -- "$0")" && pwd)
base=/srv/compose/toram
account=$SUDO_USER
for program in docker openssl python3 flock curl visudo; do command -v "$program" >/dev/null; done
docker compose version
docker network inspect proxy >/dev/null
[[ -f /srv/compose/proxy/compose.yaml && -f /srv/compose/proxy/Caddyfile ]]
install -d -m 755 /usr/local/lib/toram-deploy
install -m 755 "$source_dir/activate.sh" /usr/local/sbin/toram-deploy
install -m 644 "$source_dir/verify-release.py" "$source_dir/Caddyfile.toram" /usr/local/lib/toram-deploy/
install -d -m 750 -o root -g "$(id -gn "$account")" "$base"
install -d -m 750 -o root -g root "$base/releases" /srv/data/toram
install -d -m 700 -o "$account" -g "$(id -gn "$account")" "$base/incoming"
install -d -m 700 -o 1000 -g 1000 /srv/data/toram/db
install -d -m 750 -o root -g 1000 /srv/data/toram/tls
install -d -m 700 /srv/backups/toram
if [[ ! -f $base/.env ]]; then
    install -m 600 "$source_dir/oauth.env" "$base/.env"
fi
python3 - "$base/.env" <<'PY'
import re,sys
values = dict(line.rstrip('\n').split('=',1) for line in open(sys.argv[1]) if '=' in line and not line.startswith('#'))
for key in ['GOOGLE_CLIENT_ID','GOOGLE_CLIENT_SECRET']:
    if not re.fullmatch(r'[-A-Za-z0-9._:]+',values.get(key,'')):
        raise SystemExit('Configure '+key+' in /srv/compose/toram/.env')
PY
tls=/srv/data/toram/tls
if [[ ! -f $tls/cert.pem || ! -f $tls/key.pem ]]; then
    [[ ! -e $tls/cert.pem && ! -e $tls/key.pem ]] || { echo 'Incomplete TLS pair; inspect it before retrying.' >&2; exit 1; }
    openssl req -x509 -newkey rsa:3072 -sha256 -nodes -days 3650 \
        -subj /CN=toram.nimp.dev -addext subjectAltName=DNS:toram.nimp.dev \
        -keyout "$tls/key.pem" -out "$tls/cert.pem" 2>/dev/null
fi
chmod 640 "$tls/key.pem"
chmod 644 "$tls/cert.pem"
chown root:1000 "$tls/key.pem" "$tls/cert.pem"
openssl x509 -in "$tls/cert.pem" -checkend 2592000 -noout
install -m 644 "$tls/cert.pem" /srv/data/proxy/certs/toram-upstream.pem
connector=/srv/data/toram/cloudflared
install -d -m 750 -o root -g 65532 "$connector"
if [[ ! -s $connector/token ]]; then
    echo 'Paste only the Cloudflare Tunnel token below. Input is hidden; do not paste the Docker command.'
    IFS= read -r -s -p 'Tunnel token: ' tunnel_token
    printf '\n'
    [[ ${#tunnel_token} -ge 80 && ${#tunnel_token} -le 8192 && $tunnel_token != *[[:space:]]* ]] || { echo 'Invalid token input.' >&2; exit 1; }
    printf '%s\n' "$tunnel_token" > "$connector/token"
    unset tunnel_token
fi
chown root:65532 "$connector/token"
chmod 640 "$connector/token"
trust=$(mktemp -d)
trap 'rm -rf -- "$trust"' EXIT
for kind in ecc rsa; do
    curl --fail --silent --show-error --retry 3 --proto '=https' \
        "https://developers.cloudflare.com/ssl/static/origin_ca_${kind}_root.pem" -o "$trust/$kind.pem"
    openssl x509 -in "$trust/$kind.pem" -checkend 2592000 -noout
done
cat "$trust/ecc.pem" "$trust/rsa.pem" > "$connector/origin-ca.pem"
chmod 644 "$connector/origin-ca.pem"
rm -rf -- "$trust"
install -m 600 "$source_dir/compose.yaml" "$base/compose.yaml"
sudoers=$(mktemp)
trap 'rm -f -- "$sudoers"' EXIT
printf '%s ALL=(root) NOPASSWD: /usr/local/sbin/toram-deploy\n' "$account" > "$sudoers"
visudo -cf "$sudoers"
install -m 440 "$sudoers" /etc/sudoers.d/toram-deploy
rm -f -- "$source_dir/oauth.env"
/usr/local/sbin/toram-deploy --check
TORAM_RELEASE=$(cat "$base/current" 2>/dev/null || printf setup) \
    docker compose --project-directory "$base" -f "$base/compose.yaml" up -d --no-build --wait --wait-timeout 120 tunnel
echo 'Tunnel connector is ready. In Cloudflare, publish toram.nimp.dev with service URL https://caddy:443, Origin Server Name toram.nimp.dev and TLS verification enabled.'
echo 'Then run npm run web:deploy on your development computer.'
