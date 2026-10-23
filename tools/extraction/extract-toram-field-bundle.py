"""Read reviewed outer Unity TextAsset wrappers and MapInfo.mobDb references.

This module does not download assets or access the game process. UnityPy is
imported only when inspecting an actual retained bundle.
"""
import hashlib
import importlib.util
from pathlib import Path

_spec = importlib.util.spec_from_file_location(
    "toram_field_asset_reader", Path(__file__).with_name("extract-toram-item-assets.py"))
_assets = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_assets)


def _digest(data):
    return hashlib.sha256(data).hexdigest()


def _local_pointer(value, objects, expected_type=None):
    if value["m_FileID"] != 0:
        raise ValueError("External field component reference requires review")
    if value["m_PathID"] == 0:
        return None
    obj = objects.get(value["m_PathID"])
    if obj is None or expected_type and obj.type.name != expected_type:
        raise ValueError("Missing field component or reference type changed")
    return obj


def inspect_inner_bundle(data):
    import UnityPy
    if not data.startswith(b"UnityFS\0"):
        raise ValueError("Decoded field wrapper is not UnityFS")
    env = UnityPy.load(data)
    objects = {obj.path_id: obj for obj in env.objects}
    if len(objects) != len(env.objects):
        raise ValueError("Ambiguous object IDs across inner field files")
    scripts = {obj.path_id: obj.parse_as_object().m_Name for obj in env.objects
               if obj.type.name == "MonoScript"}
    game_objects = {obj.path_id: obj.parse_as_dict() for obj in env.objects
                    if obj.type.name == "GameObject"}
    parents = {}
    for obj in env.objects:
        if obj.type.name != "Transform":
            continue
        tree = obj.parse_as_dict()
        father = _local_pointer(tree["m_Father"], objects, "Transform")
        parent_game_id = father.parse_as_dict()["m_GameObject"]["m_PathID"] if father else None
        parents[tree["m_GameObject"]["m_PathID"]] = parent_game_id
    map_infos, pop_mobs, event_areas, components = [], [], [], {}
    for obj in env.objects:
        if obj.type.name != "MonoBehaviour":
            continue
        tree = obj.parse_as_dict()
        script = scripts.get(tree["m_Script"]["m_PathID"])
        component_game_id = tree["m_GameObject"]["m_PathID"]
        components.setdefault(component_game_id, []).append(
            {"pathId": obj.path_id, "script": script, "tree": tree})
        if script not in ("MapInfo", "MobPopPoint", "EventArea"):
            continue
        if tree["m_Script"]["m_FileID"] != 0:
            raise ValueError("External MapInfo script requires review")
        game_object = _local_pointer(tree["m_GameObject"], objects, "GameObject")
        game_id = game_object.path_id if game_object else None
        record = {"pathId": obj.path_id, "gameObjectPathId": game_id,
                  "gameObjectName": game_objects[game_id]["m_Name"] if game_id else None,
                  "tree": tree}
        if script == "MobPopPoint":
            pop_mobs.append(record)
            continue
        if script == "EventArea":
            event_areas.append(record)
            continue
        if "mobDb" not in tree:
            raise ValueError("MapInfo.mobDb disappeared")
        referenced = _local_pointer(tree["mobDb"], objects, "TextAsset")
        if referenced:
            asset = referenced.parse_as_object()
            raw = asset.m_Script.encode("utf-8", "surrogateescape")
            record["mobDb"] = {"pathId": referenced.path_id, "name": asset.m_Name,
                               "sha256": _digest(raw), "bytes": raw}
        else:
            record["mobDb"] = None
        script_reference = tree.get("fieldScriptBytes")
        script_asset = _local_pointer(script_reference, objects, "TextAsset") if script_reference else None
        if script_asset:
            value = script_asset.parse_as_object()
            script_raw = value.m_Script.encode("utf-8", "surrogateescape")
            record["fieldScriptAsset"] = {"pathId": script_asset.path_id, "name": value.m_Name,
                                           "sha256": _digest(script_raw), "bytes": len(script_raw), "data": script_raw}
        else:
            record["fieldScriptAsset"] = None
        map_infos.append(record)
    for record in [*pop_mobs, *event_areas]:
        chain, current, seen = [], record["gameObjectPathId"], set()
        while current is not None:
            if current in seen:
                raise ValueError("Transform parent cycle")
            seen.add(current)
            chain.append(current)
            current = parents.get(current)
        record["ancestorGameObjectPathIds"] = chain
        record["ancestorGameObjectNames"] = [game_objects[value]["m_Name"] for value in chain]
    for record in map_infos:
        record["popMobs"] = [pop for pop in pop_mobs
                             if record["gameObjectPathId"] in pop["ancestorGameObjectPathIds"]]
        record["eventAreas"] = [event for event in event_areas
                                if record["gameObjectPathId"] in event["ancestorGameObjectPathIds"]]
        record["childGameObjects"] = [
            {"pathId": game_id, "name": game_objects[game_id]["m_Name"],
             "components": components.get(game_id, [])}
            for game_id, parent_id in parents.items() if parent_id == record["gameObjectPathId"]]
    return {"decodedSha256": _digest(data), "mapInfos": map_infos,
            "noMapInfo": not map_infos}


def inspect_bundle(data, cache_key):
    import UnityPy
    if not data.startswith(b"UnityFS\0"):
        raise ValueError("Field source is not UnityFS")
    env = UnityPy.load(data)
    assets = [obj for obj in env.objects if obj.type.name == "TextAsset"]
    if len(assets) != 1:
        raise ValueError("Expected one outer field wrapper TextAsset")
    obj = assets[0]
    value = obj.parse_as_object()
    raw = value.m_Script.encode("utf-8", "surrogateescape")
    key = int(cache_key, 16) if isinstance(cache_key, str) else cache_key
    decoded = _assets.decode(raw, key)
    return {"sourceSha256": _digest(data),
            "wrapper": {"name": value.m_Name, "pathId": obj.path_id,
                        "rawSha256": _digest(raw), "bytes": len(raw)},
            **inspect_inner_bundle(decoded)}
