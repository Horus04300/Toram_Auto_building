"""Shared immutable snapshot storage and capture lifecycle; no domain parsing."""
import hashlib
import json
from pathlib import Path
import runpy
import uuid
HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
MODULES = {}

def module(name):
    if name not in MODULES:
        MODULES[name] = runpy.run_path(str(HERE / name))
    return MODULES[name]

def require(value, message):
    if not value:
        raise ValueError(message)

def digest(data):
    return hashlib.sha256(data).hexdigest()

def load(path):
    return json.loads(path.read_text(encoding='utf-8'))

def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('x', encoding='utf-8', newline='\n') as stream:
        json.dump(value, stream, ensure_ascii=False, indent=2, allow_nan=False)
        stream.write('\n')

def atomic_json(path, value):
    temporary = path.with_name(path.name + '.' + uuid.uuid4().hex + '.tmp')
    try:
        write_json(temporary, value)
        temporary.replace(path)
    finally:
        temporary.unlink(missing_ok=True)

def checked_child(root, relative):
    if root == ROOT and relative.startswith('assets/source-data/'):
        relative = 'data/sources/' + relative[len('assets/source-data/'):]
    require(not Path(relative).is_absolute(), 'Absolute artifact path')
    target = (root / relative).resolve()
    require(target.is_relative_to(root.resolve()) and target != root.resolve(), 'Artifact escapes its store')
    return target

def installation_identity(install, contract):
    observed, reasons = ({}, [])
    for relative, expected in contract['installation'].items():
        path = install / relative
        observed[relative] = digest(path.read_bytes()) if path.is_file() else None
        if observed[relative] != expected:
            reasons.append(f'Installation requires code review: {relative}')
    return (observed, reasons)

def manifest_source(offline, application, destination):
    localization = module('extract-toram-localizations.py')
    url = f"{localization['PUBLIC_BASE']}{application}/{localization['MANIFEST_NAME']}"
    if offline:
        filename = localization['MANIFEST_NAME'] if application == 'releaseA' else f'RevisionInfoBinary.{application}.bytes'
        path = offline / 'manifest.bytes' if (offline / 'manifest.bytes').is_file() else offline / filename
        data = path.read_bytes()
        if destination:
            destination.write_bytes(data)
        return (data, {'url': url, 'sha256': digest(data), 'input': str(path.resolve()), 'mode': 'offline'})
    record = localization['get_public'](url, destination)
    return (destination.read_bytes(), record)

def resource_changes(before, after):
    old = {r['name']: r['decodedSha256'] for r in before}
    new = {r['name']: r['decodedSha256'] for r in after}
    return [{'name': name, 'beforeSha256': old.get(name), 'afterSha256': new.get(name)} for name in sorted(old.keys() | new.keys()) if old.get(name) != new.get(name)]

def read_snapshot(store, pointer):
    path = checked_child(store, pointer['snapshot'])
    require(digest((path / 'report.json').read_bytes()) == pointer['reportSha256'], 'Stored report changed')
    report = load(path / 'report.json')
    for name, expected in report['outputHashes'].items():
        require(digest(checked_child(path, name).read_bytes()) == expected, f'Stored snapshot changed: {name}')
    return (path, report)

class SnapshotCapture:

    def __init__(self, store, install):
        self.store = store.resolve()
        require(not self.store.is_relative_to(install.resolve()), 'Store must not be inside the game installation')
        self.lock = self.store / '.pipeline.lock'
        self.manifest_path = self.store / ('.manifest-' + uuid.uuid4().hex + '.bytes')
        self.path = None
        self.latest_pointer = self.latest_path = self.latest_report = None

    def __enter__(self):
        self.store.mkdir(parents=True, exist_ok=True)
        with self.lock.open('x', encoding='ascii') as stream:
            stream.write(uuid.uuid4().hex)
        return self

    def __exit__(self, kind, error, traceback):
        try:
            if error is not None and self.path is not None:
                write_json(self.path / 'failure.json', {'status': 'failed', 'error': str(error), 'latestUnchanged': True})
        finally:
            self.manifest_path.unlink(missing_ok=True)
            self.lock.unlink()

    def load_state(self, identity):
        latest = self.store / 'latest.json'
        self.latest_pointer = load(latest) if latest.is_file() else None
        if self.latest_pointer:
            self.latest_path, self.latest_report = read_snapshot(self.store, self.latest_pointer)
        observed = self.store / 'observed.json'
        pointers = [self.latest_pointer, load(observed) if observed.is_file() else None]
        for pointer in pointers:
            if not pointer:
                continue
            report = self.latest_report if pointer == self.latest_pointer else read_snapshot(self.store, pointer)[1]
            if report['identity'] == identity and (report['status'] != 'ready' or pointer == self.latest_pointer):
                return (pointer, report)
        return None

    def begin(self, label):
        self.path = checked_child(self.store, 'snapshots/' + label + '-' + uuid.uuid4().hex)
        self.path.mkdir(parents=True)
        return self.path

    # Publish latest last; a ready but unpublished observation cannot be a cache hit.
    def publish(self, report):
        report['outputHashes'] = {p.relative_to(self.path).as_posix(): digest(p.read_bytes()) for p in self.path.rglob('*') if p.is_file()}
        write_json(self.path / 'report.json', report)
        pointer = {'snapshot': self.path.relative_to(self.store).as_posix(), 'reportSha256': digest((self.path / 'report.json').read_bytes())}
        atomic_json(self.store / 'observed.json', pointer)
        if report['status'] == 'ready':
            atomic_json(self.store / 'latest.json', pointer)
        self.path = None
