//! Dense known coordinates with a sparse fallback and unchanged JSON map contract.
use serde::{Deserialize, Serialize};
use std::collections::BTreeMap;
pub const STAT_COUNT: usize = 59;
// All coordinates read by the native evaluator, including utility goals.
// Keep this in sync with stat()/stat_total() dependencies in the evaluator.
macro_rules! stat_keys {
    ($($key:ident),* $(,)?) => {
        // Variants mirror StatRegistry keys; their dense indices are tested.
        #[allow(non_camel_case_types, clippy::upper_case_acronyms)]
        #[derive(Clone, Copy, Debug)]
        #[repr(usize)]
        pub enum StatKey { $($key,)* }
        pub const KEYS: [&str; STAT_COUNT] = [$(stringify!($key),)*];
        impl StatKey {
            pub fn name(self) -> &'static str { KEYS[self as usize] }
        }
        #[inline]
        fn index(key: &str) -> Option<usize> {
            match key { $(stringify!($key) => Some(StatKey::$key as usize),)* _ => None }
        }
        #[cfg(test)]
        const TYPED_KEYS: [StatKey; STAT_COUNT] = [$(StatKey::$key,)*];
    };
}
stat_keys! { AGI, AGIP, AMPR, AMPRP, ASPD, ASPD_P, ATK, ATKP, CDMG, CDMGP, CRIT, CRITP, DAMAGE_P, DEX, DEXP, ELEM_P, INT, INTP, LRW, MAG_PIERCE, MATK, MATKP, MAXHP, MAXHPP, MAXMP, PHYS_PIERCE, SRW, STABILITY, STR, STRP, UNSHEATHE, UNSHEATHEP, VIT, VITP, WATK, WATKP, MOTIONSPEED, CSPD, CSPD_P, CAST_RED, ATK_UP_STR, ATK_UP_DEX, ATK_UP_AGI, ATK_UP_INT, ATK_UP_VIT, MATK_UP_STR, MATK_UP_DEX, MATK_UP_AGI, MATK_UP_INT, MATK_UP_VIT, ELEM_AWAKENING, MAGIC_ELEMENT, FIRE_DMG, WATER_DMG, WIND_DMG, EARTH_DMG, LIGHT_DMG, DARK_DMG, NEUTRAL_DMG }
#[derive(Clone, Debug, PartialEq)]
pub struct NativeStats {
    values: [f64; STAT_COUNT],
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
            values: [0.0; STAT_COUNT],
            present: 0,
            extra: BTreeMap::new(),
        }
    }
    /// Search-only copy. Raw package options remain available for result output.
    /// Preserve presence, negative values and signed zero without re-summing.
    pub fn evaluation_projection(&self) -> Self {
        Self {
            values: self.values,
            present: self.present,
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
    pub fn get_mut(&mut self, key: &str) -> Option<&mut f64> {
        match index(key) {
            Some(i) if self.present & (1 << i) != 0 => Some(&mut self.values[i]),
            Some(_) => None,
            None => self.extra.get_mut(key),
        }
    }
    #[inline]
    pub fn number_at(&self, key: StatKey) -> f64 {
        let i = key as usize;
        if self.present & (1 << i) != 0 {
            self.values[i]
        } else {
            0.0
        }
    }
    #[inline]
    pub fn sum_at(&self, right: &Self, key: StatKey) -> f64 {
        let i = key as usize;
        let left = self.number_at(key);
        if right.present & (1 << i) != 0 {
            left + right.values[i]
        } else {
            left
        }
    }
    /// Read one coordinate of the same ordered sum as clone()+add_assign().
    /// An absent right coordinate must leave a left signed zero unchanged.
    #[inline]
    pub fn sum_number(&self, right: &Self, key: &str) -> f64 {
        if let Some(i) = index(key) {
            let left = if self.present & (1 << i) != 0 {
                self.values[i]
            } else {
                0.0
            };
            if right.present & (1 << i) != 0 {
                left + right.values[i]
            } else {
                left
            }
        } else {
            let left = self.extra.get(key).copied().unwrap_or(0.0);
            right.extra.get(key).map_or(left, |value| left + value)
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
    fn typed_keys_match_sparse_lookup_and_lazy_sum_bits() {
        for key in TYPED_KEYS {
            assert_eq!(index(key.name()), Some(key as usize));
            for left in [None, Some(-0.0), Some(-17.25), Some(1e16)] {
                for right in [None, Some(-0.0), Some(0.0), Some(3.5), Some(-1e16)] {
                    let mut a = NativeStats::new();
                    let mut b = NativeStats::new();
                    if let Some(v) = left {
                        a.insert(key.name().into(), v);
                    }
                    if let Some(v) = right {
                        b.insert(key.name().into(), v);
                    }
                    assert_eq!(
                        a.number_at(key).to_bits(),
                        a.get(key.name()).copied().unwrap_or(0.0).to_bits()
                    );
                    let mut sum = a.clone();
                    sum.add_assign(&b);
                    assert_eq!(a.sum_at(&b, key).to_bits(), sum.number_at(key).to_bits());
                }
            }
        }
    }
    #[test]
    fn lazy_sum_matches_materialized_coordinate_bits() {
        let values = [
            None,
            Some(-0.0),
            Some(0.0),
            Some(-7.25),
            Some(1e20),
            Some(-1e20),
            Some(f64::INFINITY),
            Some(f64::NAN),
        ];
        for key in KEYS.into_iter().chain(["future-coordinate"]) {
            for left_value in values {
                for right_value in values {
                    let mut left = NativeStats::new();
                    let mut right = NativeStats::new();
                    if let Some(value) = left_value {
                        left.insert(key.into(), value);
                    }
                    if let Some(value) = right_value {
                        right.insert(key.into(), value);
                    }
                    let mut expected = left.clone();
                    expected.add_assign(&right);
                    assert_eq!(
                        left.sum_number(&right, key).to_bits(),
                        expected.get(key).copied().unwrap_or(0.0).to_bits(),
                        "{key}"
                    );
                }
            }
        }
    }
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
                let projected = actual.evaluation_projection();
                assert!(projected.extra.is_empty());
                for key in KEYS {
                    assert_eq!(
                        projected.get(key).map(|v| v.to_bits()),
                        expected.get(key).map(|v| v.to_bits())
                    );
                }
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
