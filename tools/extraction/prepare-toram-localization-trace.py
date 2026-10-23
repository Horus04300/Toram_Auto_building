"""Prepare selected coroutine functions from saved metadata/module files only.

Reuses the existing token/pointer mapper and Ghidra script. Does not access a
process, load target code, change game files, or make network requests.
"""

import argparse
import importlib.util
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
TARGETS = {
    5500: ("<Start>d__28", "InitGameSystem_Start_StateMachine"),
    5513: ("<Start>d__12", "StageLoginDownloader_Start_StateMachine"),
    5514: ("<StartDownload>d__13", "StageLoginDownloader_StartDownload_StateMachine"),
    5520: ("<initResourceDownload>d__14", "StageLoginDownloader_initResourceDownload_StateMachine"),
    5518: ("<initLocalizeData>d__17", "StageLoginDownloader_initLocalizeData_StateMachine"),
    5892: ("<Initialize>d__31", "ResourceManager_Initialize_StateMachine"),
    5779: ("<Initialize>d__43", "AssetBundleManager_Initialize_StateMachine"),
    5780: ("<LoadCacheAssetBundle>d__61", "AssetBundleManager_LoadCacheAssetBundle61_StateMachine"),
    5781: ("<LoadCacheAssetBundle>d__62", "AssetBundleManager_LoadCacheAssetBundle62_StateMachine"),
    5782: ("<LoadCacheAssetBundle>d__63", "AssetBundleManager_LoadCacheAssetBundle63_StateMachine"),
    5783: ("<LoadCacheAssetBundle>d__64", "AssetBundleManager_LoadCacheAssetBundle64_StateMachine"),
    5806: ("<DownloadCacheAssetBundle>d__34", "DownloadManager_DownloadCacheAssetBundle_StateMachine"),
}


def selected_type(index, name):
    if index not in TARGETS:
        return None
    expected, label = TARGETS[index]
    if name != expected:
        raise ValueError(f"Metadata type changed: {index}: {name!r}")
    return label


def prepare(runtime, output):
    spec = importlib.util.spec_from_file_location("native_mapper", Path(__file__).with_name("map-il2cpp-methods.py"))
    mapper = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mapper)
    metadata_path = runtime / "current-source/global-metadata.dat"
    metadata = mapper.metadata_module.Metadata(metadata_path.read_bytes())
    mapper.SELECTED_TYPES |= {"AssetBundleManager", "LocalizeManager", "DownloadManager"}
    for index, (name, _) in TARGETS.items():
        selected_type(index, metadata.full_name(metadata.types[index]))
        mapper.SELECTED_TYPES.add(name)
    output.mkdir(parents=True, exist_ok=True)
    destination = output / "native-map.json"
    mapper.extract(metadata_path, runtime / "snapshot-1/GameAssembly.mapped.bin", runtime / "snapshot-1/capture.json", destination)
    mapping = json.loads(destination.read_text(encoding="utf-8"))
    mapping["methods"] = [method for method in mapping["methods"]
                          if not method["class"].startswith("<")
                          or metadata.methods[method["method_definition_index"]][1] in TARGETS]
    for method in mapping["methods"]:
        index = metadata.methods[method["method_definition_index"]][1]
        method["declaring_type_definition_index"] = index
        label = selected_type(index, method["class"])
        if label:
            method["original_metadata_class"] = method["class"]
            method["class"] = label
    selected = [m for m in mapping["methods"] if m["declaring_type_definition_index"] in TARGETS and m["name"] == "MoveNext"]
    mapper.require(len(selected) == len(TARGETS) and all(m["status"] == "mapped" for m in selected), "Incomplete selected coroutine mapping")
    mapping["selected_coroutines"] = selected
    destination.write_text(json.dumps(mapping, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    java = (ROOT / "tools/extraction/ghidra/TraceToramItemFunctions.java").read_text(encoding="utf-8")
    start = java.index('Set<String> names = Set.of(')
    end = java.index(';', start) + 1
    java = java[:start] + 'Set<String> names = Set.of("MoveNext");' + java[end:]
    java = java.replace("TraceToramItemFunctions", "TraceToramLocalization")
    (output / "TraceToramLocalization.java").write_text(java, encoding="utf-8")
    print(json.dumps({"selected": [{"class": m["class"], "token": m["token"], "rva": m["rva"]} for m in selected]}))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--runtime", type=Path, default=ROOT / "build/tmp/toram-item-extraction/code-trace/runtime")
    parser.add_argument("--output", type=Path, default=ROOT / "build/tmp/toram-item-extraction/code-trace/localization-trace")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        assert selected_type(5520, "<initResourceDownload>d__14").startswith("StageLoginDownloader_")
        assert selected_type(1, "other") is None
        try:
            selected_type(5520, "wrong")
        except ValueError:
            pass
        else:
            raise AssertionError("Changed metadata accepted")
        print("localization trace preparation self-test PASS")
    else:
        prepare(args.runtime.resolve(), args.output.resolve())


if __name__ == "__main__":
    main()
