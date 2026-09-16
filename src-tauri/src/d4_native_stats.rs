//! Dense known coordinates with a sparse fallback and unchanged JSON map contract.
use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;
const KEYS: [&str; 36] = [
    "AGI",
    "AGIP",
    "AMPR",
    "AMPRP",
    "ASPD",
    "ASPD_P",
    "ATK",
    "ATKP",
    "CDMG",
    "CDMGP",
    "CRIT",
    "CRITP",
    "DAMAGE_P",
    "DEX",
    "DEXP",
    "ELEM_P",
    "INT",
    "INTP",
    "LRW",
    "MAG_PIERCE",
    "MATK",
    "MATKP",
    "MAXHP",
    "MAXHPP",
    "MAXMP",
    "PHYS_PIERCE",
    "SRW",
    "STABILITY",
    "STR",
    "STRP",
    "UNSHEATHE",
    "UNSHEATHEP",
    "VIT",
    "VITP",
    "WATK",
    "WATKP",
];
#[inline]
fn index(key: &str) -> Option<usize> {
    match key {
        "AGI" => Some(0),
        "AGIP" => Some(1),
        "AMPR" => Some(2),
        "AMPRP" => Some(3),
        "ASPD" => Some(4),
        "ASPD_P" => Some(5),
        "ATK" => Some(6),
        "ATKP" => Some(7),
        "CDMG" => Some(8),
        "CDMGP" => Some(9),
        "CRIT" => Some(10),
        "CRITP" => Some(11),
        "DAMAGE_P" => Some(12),
        "DEX" => Some(13),
        "DEXP" => Some(14),
        "ELEM_P" => Some(15),
        "INT" => Some(16),
        "INTP" => Some(17),
        "LRW" => Some(18),
        "MAG_PIERCE" => Some(19),
        "MATK" => Some(20),
        "MATKP" => Some(21),
        "MAXHP" => Some(22),
        "MAXHPP" => Some(23),
        "MAXMP" => Some(24),
        "PHYS_PIERCE" => Some(25),
        "SRW" => Some(26),
        "STABILITY" => Some(27),
        "STR" => Some(28),
        "STRP" => Some(29),
        "UNSHEATHE" => Some(30),
        "UNSHEATHEP" => Some(31),
        "VIT" => Some(32),
        "VITP" => Some(33),
        "WATK" => Some(34),
        "WATKP" => Some(35),
        _ => None,
    }
}
#[derive(Clone, Debug, PartialEq)]
pub struct NativeStats {
    values: [f64; 36],
    present: u64,
    extra: BTreeMap<String, f64>,
}
impl Default for NativeStats {
    fn default() -> Self {
        Self::new()
    }
}
impl NativeStats {
    pub fn new() -> Self {
        Self {
            values: [0.0; 36],
            present: 0,
            extra: BTreeMap::new(),
        }
    }
    #[inline]
    pub fn get(&self, key: &str) -> Option<&f64> {
        match index(key) {
            Some(i) if self.present & (1 << i) != 0 => Some(&self.values[i]),
            Some(_) => None,
            None => self.extra.get(key),
        }
    }
    pub fn insert(&mut self, key: String, value: f64) {
        if let Some(i) = index(&key) {
            self.values[i] = value;
            self.present |= 1 << i;
        } else {
            self.extra.insert(key, value);
        }
    }
    pub fn add_assign(&mut self, other: &Self) {
        // Update only present coordinates: absent +0 must not change existing -0.
        let mut mask = other.present;
        while mask != 0 {
            let i = mask.trailing_zeros() as usize;
            self.values[i] += other.values[i];
            mask &= mask - 1;
        }
        self.present |= other.present;
        for (key, value) in &other.extra {
            if let Some(total) = self.extra.get_mut(key) {
                *total += value;
            } else {
                self.extra.insert(key.clone(), 0.0 + value);
            }
        }
    }
    pub fn iter(&self) -> impl Iterator<Item = (&str, &f64)> {
        let mut entries = KEYS
            .iter()
            .enumerate()
            .filter(|(i, _)| self.present & (1 << i) != 0)
            .map(|(i, key)| (*key, &self.values[i]))
            .chain(self.extra.iter().map(|(key, value)| (key.as_str(), value)))
            .collect::<Vec<_>>();
        entries.sort_unstable_by(|a, b| a.0.cmp(b.0));
        entries.into_iter()
    }
    pub fn keys(&self) -> impl Iterator<Item = &str> {
        self.iter().map(|(key, _)| key)
    }
    #[cfg(test)]
    pub fn is_empty(&self) -> bool {
        self.present == 0 && self.extra.is_empty()
    }
}
impl FromIterator<(String, f64)> for NativeStats {
    fn from_iter<T: IntoIterator<Item = (String, f64)>>(items: T) -> Self {
        let mut result = Self::new();
        for (key, value) in items {
            result.insert(key, value);
        }
        result
    }
}
impl<const N: usize> From<[(String, f64); N]> for NativeStats {
    fn from(items: [(String, f64); N]) -> Self {
        items.into_iter().collect()
    }
}
impl std::ops::Index<&str> for NativeStats {
    type Output = f64;
    fn index(&self, key: &str) -> &f64 {
        self.get(key).expect("stat key must exist")
    }
}
impl Serialize for NativeStats {
    fn serialize<S: serde::Serializer>(&self, serializer: S) -> Result<S::Ok, S::Error> {
        serializer.collect_map(self.iter())
    }
}
impl<'de> Deserialize<'de> for NativeStats {
    fn deserialize<D: serde::Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        BTreeMap::<String, f64>::deserialize(deserializer).map(|map| map.into_iter().collect())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn dense_merge_matches_sparse_map_and_roundtrip() {
        let mut seed = 7_u64;
        let mut random = || {
            seed = seed.wrapping_mul(6364136223846793005).wrapping_add(1);
            seed
        };
        for _ in 0..1000 {
            let mut expected = BTreeMap::<String, f64>::new();
            let mut actual = NativeStats::new();
            for _ in 0..4 {
                let mut source = BTreeMap::new();
                for key in KEYS.into_iter().chain(["UNKNOWN", "ZZZ"]) {
                    let next = random();
                    if next % 3 == 0 {
                        continue;
                    }
                    let value = [-0.0, 1e16, -1e16, -0.125, 1.0, 0.0][(next % 6) as usize];
                    source.insert(key.to_owned(), value);
                }
                let dense: NativeStats = source.clone().into_iter().collect();
                for (key, value) in &source {
                    assert_eq!(dense.get(key).unwrap().to_bits(), value.to_bits());
                    *expected.entry(key.clone()).or_insert(0.0) += value;
                }
                actual.add_assign(&dense);
                assert_eq!(
                    actual.keys().collect::<Vec<_>>(),
                    expected.keys().map(String::as_str).collect::<Vec<_>>()
                );
                for (key, value) in &expected {
                    assert_eq!(actual[key.as_str()].to_bits(), value.to_bits());
                }
                let restored: NativeStats =
                    serde_json::from_str(&serde_json::to_string(&actual).unwrap()).unwrap();
                for (key, value) in actual.iter() {
                    assert_eq!(restored[key].to_bits(), value.to_bits());
                }
            }
        }
        let mut negative_zero = NativeStats::from([("ATK".into(), -0.0)]);
        negative_zero.add_assign(&NativeStats::new());
        assert_eq!(negative_zero["ATK"].to_bits(), (-0.0_f64).to_bits());
    }
}
