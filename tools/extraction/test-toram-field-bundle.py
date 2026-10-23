"""Small trust-boundary tests; no UnityPy installation or game assets required."""
import runpy
import sys
from pathlib import Path
from types import SimpleNamespace
import unittest
from unittest.mock import patch

reader = runpy.run_path(str(Path(__file__).with_name("extract-toram-field-bundle.py")))


def pointer(path_id):
    return {"m_FileID": 0, "m_PathID": path_id}


def obj(path_id, kind, value):
    return SimpleNamespace(path_id=path_id, type=SimpleNamespace(name=kind),
                           parse_as_dict=lambda: value,
                           parse_as_object=lambda: SimpleNamespace(**value))


def fixture():
    return [obj(1, "MonoScript", {"m_Name": "MapInfo"}),
            obj(2, "MonoScript", {"m_Name": "MobPopPoint"}),
            obj(10, "GameObject", {"m_Name": "mapInfo_23000"}),
            obj(11, "GameObject", {"m_Name": "pop_1"}),
            obj(20, "Transform", {"m_GameObject": pointer(10), "m_Father": pointer(0)}),
            obj(21, "Transform", {"m_GameObject": pointer(11), "m_Father": pointer(20)}),
            obj(30, "MonoBehaviour", {"m_GameObject": pointer(10), "m_Script": pointer(1),
                                      "mobDb": pointer(40), "typeRoomObj": 7,
                                      "fieldScriptBytes": pointer(41)}),
            obj(31, "MonoBehaviour", {"m_GameObject": pointer(11), "m_Script": pointer(2),
                                      "monsterDatabaseID": 1}),
            obj(40, "TextAsset", {"m_Name": "mob_23000", "m_Script": "\udcffabc"}),
            obj(41, "TextAsset", {"m_Name": "sc_23000", "m_Script": "script"}),
            obj(3, "MonoScript", {"m_Name": "EventArea"}),
            obj(32, "MonoBehaviour", {"m_GameObject": pointer(11), "m_Script": pointer(3),
                                      "eventType": 1, "scriptId": 3})]


class FieldBundleTests(unittest.TestCase):
    def inspect(self, objects):
        fake = SimpleNamespace(load=lambda _: SimpleNamespace(objects=objects))
        with patch.dict(sys.modules, {"UnityPy": fake}):
            return reader["inspect_inner_bundle"](b"UnityFS\0fixture")

    def test_referenced_bytes_and_descendant_pop_are_preserved(self):
        value = self.inspect(fixture())
        self.assertFalse(value["noMapInfo"])
        info = value["mapInfos"][0]
        self.assertEqual(info["mobDb"]["bytes"], b"\xffabc")
        self.assertEqual(info["tree"]["typeRoomObj"], 7)
        self.assertEqual(info["gameObjectName"], "mapInfo_23000")
        self.assertEqual(info["popMobs"][0]["tree"]["monsterDatabaseID"], 1)
        self.assertEqual(info["popMobs"][0]["ancestorGameObjectNames"],
                         ["pop_1", "mapInfo_23000"])
        self.assertEqual(info["childGameObjects"][0]["name"], "pop_1")
        self.assertEqual(info["childGameObjects"][0]["components"][0]["script"], "MobPopPoint")
        self.assertEqual(info["fieldScriptAsset"]["name"], "sc_23000")
        self.assertEqual(info["fieldScriptAsset"]["bytes"], 6)
        self.assertEqual(info["eventAreas"][0]["tree"]["scriptId"], 3)

    def test_absent_mapinfo_is_explicit(self):
        value = self.inspect([])
        self.assertTrue(value["noMapInfo"])
        self.assertEqual(value["mapInfos"], [])

    def test_null_database_is_preserved(self):
        objects = fixture()
        objects[6].parse_as_dict()["mobDb"] = pointer(0)
        self.assertIsNone(self.inspect(objects)["mapInfos"][0]["mobDb"])

    def test_broken_or_external_database_reference_is_rejected(self):
        for reference in [pointer(999), {"m_FileID": 1, "m_PathID": 40}, pointer(10)]:
            with self.subTest(reference=reference):
                objects = fixture()
                objects[6].parse_as_dict()["mobDb"] = reference
                with self.assertRaises(ValueError):
                    self.inspect(objects)

    def test_parent_cycle_and_duplicate_ids_are_rejected(self):
        objects = fixture()
        objects[4].parse_as_dict()["m_Father"] = pointer(21)
        with self.assertRaisesRegex(ValueError, "cycle"):
            self.inspect(objects)
        with self.assertRaisesRegex(ValueError, "Ambiguous"):
            self.inspect([*fixture(), fixture()[0]])


if __name__ == "__main__":
    unittest.main()
