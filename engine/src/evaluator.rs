//! Native build evaluator shared by exact search and parity verification.
//! Formula changes require the JavaScript/Rust parity and upper-bound gates.

use std::collections::BTreeMap;

use serde::Serialize;
use serde_json::Value;
#[path = "stats.rs"]
#[allow(dead_code)] // The summary bridge does not link search-only operations.
mod native_stats;
pub use native_stats::NativeStats;
use native_stats::StatKey;
#[cfg(test)]
#[allow(unused_imports)] // Summary-only bridges do not link solver property tests.
pub use native_stats::KEYS as NATIVE_STAT_KEYS;

// Decimal input coefficients use integer ratios. Common integral operands stay
// in i128; BigInt is an exact overflow fallback, not a floating-point fallback.
pub(crate) mod decimal_math {
    use num_bigint::{BigInt, Sign};
    use std::fmt::Write;
    use std::{cell::RefCell, collections::HashMap};
    thread_local! {
        static PARTS: RefCell<HashMap<u64, (i128, i128)>> = RefCell::new(HashMap::new());
        static TEXT: RefCell<String> = const { RefCell::new(String::new()) };
    }
    fn decimal_text(value: f64) -> (String, i32) {
        let text = value.to_string();
        let (mantissa, exponent) = text
            .split_once('e')
            .map_or((text.as_str(), 0), |(a, b)| (a, b.parse::<i32>().unwrap()));
        let places = mantissa.split_once('.').map_or(0, |(_, b)| b.len() as i32);
        (mantissa.replace('.', ""), places - exponent)
    }
    fn small_parts(value: f64) -> Option<(i128, i128)> {
        if value.fract() == 0.0 && value.abs() <= 9007199254740991.0 {
            return Some((value as i128, 1));
        }
        if let Some(pair) = PARTS.with(|cache| cache.borrow().get(&value.to_bits()).copied()) {
            return Some(pair);
        }
        // Reuse decimal text per thread: shared WASM allocation otherwise serializes workers.
        let (n, scale) = TEXT.with(|text| {
            let mut text = text.borrow_mut();
            text.clear();
            write!(text, "{value}").unwrap();
            let (mantissa, exponent) = text
                .split_once('e')
                .map_or((text.as_str(), 0), |(a, b)| (a, b.parse::<i32>().unwrap()));
            let length = mantissa.len();
            let scale = mantissa.split_once('.').map_or(0, |(_, b)| b.len() as i32) - exponent;
            text.truncate(length);
            text.retain(|c| c != '.');
            Some((text.parse::<i128>().ok()?, scale))
        })?;
        let pair = if scale >= 0 {
            (n, 10_i128.checked_pow(scale as u32)?)
        } else {
            (n.checked_mul(10_i128.checked_pow((-scale) as u32)?)?, 1)
        };
        PARTS.with(|cache| {
            let mut cache = cache.borrow_mut();
            if cache.len() >= 1024 {
                cache.clear();
            }
            cache.insert(value.to_bits(), pair);
        });
        Some(pair)
    }
    fn big_parts(value: f64) -> (BigInt, BigInt) {
        let (digits, scale) = decimal_text(value);
        let n: BigInt = digits.parse().unwrap();
        if scale >= 0 {
            (n, BigInt::from(10).pow(scale as u32))
        } else {
            (n * BigInt::from(10).pow((-scale) as u32), BigInt::from(1))
        }
    }
    #[test]
    fn reused_decimal_text_matches_original_conversion_across_cache_evictions() {
        for exponent in -30..=30 {
            for numerator in -23..=23 {
                let value = f64::from(numerator) * 1.37 * 10.0_f64.powi(exponent);
                let expected = (|| {
                    let (digits, scale) = decimal_text(value);
                    let n = digits.parse::<i128>().ok()?;
                    if scale >= 0 {
                        Some((n, 10_i128.checked_pow(scale as u32)?))
                    } else {
                        Some((n.checked_mul(10_i128.checked_pow((-scale) as u32)?)?, 1))
                    }
                })();
                assert_eq!(small_parts(value), expected, "{value}");
            }
        }
    }
    fn small_ratio(
        v: (i128, i128),
        r: (i128, i128),
        d: (i128, i128),
        f: (i128, i128),
    ) -> Option<f64> {
        let n = v.0.checked_mul(r.0)?.checked_mul(d.1)?;
        let den = v.1.checked_mul(r.1)?.checked_mul(d.0)?;
        let mut n = n.checked_mul(f.1)?.checked_add(f.0.checked_mul(den)?)?;
        let mut den = den.checked_mul(f.1)?;
        if den < 0 {
            n = n.checked_neg()?;
            den = den.checked_neg()?;
        }
        Some(n.checked_div_euclid(den)? as f64)
    }
    fn big_ratio(
        v: (BigInt, BigInt),
        r: (BigInt, BigInt),
        d: (BigInt, BigInt),
        f: (BigInt, BigInt),
    ) -> f64 {
        let n = v.0 * r.0 * d.1;
        let den = v.1 * r.1 * d.0;
        let mut n = n * &f.1 + f.0 * &den;
        let mut den = den * f.1;
        if den.sign() == Sign::Minus {
            n = -n;
            den = -den;
        }
        let mut q = &n / &den;
        if (&n % &den).sign() == Sign::Minus {
            q -= 1;
        }
        q.to_string().parse().unwrap()
    }
    pub fn floor_ratio(value: f64, rate: f64, divisor: f64, flat: f64) -> f64 {
        // Identity stages need no multiplication or decimal conversion.
        if rate == divisor && divisor != 0.0 && divisor.is_finite() && flat == 0.0 {
            return value.floor();
        }
        // These operand limits prove both products and their sum fit i64.
        // Keep the common integer stages out of i128 division and the cache.
        if divisor != 0.0
            && [value, rate, divisor, flat]
                .iter()
                .all(|v| v.abs() <= 2147483647.0 && v.fract() == 0.0)
        {
            let n = (value as i64) * (rate as i64) + (flat as i64) * (divisor as i64);
            let d = divisor as i64;
            return if d > 0 {
                n.div_euclid(d)
            } else {
                (-n).div_euclid(-d)
            } as f64;
        }
        if ![value, rate, divisor, flat].iter().all(|v| v.is_finite()) || divisor == 0.0 {
            return (value * rate / divisor + flat).floor();
        }
        if let (Some(v), Some(r), Some(d), Some(f)) = (
            small_parts(value),
            small_parts(rate),
            small_parts(divisor),
            small_parts(flat),
        ) {
            if let Some(result) = small_ratio(v, r, d, f) {
                return result;
            }
        }
        big_ratio(
            big_parts(value),
            big_parts(rate),
            big_parts(divisor),
            big_parts(flat),
        )
    }
    pub fn floor_percent(value: f64, rate: f64, flat: f64) -> f64 {
        if rate.fract() == 0.0 && rate.abs() < 9007199254740000.0 {
            return floor_ratio(value, 100.0 + rate, 100.0, flat);
        }
        if ![value, rate, flat].iter().all(|v| v.is_finite()) {
            return (value * (1.0 + rate / 100.0) + flat).floor();
        }
        if let (Some(v), Some(r), Some(f)) =
            (small_parts(value), small_parts(rate), small_parts(flat))
        {
            if let Some(n) = r.1.checked_mul(100).and_then(|n| n.checked_add(r.0)) {
                if let Some(result) = small_ratio(v, (n, r.1), (100, 1), f) {
                    return result;
                }
            }
        }
        let r = big_parts(rate);
        big_ratio(
            big_parts(value),
            (&r.1 * 100 + r.0, r.1),
            (BigInt::from(100), BigInt::from(1)),
            big_parts(flat),
        )
    }

    /// Decimal coefficient preparation belongs to the immutable context, not
    /// each candidate. Checked products retain the ordinary exact fallback.
    #[derive(Clone, Debug)]
    pub struct PreparedMultiplier {
        rate: f64,
        ratio: Option<(i128, i128)>,
    }
    impl PreparedMultiplier {
        pub fn new(rate: f64) -> Self {
            let ratio = rate.is_finite().then(|| small_parts(rate)).flatten();
            Self { rate, ratio }
        }
        pub fn apply(&self, value: f64) -> f64 {
            if self.rate == 1.0 {
                return value.floor();
            }
            if value.is_finite() {
                if let (Some((n, d)), Some((v, vd))) = (self.ratio, small_parts(value)) {
                    if let Some(result) = v
                        .checked_mul(n)
                        .and_then(|n| vd.checked_mul(d).and_then(|d| n.checked_div_euclid(d)))
                    {
                        return result as f64;
                    }
                }
            }
            floor_ratio(value, self.rate, 1.0, 0.0)
        }
    }
}
use decimal_math::{floor_percent, floor_ratio};

#[path = "joint_supply.rs"]
#[allow(dead_code)] // Summary-only bridges do not prepare search bounds.
pub mod joint_supply;

/// Immutable lookup cache. JSON remains the serialization contract; cached
/// fields preserve missing/null/type semantics and are rebuilt on deserialize.
pub trait ContextLookup {
    fn context_get(&self, key: &str) -> Option<&Value>;
    fn number_at(&self, key: ContextKey) -> f64 {
        self.context_number(key.name())
    }
    fn flag_at(&self, key: ContextKey) -> bool {
        self.context_flag(key.name())
    }
    fn get_at(&self, key: ContextKey) -> Option<&Value> {
        self.context_get(key.name())
    }
    fn context_number(&self, key: &str) -> f64 {
        self.context_get(key).and_then(Value::as_f64).unwrap_or(0.0)
    }
    fn context_flag(&self, key: &str) -> bool {
        self.context_get(key)
            .and_then(Value::as_bool)
            .unwrap_or(false)
    }
    fn prepared_effects(&self) -> Option<&PreparedEffects> {
        None
    }
    fn invariant(&self, kind: Invariant) -> f64;
    fn is_object(&self) -> bool;
    fn evaluation_plan(&self) -> Option<EvaluationPlan> {
        None
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum WeaponKind {
    Sword,
    TwoHand,
    Bow,
    Bowgun,
    Staff,
    Device,
    Knuckle,
    Halberd,
    Katana,
    Barehand,
    Other,
}
impl WeaponKind {
    fn from_name(name: &str) -> Self {
        match name {
            "한손검" => Self::Sword,
            "양손검" => Self::TwoHand,
            "활" => Self::Bow,
            "자동활" => Self::Bowgun,
            "지팡이" => Self::Staff,
            "마도구" => Self::Device,
            "권갑" => Self::Knuckle,
            "선풍창" => Self::Halberd,
            "발도검" => Self::Katana,
            "맨손" => Self::Barehand,
            _ => Self::Other,
        }
    }
}

#[derive(Clone, Copy, Debug)]
enum PowerMode {
    Atk,
    Matk,
    Sum,
    Higher,
    WizardBlend,
}

#[derive(Clone, Copy, Debug)]
pub struct EvaluationPlan {
    weapon: WeaponKind,
    sub_dual: bool,
    power: PowerMode,
    is_magic: bool,
    need_atk: bool,
    need_matk: bool,
    arrow: bool,
    dual: bool,
    sub_device: bool,
    conversion: bool,
    armor_aspd: f64,
    weapon_aspd: f64,
}

impl EvaluationPlan {
    fn new<C: ContextLookup>(base: &C) -> Self {
        let main = text_at(base, ContextKey::field_main_type);
        let sub = text_at(base, ContextKey::field_sub_type);
        let is_magic = text_at(base, ContextKey::field_atk_type) == "MAG";
        let power = match text_at(base, ContextKey::field_attack_power_mode) {
            "sum" => PowerMode::Sum,
            "higher" => PowerMode::Higher,
            "atk" => PowerMode::Atk,
            "wizardBlend" => PowerMode::WizardBlend,
            _ if is_magic => PowerMode::Matk,
            _ => PowerMode::Atk,
        };
        Self {
            weapon: WeaponKind::from_name(main),
            sub_dual: sub == "한손검(듀얼소드)",
            power,
            is_magic,
            need_atk: !matches!(power, PowerMode::Matk),
            need_matk: !matches!(power, PowerMode::Atk),
            arrow: sub == "화살" && matches!(main, "활" | "자동활"),
            dual: main == "한손검" && sub == "한손검(듀얼소드)",
            sub_device: sub == "마도구",
            conversion: number_at(base, ContextKey::field_conversion_level) > 0.0
                && matches!(main, "한손검" | "양손검" | "자동활" | "권갑"),
            armor_aspd: match text_at(base, ContextKey::field_armor_type) {
                "경량옷" => 50.0,
                "중량옷" => -50.0,
                _ => 0.0,
            },
            weapon_aspd: base_aspd(main),
        }
    }
}

impl ContextLookup for Value {
    fn invariant(&self, kind: Invariant) -> f64 {
        compute_invariant(self, kind)
    }
    #[inline]
    fn context_get(&self, key: &str) -> Option<&Value> {
        self.get(key)
    }
    fn is_object(&self) -> bool {
        Value::is_object(self)
    }
}

#[derive(Clone, Copy)]
pub enum Invariant {
    AtkUp,
    MatkUp,
    PhysResistance,
    MagicResistance,
    Proc,
    BaseCrit,
    MainRefineSquared,
    SubRefineSquared,
    ConversionSquared,
    MpFlat,
}

// Native caps 166..175 accumulate f32 terms in cap order and truncate once.
pub(crate) fn proportional_attack<C: ContextLookup>(base: &C, rates: [f64; 5]) -> f64 {
    let mut total = 0.0_f32;
    for (attribute, rate) in [
        ContextKey::field_str_base,
        ContextKey::field_int_base,
        ContextKey::field_vit_base,
        ContextKey::field_agi_base,
        ContextKey::field_dex_base,
    ]
    .into_iter()
    .zip(rates)
    {
        let mut scaled = rate * 10.0;
        let nearest = scaled.round();
        if (scaled - nearest).abs() <= scaled.abs().max(1.0) * 2.0_f64.powi(-22) {
            scaled = nearest;
        }
        let factor = scaled as f32 / 1000.0_f32;
        let term = factor * number_at(base, attribute) as f32;
        total += term;
    }
    let result = total.trunc();
    if result == 0.0 {
        0.0
    } else {
        result as f64
    }
}

// Only base-context expressions belong here; no candidate stats are cached.
fn compute_invariant(base: &Value, kind: Invariant) -> f64 {
    match kind {
        Invariant::AtkUp => proportional_attack(
            base,
            ["atkUpSTR", "atkUpINT", "atkUpVIT", "atkUpAGI", "atkUpDEX"]
                .map(|key| number(base, key)),
        ),
        Invariant::MatkUp => proportional_attack(
            base,
            [
                "matkUpSTR",
                "matkUpINT",
                "matkUpVIT",
                "matkUpAGI",
                "matkUpDEX",
            ]
            .map(|key| number(base, key)),
        ),
        Invariant::PhysResistance => resistance_multiplier(base, false),
        Invariant::MagicResistance => resistance_multiplier(base, true),
        Invariant::Proc => expected_proc_multiplier(base),
        Invariant::BaseCrit => {
            25.0 + floor_ratio(number_at(base, ContextKey::field_crt_base), 10.0, 34.0, 0.0)
        }
        Invariant::MainRefineSquared => number_at(base, ContextKey::field_wpn_refine).powi(2),
        Invariant::SubRefineSquared => number_at(base, ContextKey::field_sub_refine).powi(2),
        Invariant::ConversionSquared => number_at(base, ContextKey::field_conversion_level).powi(2),
        Invariant::MpFlat => {
            100.0
                + number_at(base, ContextKey::field_level)
                + number_at(base, ContextKey::field_max_mp_f)
        }
    }
}

#[derive(Clone, Debug)]
struct PreparedField {
    original: Option<Value>,
    number: f64,
    flag: bool,
}
impl PreparedField {
    fn new(value: Option<&Value>) -> Self {
        Self {
            original: value.cloned(),
            number: value.and_then(Value::as_f64).unwrap_or(0.0),
            flag: value.and_then(Value::as_bool).unwrap_or(false),
        }
    }
}

macro_rules! prepared_context {
    ($($field:ident => $key:literal),* $(,)?) => {
        /// Typed fields avoid repeated string dispatch in every search evaluation.
        // Include fields consumed through nested-effect preparation as well.
        #[allow(non_camel_case_types, dead_code)]
        #[derive(Clone, Copy, Debug)]
        pub enum ContextKey { $($field,)* }
        impl ContextKey {
            fn name(self) -> &'static str { match self { $(Self::$field => $key,)* } }
        }
        #[cfg(test)]
        const PREPARED_FIELDS: &[(ContextKey, &str)] = &[$((ContextKey::$field, $key),)*];
        #[cfg(test)]
        const PREPARED_KEYS: &[&str] = &[$($key,)*];
        #[derive(Clone, Debug, Serialize)]
        #[serde(transparent)]
        pub struct PreparedContext {
            original: Value,
            #[serde(skip)] invariants: [f64; 10],
            #[serde(skip)] plan: EvaluationPlan,
            #[serde(skip)] effects: PreparedEffects,
            $(#[serde(skip)] $field: PreparedField,)*
        }
        impl From<Value> for PreparedContext {
            fn from(original: Value) -> Self {
                Self { $($field: PreparedField::new(original.get($key)),)*
                    plan: EvaluationPlan::new(&original),
                    effects: PreparedEffects::new(&original),
                    invariants: [Invariant::AtkUp, Invariant::MatkUp, Invariant::PhysResistance, Invariant::MagicResistance, Invariant::Proc, Invariant::BaseCrit, Invariant::MainRefineSquared, Invariant::SubRefineSquared, Invariant::ConversionSquared, Invariant::MpFlat].map(|kind| compute_invariant(&original, kind)), original }
            }
        }
        impl<'de> serde::Deserialize<'de> for PreparedContext {
            fn deserialize<D: serde::Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
                <Value as serde::Deserialize>::deserialize(deserializer).map(Self::from)
            }
        }
        impl std::ops::Deref for PreparedContext {
            type Target = Value;
            fn deref(&self) -> &Value { &self.original }
        }
        impl ContextLookup for PreparedContext {
            #[inline]
            fn number_at(&self, key: ContextKey) -> f64 { match key { $(ContextKey::$field => self.$field.number,)* } }
            #[inline]
            fn flag_at(&self, key: ContextKey) -> bool { match key { $(ContextKey::$field => self.$field.flag,)* } }
            #[inline]
            fn get_at(&self, key: ContextKey) -> Option<&Value> { match key { $(ContextKey::$field => self.$field.original.as_ref(),)* } }
            #[inline]
            fn context_number(&self, key: &str) -> f64 {
                match key {
                    $($key => self.$field.number,)*
                    _ => self.original.context_number(key),
                }
            }
            #[inline]
            fn context_flag(&self, key: &str) -> bool {
                match key {
                    $($key => self.$field.flag,)*
                    _ => self.original.context_flag(key),
                }
            }
            #[inline]
            fn evaluation_plan(&self) -> Option<EvaluationPlan> { Some(self.plan) }
            fn prepared_effects(&self) -> Option<&PreparedEffects> { Some(&self.effects) }
            #[inline]
            fn invariant(&self, kind: Invariant) -> f64 { self.invariants[kind as usize] }
            #[inline]
            fn context_get(&self, key: &str) -> Option<&Value> {
                match key {
                    $($key => self.$field.original.as_ref(),)*
                    _ => self.original.get(key),
                }
            }
            fn is_object(&self) -> bool { self.original.is_object() }
        }
    };
}

prepared_context! {
    field_active_build_conversions => "activeBuildConversions",
    field_additional_target_resistances => "additionalTargetResistances",
    field_agi_base => "agiBase",
    field_agi_f => "agiF",
    field_agi_p => "agiP",
    field_ampr_f => "amprF",
    field_ampr_p => "amprP",
    field_armor_type => "armorType",
    field_aspd_f => "aspdF",
    field_aspd_p => "aspdP",
    field_atk_f => "atkF",
    field_atk_p => "atkP",
    field_atk_type => "atkType",
    field_atk_up_a_g_i => "atkUpAGI",
    field_atk_up_d_e_x => "atkUpDEX",
    field_atk_up_i_n_t => "atkUpINT",
    field_atk_up_s_t_r => "atkUpSTR",
    field_atk_up_v_i_t => "atkUpVIT",
    field_attack_element => "attackElement",
    field_attack_power_mode => "attackPowerMode",
    field_base_wpn_atk_f => "baseWpnAtkF",
    field_boss_crit_resist => "bossCritResist",
    field_boss_def => "bossDef",
    field_boss_level => "bossLevel",
    field_boss_mag_resist => "bossMagResist",
    field_boss_mdef => "bossMdef",
    field_boss_phys_resist => "bossPhysResist",
    field_cdmg_f => "cdmgF",
    field_cdmg_p => "cdmgP",
    field_chk_guaranteed_crit => "chkGuaranteedCrit",
    field_chk_is_unsheathe => "chkIsUnsheathe",
    field_conversion_level => "conversionLevel",
    field_crit_f => "critF",
    field_crit_p => "critP",
    field_critical_chance_bonus => "criticalChanceBonus",
    field_critical_chance_multiplier => "criticalChanceMultiplier",
    field_crt_base => "crtBase",
    field_damage_multiplier_layers => "damageMultiplierLayers",
    field_damage_p => "damageP",
    field_dex_base => "dexBase",
    field_dex_f => "dexF",
    field_dex_p => "dexP",
    field_dual_bringer_active => "dualBringerActive",
    field_dual_bringer_level => "dualBringerLevel",
    field_elem_p => "elemP",
    field_fire_dmg => "fireDmg",
    field_water_dmg => "waterDmg",
    field_wind_dmg => "windDmg",
    field_earth_dmg => "earthDmg",
    field_light_dmg => "lightDmg",
    field_dark_dmg => "darkDmg",
    field_neutral_dmg => "neutralDmg",
    field_element_awakening => "elementAwakening",
    field_fixed_critical_chance => "fixedCriticalChance",
    field_half_mdef_ignored => "halfMdefIgnored",
    field_ignore_defense => "ignoreDefense",
    field_ignore_mdef => "ignoreMdef",
    field_int_base => "intBase",
    field_int_f => "intF",
    field_int_p => "intP",
    field_level => "level",
    field_lrw => "lrw",
    field_mag_pierce => "magPierce",
    field_magic_element => "magicElement",
    field_magic_pierce_skill_bonus => "magicPierceSkillBonus",
    field_main_type => "mainType",
    field_matk_f => "matkF",
    field_matk_p => "matkP",
    field_matk_up_a_g_i => "matkUpAGI",
    field_matk_up_d_e_x => "matkUpDEX",
    field_matk_up_i_n_t => "matkUpINT",
    field_matk_up_s_t_r => "matkUpSTR",
    field_matk_up_v_i_t => "matkUpVIT",
    field_max_hp_f => "maxHpF",
    field_max_hp_p => "maxHpP",
    field_max_mp_f => "maxMpF",
    field_minimum_critical_damage => "minimumCriticalDamage",
    field_no_critical => "noCritical",
    field_motion_speed => "motionSpeed",
    field_godspeed_wield_level => "godspeedWieldLevel",
    field_normal_attack_ampr_profile => "normalAttackAmprProfile",
    field_phys_pierce => "physPierce",
    field_physical_pierce_skill_bonus => "physicalPierceSkillBonus",
    field_proc_damage_modifiers => "procDamageModifiers",
    field_range_type => "rangeType",
    field_skill_const => "skillConst",
    field_skill_mult => "skillMult",
    field_skill_stats => "skillStats",
    field_spell_burst_level => "spellBurstLevel",
    field_srw => "srw",
    field_stability => "stability",
    field_stability_bonus => "stabilityBonus",
    field_str_base => "strBase",
    field_str_f => "strF",
    field_str_p => "strP",
    field_sub_atk => "subAtk",
    field_sub_refine => "subRefine",
    field_sub_stab => "subStab",
    field_sub_type => "subType",
    field_weapon_element => "weaponElement",
    field_sub_weapon_element => "subWeaponElement",
    field_target_element => "targetElement",
    field_target_weakened => "targetWeakened",
    field_unsheathe_f => "unsheatheF",
    field_unsheathe_p => "unsheatheP",
    field_use_higher_range_damage => "useHigherRangeDamage",
    field_vit_base => "vitBase",
    field_vit_f => "vitF",
    field_vit_p => "vitP",
    field_watk_f => "watkF",
    field_watk_p => "watkP",
    field_wpn_atk => "wpnAtk",
    field_wpn_refine => "wpnRefine",
    field_wpn_stab => "wpnStab",
}

#[derive(Clone, Debug, PartialEq, Serialize)]
pub struct CrystaOptimizationNativeSummary {
    #[serde(rename = "optimizationDamageFactor")]
    pub optimization_damage_factor: f64,
    #[serde(rename = "finalMaxHP")]
    pub final_max_hp: i64,
    #[serde(rename = "finalMaxMP")]
    pub final_max_mp: i64,
    #[serde(rename = "amprBeforeDual")]
    pub ampr_before_dual: i64,
    #[serde(rename = "normalAttackCrit")]
    pub normal_attack_crit: i64,
    #[serde(rename = "finalASPD")]
    pub final_aspd: i64,
}

#[inline]
fn number_at<C: ContextLookup>(value: &C, key: ContextKey) -> f64 {
    value.number_at(key)
}
#[inline]
fn flag_at<C: ContextLookup>(value: &C, key: ContextKey) -> bool {
    value.flag_at(key)
}
#[inline]
fn text_at<C: ContextLookup>(value: &C, key: ContextKey) -> &str {
    value.get_at(key).and_then(Value::as_str).unwrap_or("")
}

fn number<C: ContextLookup>(value: &C, key: &str) -> f64 {
    value.context_number(key)
}

#[cfg(test)]
fn flag<C: ContextLookup>(value: &C, key: &str) -> bool {
    value.context_flag(key)
}

fn text<'a, C: ContextLookup>(value: &'a C, key: &str) -> &'a str {
    value.context_get(key).and_then(Value::as_str).unwrap_or("")
}

fn finite_number<C: ContextLookup>(value: &C, key: &str, default: f64) -> f64 {
    value
        .context_get(key)
        .and_then(Value::as_f64)
        .filter(|number| number.is_finite())
        .unwrap_or(default)
}

fn array<'a, C: ContextLookup>(value: &'a C, key: &str) -> &'a [Value] {
    value
        .context_get(key)
        .and_then(Value::as_array)
        .map(Vec::as_slice)
        .unwrap_or(&[])
}

#[derive(Clone, Debug)]
struct AmprModifier {
    percent: f64,
    multiplier: f64,
    flat: f64,
    id: String,
}
impl AmprModifier {
    fn new(value: &Value) -> Self {
        Self {
            percent: number(value, "percent"),
            multiplier: finite_number(value, "multiplier", 1.0),
            flat: number(value, "flat"),
            id: value.get("id").map(Value::to_string).unwrap_or_default(),
        }
    }
    fn apply(&self, value: f64) -> f64 {
        let mut result = floor(value);
        if self.percent != 0.0 {
            result = floor_percent(result, self.percent, 0.0);
        }
        if self.multiplier != 1.0 {
            result = floor_ratio(result, self.multiplier, 1.0, 0.0);
        }
        floor(result + self.flat)
    }
}
#[derive(Clone, Debug)]
enum SkillSource {
    Fixed(f64),
    Total(usize),
}
#[derive(Clone, Debug)]
struct SkillTerm {
    source: SkillSource,
    ratio: f64,
    to_mult: bool,
}
/// Derived only from immutable input; rebuilt from original JSON on restore.
#[derive(Clone, Debug)]
pub struct PreparedEffects {
    passive_ampr: Vec<AmprModifier>,
    active_ampr: Vec<AmprModifier>,
    conversions: Vec<f64>,
    layers: [f64; 4],
    layer_ratios: [decimal_math::PreparedMultiplier; 4],
    skill_terms: Vec<SkillTerm>,
}
impl PreparedEffects {
    fn new(base: &Value) -> Self {
        let profile = base
            .context_get("normalAttackAmprProfile")
            .unwrap_or(&Value::Null);
        let layers = base.get("damageMultiplierLayers").unwrap_or(&Value::Null);
        let layer_values = [
            finite_number(
                layers,
                "skill",
                number_at(base, ContextKey::field_skill_mult),
            ),
            finite_number(layers, "passive", 1.0),
            finite_number(layers, "active", 1.0),
            finite_number(layers, "combo", 1.0),
        ];
        let skill_terms = array(base, "skillStats")
            .iter()
            .filter_map(|item| {
                let to_mult = match text(item, "target") {
                    "mult" => true,
                    "const" => false,
                    _ => return None,
                };
                let source = match text(item, "stat") {
                    "STR" => SkillSource::Fixed(number_at(base, ContextKey::field_str_base)),
                    "INT" => SkillSource::Fixed(number_at(base, ContextKey::field_int_base)),
                    "VIT" => SkillSource::Fixed(number_at(base, ContextKey::field_vit_base)),
                    "AGI" => SkillSource::Fixed(number_at(base, ContextKey::field_agi_base)),
                    "DEX" => SkillSource::Fixed(number_at(base, ContextKey::field_dex_base)),
                    "totalSTR" => SkillSource::Total(0),
                    "totalINT" => SkillSource::Total(1),
                    "totalVIT" => SkillSource::Total(2),
                    "totalAGI" => SkillSource::Total(3),
                    "totalDEX" => SkillSource::Total(4),
                    _ => SkillSource::Fixed(0.0),
                };
                Some(SkillTerm {
                    source,
                    ratio: number(item, "ratio"),
                    to_mult,
                })
            })
            .collect();
        Self {
            passive_ampr: array(profile, "passive")
                .iter()
                .map(AmprModifier::new)
                .collect(),
            active_ampr: array(profile, "activeCandidates")
                .iter()
                .map(AmprModifier::new)
                .collect(),
            conversions: array(base, "activeBuildConversions")
                .iter()
                .filter(|v| text(*v, "conversion") == "unsheatheToAtk")
                .map(|v| number(v, "value"))
                .collect(),
            layers: layer_values,
            layer_ratios: layer_values.map(decimal_math::PreparedMultiplier::new),
            skill_terms,
        }
    }
    fn ampr(&self, value: f64) -> f64 {
        let passive = self
            .passive_ampr
            .iter()
            .fold(floor(value), |v, m| m.apply(v));
        self.active_ampr
            .iter()
            .map(|m| (m.apply(passive), &m.id))
            .min_by(|a, b| {
                b.0.partial_cmp(&a.0)
                    .unwrap_or(std::cmp::Ordering::Equal)
                    .then_with(|| a.1.cmp(b.1))
            })
            .map(|v| v.0)
            .unwrap_or(passive)
    }
}

fn modifier_ampr(value: f64, modifier: &Value) -> f64 {
    let mut result = floor(value);
    let percent = number(modifier, "percent");
    let multiplier = finite_number(modifier, "multiplier", 1.0);
    if percent != 0.0 {
        result = floor_percent(result, percent, 0.0);
    }
    if multiplier != 1.0 {
        result = floor_ratio(result, multiplier, 1.0, 0.0);
    }
    floor(result + number(modifier, "flat"))
}

fn resolve_normal_attack_ampr(value: f64, profile: Option<&Value>) -> f64 {
    let Some(profile) = profile else {
        return floor(value);
    };
    let after_passive = array(profile, "passive")
        .iter()
        .fold(floor(value), |current, modifier| {
            modifier_ampr(current, modifier)
        });
    array(profile, "activeCandidates")
        .iter()
        .map(|modifier| {
            (
                modifier_ampr(after_passive, modifier),
                modifier.get("id").map(Value::to_string).unwrap_or_default(),
            )
        })
        .min_by(|left, right| {
            // The JavaScript reducer chooses the highest result and then the
            // lexically smallest id. Reverse that order for min_by.
            right
                .0
                .partial_cmp(&left.0)
                .unwrap_or(std::cmp::Ordering::Equal)
                .then_with(|| left.1.cmp(&right.1))
        })
        .map(|selected| selected.0)
        .unwrap_or(after_passive)
}

fn resistance_multiplier<C: ContextLookup>(base: &C, is_magic: bool) -> f64 {
    let resistance_key = if is_magic {
        "bossMagResist"
    } else {
        "bossPhysResist"
    };
    let total = number(base, resistance_key)
        + array(base, "additionalTargetResistances")
            .iter()
            .filter_map(Value::as_f64)
            .filter(|number| number.is_finite())
            .sum::<f64>();
    // Mirrors Math.round(x * 1e12) / 1e12 for the positive scale used here.
    ((1.0 - total / 100.0) * 1e12).round() / 1e12
}

fn expected_proc_multiplier<C: ContextLookup>(base: &C) -> f64 {
    array(base, "procDamageModifiers")
        .iter()
        .fold(1.0, |expected, item| {
            let chance = number(item, "chancePercent").clamp(0.0, 100.0);
            let multiplier = finite_number(item, "multiplier", 1.0);
            expected * (1.0 + chance / 100.0 * (multiplier - 1.0))
        })
}

trait StatLookup {
    fn stat_number(&self, key: &str) -> f64;
    fn stat_at(&self, key: StatKey) -> f64 {
        self.stat_number(key.name())
    }
}

struct SummedStats<'a> {
    left: &'a NativeStats,
    right: &'a NativeStats,
}
impl StatLookup for SummedStats<'_> {
    #[inline]
    fn stat_at(&self, key: StatKey) -> f64 {
        self.left.sum_at(self.right, key)
    }
    #[inline]
    fn stat_number(&self, key: &str) -> f64 {
        self.left.sum_number(self.right, key)
    }
}

impl StatLookup for Value {
    fn stat_number(&self, key: &str) -> f64 {
        number(self, key)
    }
}

impl StatLookup for BTreeMap<String, f64> {
    fn stat_number(&self, key: &str) -> f64 {
        self.get(key).copied().unwrap_or(0.0)
    }
}

// Per-evaluation numeric view: one map traversal, then direct field reads.
// Keep the source map for future/dynamic keys that are not cached here.
macro_rules! dense_stats {
    ($($field:ident => $key:literal),* $(,)?) => {
        #[cfg(test)]
        const DENSE_STAT_KEYS: &[&str] = &[$($key,)*];
        struct DenseStats<'a> {
            source: &'a BTreeMap<String, f64>,
            $($field: f64,)*
        }
        impl<'a> DenseStats<'a> {
            fn new(source: &'a BTreeMap<String, f64>) -> Self {
                let mut result = Self { source, $($field: 0.0,)* };
                for (key, value) in source {
                    match key.as_str() {
                        $($key => result.$field = *value,)*
                        _ => {},
                    }
                }
                result
            }
        }
        impl StatLookup for DenseStats<'_> {
            #[inline]
            fn stat_number(&self, key: &str) -> f64 {
                match key {
                    $($key => self.$field,)*
                    _ => self.source.stat_number(key),
                }
            }
        }
    };
}

dense_stats! {
    agi => "AGI",
    agip => "AGIP",
    ampr => "AMPR",
    amprp => "AMPRP",
    aspd => "ASPD",
    aspd_p => "ASPD_P",
    atk => "ATK",
    atkp => "ATKP",
    cdmg => "CDMG",
    cdmgp => "CDMGP",
    crit => "CRIT",
    critp => "CRITP",
    damage_p => "DAMAGE_P",
    dex => "DEX",
    dexp => "DEXP",
    elem_p => "ELEM_P",
    int => "INT",
    intp => "INTP",
    lrw => "LRW",
    mag_pierce => "MAG_PIERCE",
    matk => "MATK",
    matkp => "MATKP",
    maxhp => "MAXHP",
    maxhpp => "MAXHPP",
    maxmp => "MAXMP",
    phys_pierce => "PHYS_PIERCE",
    srw => "SRW",
    stability => "STABILITY",
    str => "STR",
    strp => "STRP",
    unsheathe => "UNSHEATHE",
    unsheathep => "UNSHEATHEP",
    vit => "VIT",
    vitp => "VITP",
    watk => "WATK",
    watkp => "WATKP",
}

impl StatLookup for NativeStats {
    #[inline]
    fn stat_at(&self, key: StatKey) -> f64 {
        self.number_at(key)
    }
    #[inline]
    fn stat_number(&self, key: &str) -> f64 {
        self.get(key).copied().unwrap_or(0.0)
    }
}
#[allow(dead_code)]
pub fn evaluate_summary_from_native_stats<C: ContextLookup>(
    base: &C,
    stats: &NativeStats,
) -> Result<CrystaOptimizationNativeSummary, String> {
    if !base.is_object() {
        return Err("CrystaOptimization native summary requires an object base context".into());
    }
    evaluate_summary_from_lookup(base, stats)
}

#[inline]
fn stat_at<T: StatLookup>(stats: &T, key: StatKey) -> f64 {
    stats.stat_at(key)
}

fn floor_layer<C: ContextLookup>(base: &C, value: f64, index: usize, rate: f64) -> f64 {
    if let Some(effects) = base.prepared_effects() {
        // Dynamic skill terms keep their original assembled coefficient.
        if rate.to_bits() == effects.layers[index].to_bits() {
            return effects.layer_ratios[index].apply(value);
        }
    }
    floor_ratio(value, rate, 1.0, 0.0)
}

fn floor(value: f64) -> f64 {
    value.floor()
}

fn stat_total<T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    base_key: ContextKey,
    percent_key: ContextKey,
    flat_key: ContextKey,
    stat_percent: StatKey,
    stat_flat: StatKey,
) -> f64 {
    floor_percent(
        number_at(base, base_key),
        number_at(base, percent_key) + stat_at(stats, stat_percent),
        number_at(base, flat_key) + stat_at(stats, stat_flat),
    )
}

#[cfg(test)]
fn atk_stat(main: &str, sub: &str, str_: f64, int_: f64, agi: f64, dex: f64) -> (f64, f64, f64) {
    atk_stat_prepared(
        WeaponKind::from_name(main),
        sub == "한손검(듀얼소드)",
        str_,
        int_,
        agi,
        dex,
    )
}
fn base_aspd(main: &str) -> f64 {
    match main {
        "한손검" => 100.0,
        "양손검" => 50.0,
        "활" => 75.0,
        "자동활" => 30.0,
        "지팡이" => 60.0,
        "마도구" => 90.0,
        "권갑" => 120.0,
        "선풍창" => 25.0,
        "발도검" => 200.0,
        "맨손" => 1000.0,
        _ => 100.0,
    }
}

fn atk_stat_prepared(
    main: WeaponKind,
    sub_dual: bool,
    str_: f64,
    int_: f64,
    agi: f64,
    dex: f64,
) -> (f64, f64, f64) {
    match main {
        WeaponKind::Sword if sub_dual => (str_ + agi + dex * 2.0, int_ * 3.0 + dex, 0.0),
        WeaponKind::Sword => (str_ * 2.0 + dex * 2.0, int_ * 3.0 + dex, 0.0),
        WeaponKind::TwoHand => (str_ * 3.0 + dex, int_ * 3.0 + dex, 0.0),
        WeaponKind::Bow => (str_ + dex * 3.0, int_ * 3.0 + dex, 0.0),
        WeaponKind::Bowgun => (dex * 4.0, int_ * 3.0 + dex, 0.0),
        WeaponKind::Staff => (str_ * 3.0 + int_, int_ * 4.0 + dex, 1.0),
        WeaponKind::Device => (int_ * 2.0 + agi * 2.0, int_ * 4.0 + dex, 1.0),
        // External evidence: docs/verification/weapon-stat-recommendation-audit-2026-09-09.md
        WeaponKind::Knuckle => (agi * 2.0 + dex * 0.5, int_ * 4.0 + dex, 0.5),
        WeaponKind::Halberd => (
            floor(str_ * 2.5) + floor(agi * 1.5),
            int_ * 2.0 + agi + dex,
            0.0,
        ),
        WeaponKind::Katana => (floor(dex * 2.5) + floor(str_ * 1.5), int_ * 1.5 + dex, 0.0),
        _ => (str_, int_ * 3.0 + dex, 0.0),
    }
}

fn stat_aspd_prepared(
    main: WeaponKind,
    sub_dual: bool,
    str_: f64,
    int_: f64,
    agi: f64,
    dex: f64,
) -> f64 {
    if main == WeaponKind::Sword || sub_dual {
        (agi * 42.0 + str_ * 2.0) / 10.0
    } else {
        match main {
            WeaponKind::TwoHand => (agi * 21.0 + str_ * 2.0) / 10.0,
            WeaponKind::Bow => (agi * 31.0 + dex * 2.0) / 10.0,
            WeaponKind::Bowgun => (agi * 22.0 + dex * 2.0) / 10.0,
            WeaponKind::Staff => (agi * 18.0 + int_ * 2.0) / 10.0,
            WeaponKind::Device => (agi * 40.0 + int_ * 2.0) / 10.0,
            WeaponKind::Knuckle => (agi * 46.0 + dex + str_) / 10.0,
            WeaponKind::Halberd => (agi * 35.0 + str_ * 2.0) / 10.0,
            WeaponKind::Katana => (agi * 39.0 + dex * 3.0) / 10.0,
            _ => agi * 96.0 / 10.0,
        }
    }
}

fn physical_stability_prepared(main: WeaponKind, str_: f64, dex: f64) -> f64 {
    match main {
        WeaponKind::Sword | WeaponKind::Bow => (str_ + dex * 3.0) / 40.0,
        WeaponKind::TwoHand | WeaponKind::Device => dex / 10.0,
        WeaponKind::Bowgun | WeaponKind::Staff => str_ / 20.0,
        WeaponKind::Knuckle => dex / 40.0,
        WeaponKind::Halberd => (str_ + dex) / 40.0,
        WeaponKind::Katana => (str_ * 3.0 + dex) / 40.0,
        _ => 0.0,
    }
}

#[allow(dead_code)] // Each development bridge uses one of the two input forms.
pub fn evaluate_summary(
    base: &Value,
    stats: &Value,
) -> Result<CrystaOptimizationNativeSummary, String> {
    if !base.is_object() || !stats.is_object() {
        return Err("CrystaOptimization native summary requires object inputs".to_string());
    }
    evaluate_summary_from_lookup(base, stats)
}

/// Native CrystaOptimization search keeps aggregate stats in this compact map form.  This
/// entry point deliberately avoids constructing a serde_json object for every
/// bound and leaf evaluation.
#[allow(dead_code)] // The summary bridge intentionally does not link the solver.
pub fn evaluate_summary_from_map<C: ContextLookup>(
    base: &C,
    stats: &BTreeMap<String, f64>,
) -> Result<CrystaOptimizationNativeSummary, String> {
    if !base.is_object() {
        return Err(
            "CrystaOptimization native summary requires an object base context".to_string(),
        );
    }
    evaluate_summary_from_lookup(base, &DenseStats::new(stats))
}

fn evaluate_summary_from_lookup<T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
) -> Result<CrystaOptimizationNativeSummary, String> {
    Ok(evaluate_filtered_summary(base, stats, |_, _| true)?.expect("unfiltered summary"))
}

/// Reject utility-infeasible leaves/envelopes before damage evaluation.
/// Calls the predicate as each value is ready, in order: HP, MP, AMPR before
/// dual, normal-attack critical rate, ASPD. Rejection skips subsequent stages.
#[allow(dead_code)] // The summary-only bridge does not link the solver.
pub fn evaluate_feasible_summary<C: ContextLookup>(
    base: &C,
    stats: &NativeStats,
    accepts: impl FnMut(usize, i64) -> bool,
) -> Result<Option<CrystaOptimizationNativeSummary>, String> {
    if !base.is_object() {
        return Err("CrystaOptimization native summary requires an object base context".into());
    }
    evaluate_filtered_summary(base, stats, accepts)
}

/// Goal coordinates are distinct from raw stats used by damage calculations.
#[allow(dead_code)] // Full raw-summary reference for the score-only search path.
pub fn evaluate_utility_feasible_summary<C: ContextLookup>(
    base: &C,
    stats: &NativeStats,
    accepts: impl FnMut(usize, f64) -> bool,
) -> Result<Option<CrystaOptimizationNativeSummary>, String> {
    evaluate_utility_filtered::<true, _, C>(base, stats, accepts, None)
}

#[allow(dead_code)] // Raw-summary-only bridge does not consume search scores.
pub struct CrystaOptimizationNativeScore {
    pub optimization_damage_factor: f64,
}

pub fn evaluate_utility_feasible_score<C: ContextLookup>(
    base: &C,
    stats: &NativeStats,
    accepts: impl FnMut(usize, f64) -> bool,
) -> Result<Option<CrystaOptimizationNativeScore>, String> {
    Ok(
        evaluate_utility_filtered::<false, _, C>(base, stats, accepts, None)?.map(|summary| {
            CrystaOptimizationNativeScore {
                optimization_damage_factor: summary.optimization_damage_factor,
            }
        }),
    )
}

/// Avoid materializing a final package/utility-envelope sum, including when
/// the utility stages reject before most coordinates are ever read.
#[allow(dead_code)] // The raw-summary bridge does not link the solver.
pub fn evaluate_utility_feasible_score_from_sum<C: ContextLookup>(
    base: &C,
    left: &NativeStats,
    right: &NativeStats,
    accepts: impl FnMut(usize, f64) -> bool,
) -> Result<Option<CrystaOptimizationNativeScore>, String> {
    Ok(
        evaluate_utility_filtered::<false, _, C>(
            base,
            &SummedStats { left, right },
            accepts,
            None,
        )?
        .map(|summary| CrystaOptimizationNativeScore {
            optimization_damage_factor: summary.optimization_damage_factor,
        }),
    )
}

fn evaluate_utility_filtered<const RAW_AMPR: bool, T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    mut accepts: impl FnMut(usize, f64) -> bool,
    caps: Option<&[f64; 6]>,
) -> Result<Option<CrystaOptimizationNativeSummary>, String> {
    if !base.is_object() {
        return Err("CrystaOptimization native summary requires an object base context".into());
    }
    let mut mp = 0.0;
    // Stage 2 always derives the goal AMPR here; its raw argument is unused.
    evaluate_filtered_summary_impl::<RAW_AMPR, _, _>(
        base,
        stats,
        |index, raw| {
            let value = match index {
                1 => {
                    mp = raw as f64;
                    mp.min(
                        if number_at(base, ContextKey::field_godspeed_wield_level) > 0.0 {
                            2300.0
                        } else {
                            2000.0
                        },
                    )
                }
                2 => {
                    let ampr = floor(10.0 + mp.min(2000.0) / 100.0)
                        + number_at(base, ContextKey::field_ampr_f)
                        + stat_at(stats, StatKey::AMPR);
                    match base.prepared_effects() {
                        Some(effects) => effects.ampr(ampr),
                        None => resolve_normal_attack_ampr(
                            ampr,
                            base.get_at(ContextKey::field_normal_attack_ampr_profile),
                        ),
                    }
                }
                3 => (raw as f64).clamp(0.0, 100.0),
                4 if raw >= 1000 => {
                    let motion = (floor((raw as f64 - 1000.0) / 180.0).min(50.0)
                        + number_at(base, ContextKey::field_motion_speed)
                        + stat_at(stats, StatKey::MOTIONSPEED))
                    .min(50.0);
                    1000.0 + 180.0 * motion.max(0.0)
                }
                _ => raw as f64,
            };
            accepts(index, value)
        },
        caps,
        EvaluationOutput::None,
    )
}

/// Certified derived caps are used only by the solver's monotone envelope path.
#[allow(dead_code)]
pub fn evaluate_utility_feasible_bound<C: ContextLookup>(
    base: &C,
    stats: &NativeStats,
    caps: &[f64; 6],
    accepts: impl FnMut(usize, f64) -> bool,
) -> Result<Option<CrystaOptimizationNativeScore>, String> {
    Ok(
        evaluate_utility_filtered::<false, _, C>(base, stats, accepts, Some(caps))?.map(
            |summary| CrystaOptimizationNativeScore {
                optimization_damage_factor: summary.optimization_damage_factor,
            },
        ),
    )
}

#[allow(dead_code)] // Standalone raw-summary bridges do not use goal bounds.
pub fn utility_values<C: ContextLookup>(base: &C, stats: &NativeStats) -> Result<[f64; 5], String> {
    let mut values = [0.0; 5];
    evaluate_utility_feasible_score(base, stats, |index, value| {
        values[index] = value;
        index != 4 // Utility-only probe: do not calculate damage.
    })?;
    Ok(values)
}

#[allow(dead_code)] // Summary-only bridges do not prepare search bounds.
pub fn normal_attack_crit_base(base: &PreparedContext) -> f64 {
    base.invariant(Invariant::BaseCrit)
}

fn candidate_stat_up<T: StatLookup, C: ContextLookup>(base: &C, stats: &T, magic: bool) -> f64 {
    let keys = if magic {
        [
            StatKey::MATK_UP_STR,
            StatKey::MATK_UP_INT,
            StatKey::MATK_UP_VIT,
            StatKey::MATK_UP_AGI,
            StatKey::MATK_UP_DEX,
        ]
    } else {
        [
            StatKey::ATK_UP_STR,
            StatKey::ATK_UP_INT,
            StatKey::ATK_UP_VIT,
            StatKey::ATK_UP_AGI,
            StatKey::ATK_UP_DEX,
        ]
    };
    let values = keys.map(|key| stat_at(stats, key));
    if values.iter().all(|v| *v == 0.0) {
        return base.invariant(if magic {
            Invariant::MatkUp
        } else {
            Invariant::AtkUp
        });
    }
    let rate_fields = if magic {
        [
            ContextKey::field_matk_up_s_t_r,
            ContextKey::field_matk_up_i_n_t,
            ContextKey::field_matk_up_v_i_t,
            ContextKey::field_matk_up_a_g_i,
            ContextKey::field_matk_up_d_e_x,
        ]
    } else {
        [
            ContextKey::field_atk_up_s_t_r,
            ContextKey::field_atk_up_i_n_t,
            ContextKey::field_atk_up_v_i_t,
            ContextKey::field_atk_up_a_g_i,
            ContextKey::field_atk_up_d_e_x,
        ]
    };
    let rates = rate_fields.map(|field| number_at(base, field));
    proportional_attack(base, std::array::from_fn(|i| rates[i] + values[i]))
}

/// Display-derived supply coordinates; these are not extra optimization goals.
#[allow(dead_code)]
pub fn candidate_cast_metrics(base: &PreparedContext, stats: &NativeStats) -> [f64; 2] {
    let agi = stat_total(
        base,
        stats,
        ContextKey::field_agi_base,
        ContextKey::field_agi_p,
        ContextKey::field_agi_f,
        StatKey::AGIP,
        StatKey::AGI,
    );
    let dex = stat_total(
        base,
        stats,
        ContextKey::field_dex_base,
        ContextKey::field_dex_p,
        ContextKey::field_dex_f,
        StatKey::DEXP,
        StatKey::DEX,
    );
    let cspd = floor_percent(
        number(base, "level")
            + floor_ratio(agi, 116.0, 100.0, 0.0)
            + floor_ratio(dex, 294.0, 100.0, 0.0),
        number(base, "cspdP") + stats.number_at(StatKey::CSPD_P),
        0.0,
    ) + number(base, "cspdF")
        + stats.number_at(StatKey::CSPD);
    let reduction = if cspd <= 1000.0 {
        cspd / 20.0
    } else {
        50.0 + (cspd - 1000.0) / 180.0
    };
    [
        cspd,
        (floor(reduction.min(100.0))
            + number(base, "castRed")
            + stats.number_at(StatKey::CAST_RED))
        .min(100.0),
    ]
}

fn evaluate_filtered_summary<T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    accepts: impl FnMut(usize, i64) -> bool,
) -> Result<Option<CrystaOptimizationNativeSummary>, String> {
    evaluate_filtered_summary_impl::<true, T, C>(base, stats, accepts, None, EvaluationOutput::None)
}

enum EvaluationOutput<'a> {
    None,
    Full(&'a mut Value),
    Summary(&'a mut Value),
    Supply(&'a mut Value),
}
fn evaluate_filtered_summary_impl<const RAW_AMPR: bool, T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    mut accepts: impl FnMut(usize, i64) -> bool,
    caps: Option<&[f64; 6]>,
    mut output: EvaluationOutput<'_>,
) -> Result<Option<CrystaOptimizationNativeSummary>, String> {
    let plan = base.evaluation_plan().unwrap_or_else(|| {
        let mut plan = EvaluationPlan::new(base);
        // Keep the uncached Value path as a full-computation reference.
        plan.need_atk = true;
        plan.need_matk = true;
        plan
    });
    let vit = stat_total(
        base,
        stats,
        ContextKey::field_vit_base,
        ContextKey::field_vit_p,
        ContextKey::field_vit_f,
        StatKey::VITP,
        StatKey::VIT,
    );
    let level = number_at(base, ContextKey::field_level);
    let base_max_hp = floor_ratio(vit * 100.0 + 2241.0, level, 300.0, 93.0);
    let hp_percent = number_at(base, ContextKey::field_max_hp_p) + stat_at(stats, StatKey::MAXHPP);
    let hp_flat = number_at(base, ContextKey::field_max_hp_f) + stat_at(stats, StatKey::MAXHP);
    // The Native integer DTO floors flat in-stage; full UI values retain fractional flat.
    let max_hp_full = if matches!(output, EvaluationOutput::None) {
        floor_percent(base_max_hp, hp_percent, hp_flat)
    } else {
        floor_percent(base_max_hp, hp_percent, 0.0) + hp_flat
    }
    .clamp(0.0, 99999.0);
    let max_hp = max_hp_full as i64;
    if !accepts(0, max_hp) {
        return Ok(None);
    }
    let int_ = stat_total(
        base,
        stats,
        ContextKey::field_int_base,
        ContextKey::field_int_p,
        ContextKey::field_int_f,
        StatKey::INTP,
        StatKey::INT,
    );
    let max_mp = floor_ratio(
        int_,
        1.0,
        10.0,
        base.invariant(Invariant::MpFlat) + stat_at(stats, StatKey::MAXMP),
    )
    .max(0.0) as i64;
    if !accepts(1, max_mp) {
        return Ok(None);
    }
    let ampr_before_dual = if RAW_AMPR {
        let base_ampr = floor(10.0 + max_mp as f64 / 100.0);
        let ampr = floor_percent(
            base_ampr,
            number_at(base, ContextKey::field_ampr_p) + stat_at(stats, StatKey::AMPRP),
            0.0,
        ) + number_at(base, ContextKey::field_ampr_f)
            + stat_at(stats, StatKey::AMPR);
        (match base.prepared_effects() {
            Some(effects) => effects.ampr(ampr),
            None => resolve_normal_attack_ampr(
                ampr,
                base.get_at(ContextKey::field_normal_attack_ampr_profile),
            ),
        }) as i64
    } else {
        // Never exposed as a raw summary: the score-only entry point discards
        // this field, and its utility callback independently computes AMPR.
        0
    };

    if !accepts(2, ampr_before_dual) {
        return Ok(None);
    }

    let base_crit = base.invariant(Invariant::BaseCrit);
    let normal_raw = floor_percent(
        base_crit,
        number_at(base, ContextKey::field_crit_p) + stat_at(stats, StatKey::CRITP),
        0.0,
    ) + number_at(base, ContextKey::field_crit_f)
        + stat_at(stats, StatKey::CRIT);
    let normal_attack_crit_full = normal_raw - number_at(base, ContextKey::field_boss_crit_resist);
    let normal_attack_crit = normal_attack_crit_full as i64;
    if !accepts(3, normal_attack_crit) {
        return Ok(None);
    }
    let str_ = stat_total(
        base,
        stats,
        ContextKey::field_str_base,
        ContextKey::field_str_p,
        ContextKey::field_str_f,
        StatKey::STRP,
        StatKey::STR,
    );
    let dex = stat_total(
        base,
        stats,
        ContextKey::field_dex_base,
        ContextKey::field_dex_p,
        ContextKey::field_dex_f,
        StatKey::DEXP,
        StatKey::DEX,
    );
    let agi = stat_total(
        base,
        stats,
        ContextKey::field_agi_base,
        ContextKey::field_agi_p,
        ContextKey::field_agi_f,
        StatKey::AGIP,
        StatKey::AGI,
    );
    let armor_aspd = plan.armor_aspd;
    let final_aspd_full = floor_percent(
        plan.weapon_aspd
            + floor(stat_aspd_prepared(
                plan.weapon,
                plan.sub_dual,
                str_,
                int_,
                agi,
                dex,
            ))
            + level,
        number_at(base, ContextKey::field_aspd_p) + stat_at(stats, StatKey::ASPD_P) + armor_aspd,
        0.0,
    ) + number_at(base, ContextKey::field_aspd_f)
        + stat_at(stats, StatKey::ASPD);
    let final_aspd = final_aspd_full as i64;
    if !accepts(4, final_aspd) {
        return Ok(None);
    }

    let mut atk_p = number_at(base, ContextKey::field_atk_p) + stat_at(stats, StatKey::ATKP);
    let mut atk_f = number_at(base, ContextKey::field_atk_f) + stat_at(stats, StatKey::ATK);
    let mut base_wpn_atk_f = number_at(base, ContextKey::field_base_wpn_atk_f);
    let mut unsheathe_p =
        number_at(base, ContextKey::field_unsheathe_p) + stat_at(stats, StatKey::UNSHEATHEP);
    let mut unsheathe_f =
        number_at(base, ContextKey::field_unsheathe_f) + stat_at(stats, StatKey::UNSHEATHE);
    let rates: std::borrow::Cow<'_, [f64]> = match base.prepared_effects() {
        Some(effects) => std::borrow::Cow::Borrowed(&effects.conversions),
        None => std::borrow::Cow::Owned(
            array(base, "activeBuildConversions")
                .iter()
                .filter(|v| text(*v, "conversion") == "unsheatheToAtk")
                .map(|v| number(v, "value"))
                .collect(),
        ),
    };
    for &rate in rates.iter() {
        let converted_p = floor_ratio(unsheathe_p, rate, 1.0, 0.0);
        let converted_f = floor_ratio(unsheathe_f, rate, 1.0, 0.0);
        unsheathe_p = 0.0;
        unsheathe_f = 0.0;
        atk_p += converted_p;
        base_wpn_atk_f += converted_p;
        atk_f += converted_f;
    }
    let main = text_at(base, ContextKey::field_main_type);
    let sub = text_at(base, ContextKey::field_sub_type);
    let watkp = number_at(base, ContextKey::field_watk_p) + stat_at(stats, StatKey::WATKP);
    let watk = number_at(base, ContextKey::field_watk_f) + stat_at(stats, StatKey::WATK);
    let effective_weapon = number_at(base, ContextKey::field_wpn_atk) + base_wpn_atk_f;
    let main_weapon = effective_weapon + floor_ratio(effective_weapon, watkp, 100.0, 0.0) + watk;
    let mut weapon = main_weapon
        + floor_ratio(
            effective_weapon,
            base.invariant(Invariant::MainRefineSquared),
            100.0,
            0.0,
        )
        + number_at(base, ContextKey::field_wpn_refine);
    if plan.arrow {
        weapon += floor(number_at(base, ContextKey::field_sub_atk));
    }
    let (stat_atk, stat_matk, matk_ratio) =
        atk_stat_prepared(plan.weapon, plan.sub_dual, str_, int_, agi, dex);
    let atk_up = candidate_stat_up(base, stats, false);
    let matk_up = candidate_stat_up(base, stats, true);
    if plan.sub_device {
        atk_p -= 15.0;
    }
    let mut final_atk = if plan.need_atk {
        floor_percent(weapon + stat_atk + level + atk_up, atk_p, 0.0) + atk_f
    } else {
        0.0
    };
    let mut final_matk = if plan.need_matk {
        floor_percent(
            floor_ratio(weapon, matk_ratio, 1.0, 0.0) + stat_matk + level + matk_up,
            number_at(base, ContextKey::field_matk_p) + stat_at(stats, StatKey::MATKP),
            0.0,
        ) + number_at(base, ContextKey::field_matk_f)
            + stat_at(stats, StatKey::MATK)
    } else {
        0.0
    };
    let conversion_level = number_at(base, ContextKey::field_conversion_level);
    if plan.need_matk && plan.conversion {
        let mut conversion_add = floor_ratio(
            weapon,
            base.invariant(Invariant::ConversionSquared),
            100.0,
            0.0,
        );
        let mut conversion_int = 0.0;
        if main == "권갑" {
            conversion_add = floor(conversion_add / 2.0);
        } else {
            conversion_int = floor_ratio(int_, conversion_level, 10.0, 0.0);
        }
        final_matk += floor(conversion_add) + floor(conversion_int);
    }
    let mut full_sub_pre_atk = 0.0;
    let mut full_sub_atk = 0.0;
    let mut full_sub_stab = 0.0;
    if plan.need_atk && plan.dual {
        let sub_weapon = number_at(base, ContextKey::field_sub_atk)
            + floor_ratio(
                number_at(base, ContextKey::field_sub_atk),
                watkp,
                100.0,
                0.0,
            )
            + floor_ratio(
                number_at(base, ContextKey::field_sub_atk),
                base.invariant(Invariant::SubRefineSquared),
                200.0,
                0.0,
            )
            + number_at(base, ContextKey::field_sub_refine)
            + watk;
        full_sub_pre_atk = sub_weapon + floor(str_ + agi * 3.0) + level;
        let sub_atk = floor_percent(full_sub_pre_atk, atk_p, 0.0) + atk_f;
        let sub_stab = (floor(number_at(base, ContextKey::field_sub_stab) * 0.5)
            + floor_ratio(str_, 6.0, 100.0, 0.0)
            + floor_ratio(agi, 4.0, 100.0, 0.0)
            + number_at(base, ContextKey::field_stability)
            + stat_at(stats, StatKey::STABILITY))
        .min(100.0);
        full_sub_atk = sub_atk;
        full_sub_stab = sub_stab;
        final_atk += floor_ratio(sub_atk, sub_stab, 100.0, 0.0);
    }
    if let EvaluationOutput::Supply(result) = &mut output {
        **result = serde_json::json!({
            "STR":number(base,"strBase"),"DEX":number(base,"dexBase"),"AGI":number(base,"agiBase"),"INT":number(base,"intBase"),"VIT":number(base,"vitBase"),
            "CRIT":base_crit,"CDMG":if str_>=agi {150.0+floor(str_/5.0)} else {150.0+floor((str_+agi)/10.0)},"MAXHP":base_max_hp,
            "ASPD":plan.weapon_aspd+floor(stat_aspd_prepared(plan.weapon,plan.sub_dual,str_,int_,agi,dex))+level,
            "CSPD":level+floor_ratio(agi,116.0,100.0,0.0)+floor_ratio(dex,294.0,100.0,0.0),
            "ATK":if plan.dual {vec![weapon+stat_atk+level+atk_up,full_sub_pre_atk]}else{vec![weapon+stat_atk+level+atk_up]},
            "MATK":floor_ratio(weapon,matk_ratio,1.0,0.0)+stat_matk+level+matk_up,
            "WATK":if plan.dual {vec![effective_weapon,number(base,"subAtk")]}else{vec![effective_weapon]}
        });
        return Ok(None);
    }
    let mut cdmg = floor_percent(
        if str_ >= agi {
            150.0 + floor(str_ / 5.0)
        } else {
            150.0 + floor((str_ + agi) / 10.0)
        },
        number_at(base, ContextKey::field_cdmg_p) + stat_at(stats, StatKey::CDMGP),
        0.0,
    ) + number_at(base, ContextKey::field_cdmg_f)
        + stat_at(stats, StatKey::CDMG);
    if cdmg > 300.0 {
        cdmg = 300.0 + floor((cdmg - 300.0) / 2.0);
    }
    let critical_multiplier = base
        .get_at(ContextKey::field_critical_chance_multiplier)
        .and_then(Value::as_f64)
        .unwrap_or(1.0);
    let mut final_crit = floor_ratio(
        normal_raw + number_at(base, ContextKey::field_critical_chance_bonus),
        critical_multiplier,
        1.0,
        0.0,
    );
    if let Some(fixed) = base
        .get_at(ContextKey::field_fixed_critical_chance)
        .and_then(Value::as_f64)
    {
        if fixed.is_finite() {
            final_crit = fixed;
        }
    }
    if number_at(base, ContextKey::field_minimum_critical_damage) != 0.0 {
        cdmg = cdmg.max(number_at(base, ContextKey::field_minimum_critical_damage));
    }
    let mut stab = (number_at(base, ContextKey::field_wpn_stab)
        + number_at(base, ContextKey::field_stability)
        + stat_at(stats, StatKey::STABILITY)
        + number_at(base, ContextKey::field_stability_bonus)
        + floor(physical_stability_prepared(plan.weapon, str_, dex)))
    .min(100.0);
    if plan.arrow {
        stab = (stab + number_at(base, ContextKey::field_sub_stab)).min(100.0);
    }
    let is_magic = plan.is_magic;
    let awakening = flag_at(base, ContextKey::field_element_awakening)
        || stat_at(stats, StatKey::ELEM_AWAKENING) > 0.0;
    let magic_element = flag_at(base, ContextKey::field_magic_element)
        || stat_at(stats, StatKey::MAGIC_ELEMENT) > 0.0;
    let mut weapon_element = number_at(base, ContextKey::field_weapon_element);
    let sub_element = number_at(base, ContextKey::field_sub_weapon_element);
    if plan.arrow && sub_element != 0.0 {
        weapon_element = sub_element;
    }
    let attack_element = text_at(base, ContextKey::field_attack_element);
    let inherits_weapon_element =
        attack_element.is_empty() || attack_element == "none" || attack_element == "weapon";
    let effective_attack_element = if inherits_weapon_element {
        weapon_element
    } else {
        match attack_element {
            "fire" => 1.0,
            "water" => 2.0,
            "wind" => 3.0,
            "earth" => 4.0,
            "light" => 5.0,
            "dark" => 6.0,
            "neutral" | "normal" => 7.0,
            "mana" => 8.0,
            "targetAdvantage" => match number_at(base, ContextKey::field_target_element) {
                1.0 => 2.0,
                2.0 => 3.0,
                3.0 => 4.0,
                4.0 => 1.0,
                5.0 => 6.0,
                6.0 => 5.0,
                _ => 0.0,
            },
            _ => 0.0,
        }
    };
    let target_element = number_at(base, ContextKey::field_target_element);
    let weak_target = match effective_attack_element {
        1.0 => 4.0,
        2.0 => 1.0,
        3.0 => 2.0,
        4.0 => 3.0,
        5.0 => 6.0,
        6.0 => 5.0,
        _ => 0.0,
    };
    let attacks_weakness = awakening
        || attack_element == "weakness"
        || (weak_target != 0.0 && weak_target == target_element);
    let weapon_magic_element = is_magic
        && (attacks_weakness
            || (matches!(plan.weapon, WeaponKind::Staff | WeaponKind::Device)
                && effective_attack_element != 0.0
                && effective_attack_element != 7.0));
    let phys_stab = stab;
    let mut elem = number_at(base, ContextKey::field_elem_p) + stat_at(stats, StatKey::ELEM_P);
    let target_bonus = match target_element {
        1.0 => Some((ContextKey::field_fire_dmg, StatKey::FIRE_DMG)),
        2.0 => Some((ContextKey::field_water_dmg, StatKey::WATER_DMG)),
        3.0 => Some((ContextKey::field_wind_dmg, StatKey::WIND_DMG)),
        4.0 => Some((ContextKey::field_earth_dmg, StatKey::EARTH_DMG)),
        5.0 => Some((ContextKey::field_light_dmg, StatKey::LIGHT_DMG)),
        6.0 => Some((ContextKey::field_dark_dmg, StatKey::DARK_DMG)),
        7.0 => Some((ContextKey::field_neutral_dmg, StatKey::NEUTRAL_DMG)),
        _ => None,
    };
    if let Some((field, stat)) = target_bonus {
        elem += number_at(base, field) + stat_at(stats, stat);
    }
    if attacks_weakness {
        elem += 25.0;
    }
    if awakening || magic_element || weapon_magic_element {
        elem += floor(number_at(base, ContextKey::field_int_base) / 10.0);
    }
    let mut final_cdmg = cdmg;
    let mut final_crit_rate = final_crit;
    if is_magic {
        let spell = 2.5 * number_at(base, ContextKey::field_spell_burst_level);
        let weaken = if flag_at(base, ContextKey::field_target_weakened)
            && (main == "지팡이" || main == "마도구" || attacks_weakness)
        {
            50.0
        } else {
            0.0
        };
        let mut crit_reflect = spell + weaken;
        if flag_at(base, ContextKey::field_target_weakened)
            && flag_at(base, ContextKey::field_dual_bringer_active)
            && sub == "마도구"
            && str_ >= int_
        {
            crit_reflect += 2.5 * number_at(base, ContextKey::field_dual_bringer_level);
        }
        final_crit_rate = floor_ratio(final_crit, crit_reflect, 100.0, 0.0);
        let mut cdmg_reflect = 50.0 + spell;
        if flag_at(base, ContextKey::field_dual_bringer_active) && int_ > str_ {
            cdmg_reflect += 2.5 * number_at(base, ContextKey::field_dual_bringer_level);
        }
        final_cdmg = 100.0 + floor_ratio(cdmg - 100.0, cdmg_reflect, 100.0, 0.0);
        stab = (floor(50.0 + stab / 2.0)).min(100.0);
    }
    if flag_at(base, ContextKey::field_chk_guaranteed_crit) {
        final_crit_rate = 1000.0;
    }
    if flag_at(base, ContextKey::field_no_critical) {
        final_crit_rate = 0.0;
    }
    let target_def = if is_magic {
        number_at(base, ContextKey::field_boss_mdef)
    } else {
        number_at(base, ContextKey::field_boss_def)
    };
    let pierce = if is_magic {
        number_at(base, ContextKey::field_mag_pierce)
            + stat_at(stats, StatKey::MAG_PIERCE)
            + number_at(base, ContextKey::field_magic_pierce_skill_bonus)
    } else {
        number_at(base, ContextKey::field_phys_pierce)
            + stat_at(stats, StatKey::PHYS_PIERCE)
            + number_at(base, ContextKey::field_physical_pierce_skill_bonus)
    };
    let mut effective_def = floor_percent(target_def, -pierce, 0.0);
    if (is_magic && flag_at(base, ContextKey::field_ignore_mdef))
        || (!is_magic && flag_at(base, ContextKey::field_ignore_defense))
    {
        effective_def = 0.0;
    } else if is_magic && flag_at(base, ContextKey::field_half_mdef_ignored) {
        effective_def = floor(effective_def / 2.0);
    }
    effective_def = effective_def.max(0.0);
    let [mut final_skill_mult, passive_damage_mult, active_damage_mult, combo_damage_mult] =
        match base.prepared_effects() {
            Some(effects) => effects.layers,
            None => {
                let layers = base
                    .get_at(ContextKey::field_damage_multiplier_layers)
                    .unwrap_or(&Value::Null);
                [
                    finite_number(
                        layers,
                        "skill",
                        number_at(base, ContextKey::field_skill_mult),
                    ),
                    finite_number(layers, "passive", 1.0),
                    finite_number(layers, "active", 1.0),
                    finite_number(layers, "combo", 1.0),
                ]
            }
        };
    let mut final_skill_const = number_at(base, ContextKey::field_skill_const);
    if let Some(effects) = base.prepared_effects() {
        let totals = [str_, int_, vit, agi, dex];
        for term in &effects.skill_terms {
            let value = match term.source {
                SkillSource::Fixed(value) => value,
                SkillSource::Total(index) => totals[index],
            };
            if term.to_mult {
                final_skill_mult += value * term.ratio;
            } else {
                final_skill_const += value * term.ratio;
            }
        }
    } else {
        for skill_stat in array(base, "skillStats") {
            let value = match text(skill_stat, "stat") {
                "STR" => number_at(base, ContextKey::field_str_base),
                "INT" => number_at(base, ContextKey::field_int_base),
                "VIT" => number_at(base, ContextKey::field_vit_base),
                "AGI" => number_at(base, ContextKey::field_agi_base),
                "DEX" => number_at(base, ContextKey::field_dex_base),
                "totalSTR" => str_,
                "totalINT" => int_,
                "totalVIT" => vit,
                "totalAGI" => agi,
                "totalDEX" => dex,
                _ => 0.0,
            };
            if text(skill_stat, "target") == "mult" {
                final_skill_mult += value * number(skill_stat, "ratio");
            } else if text(skill_stat, "target") == "const" {
                final_skill_const += value * number(skill_stat, "ratio");
            }
        }
    }
    let base_power = match plan.power {
        PowerMode::Sum => final_atk + final_matk,
        PowerMode::Higher => final_atk.max(final_matk),
        PowerMode::Atk => final_atk,
        PowerMode::WizardBlend => final_atk * 0.25 + final_matk * 0.75,
        PowerMode::Matk => final_matk,
    };
    let mut raw = floor_ratio(
        base_power + level - number_at(base, ContextKey::field_boss_level),
        base.invariant(if is_magic {
            Invariant::MagicResistance
        } else {
            Invariant::PhysResistance
        }),
        1.0,
        0.0,
    );
    if flag_at(base, ContextKey::field_chk_is_unsheathe) {
        raw += unsheathe_f;
    }
    raw += final_skill_const - effective_def;
    let pierced = raw > 0.0;
    raw = raw.max(1.0);
    let mut range = if flag_at(base, ContextKey::field_use_higher_range_damage) {
        (number_at(base, ContextKey::field_srw) + stat_at(stats, StatKey::SRW))
            .max(number_at(base, ContextKey::field_lrw) + stat_at(stats, StatKey::LRW))
    } else if text_at(base, ContextKey::field_range_type) == "SHORT" {
        number_at(base, ContextKey::field_srw) + stat_at(stats, StatKey::SRW)
    } else {
        number_at(base, ContextKey::field_lrw) + stat_at(stats, StatKey::LRW)
    };
    let chance =
        (final_crit_rate - number_at(base, ContextKey::field_boss_crit_resist)).clamp(0.0, 100.0);
    if let Some(caps) = caps {
        raw = raw.min(caps[0]);
        final_cdmg = final_cdmg.min(caps[1]);
        stab = stab.min(caps[2]);
        elem = elem.min(caps[3]);
        final_skill_mult = final_skill_mult.min(caps[4]);
        range = range.min(caps[5]);
    }
    let mut damage = floor_ratio(raw, 10000.0 + chance * (final_cdmg - 100.0), 10000.0, 0.0);
    damage = floor_percent(damage, elem, 0.0);
    damage = floor_layer(base, damage, 0, final_skill_mult);
    damage = floor_percent(
        damage,
        if flag_at(base, ContextKey::field_chk_is_unsheathe) {
            unsheathe_p
        } else {
            0.0
        },
        0.0,
    );
    damage = floor_ratio(damage, 100.0 + stab, 200.0, 0.0);
    damage = floor_layer(base, damage, 1, passive_damage_mult);
    damage = floor_percent(damage, range, 0.0);
    damage = floor_layer(base, damage, 2, active_damage_mult);
    damage = floor_percent(
        damage,
        number_at(base, ContextKey::field_damage_p) + stat_at(stats, StatKey::DAMAGE_P),
        0.0,
    );
    damage = floor_layer(base, damage, 3, combo_damage_mult);
    let summary_output = matches!(output, EvaluationOutput::Summary(_));
    if let EvaluationOutput::Full(result) | EvaluationOutput::Summary(result) = &mut output {
        let cspd_base =
            level + floor_ratio(agi, 116.0, 100.0, 0.0) + floor_ratio(dex, 294.0, 100.0, 0.0);
        let cspd = floor_percent(cspd_base, number(base, "cspdP"), 0.0) + number(base, "cspdF");
        let motion_bonus = if final_aspd_full >= 1000.0 {
            (final_aspd_full - 1000.0) / 180.0
        } else {
            0.0
        };
        let motion = (motion_bonus.floor().min(50.0) + number(base, "motionSpeed")).min(50.0);
        let cast = (floor(if cspd <= 1000.0 {
            cspd / 20.0
        } else {
            50.0 + (cspd - 1000.0) / 180.0
        })
        .min(100.0)
            + number(base, "castRed"))
        .min(100.0);
        let utility = serde_json::json!([
            max_hp_full,
            (max_mp as f64).min(if number(base, "godspeedWieldLevel") > 0.0 {
                2300.0
            } else {
                2000.0
            }),
            resolve_normal_attack_ampr(
                floor(10.0 + (max_mp as f64).min(2000.0) / 100.0) + number(base, "amprF"),
                base.context_get("normalAttackAmprProfile")
            ),
            normal_attack_crit_full.clamp(0.0, 100.0),
            if final_aspd_full < 1000.0 {
                final_aspd_full
            } else {
                1000.0 + 180.0 * motion.max(0.0)
            }
        ]);
        if summary_output {
            **result = serde_json::json!({"ctx":{"statDiagnostics":base.context_get("statDiagnostics").cloned().unwrap_or(serde_json::json!([]))},"optimizationUtilityValues":utility,"finalMaxHP":max_hp_full,"finalMaxMP":max_mp,"amprBeforeDual":ampr_before_dual,"normalAttackCrit":normal_attack_crit_full,"finalASPD":final_aspd_full,"optimizationDamageFactor":damage*base.invariant(Invariant::Proc)});
        } else {
            let ampr_base = floor(10.0 + max_mp as f64 / 100.0);
            let equipment_ampr =
                floor_percent(ampr_base, number(base, "amprP"), 0.0) + number(base, "amprF");
            let ampr = full_ampr(equipment_ampr, base.context_get("normalAttackAmprProfile"));
            let proc = full_proc(base.context_get("procDamageModifiers"));
            let defense_average = (number(base, "bossDef") + number(base, "bossMdef")) / 2.0;
            let defense_ratio = if number(base, "bossLevel") > 0.0 {
                (defense_average / (number(base, "bossLevel") * 6.0)).min(0.5)
            } else {
                0.0
            };
            let resistance_average =
                (number(base, "bossPhysResist") + number(base, "bossMagResist")) / 2.0;
            let poison_sources = array(base, "poisonSources");
            let mut resistance_components = vec![number(
                base,
                if is_magic {
                    "bossMagResist"
                } else {
                    "bossPhysResist"
                },
            )];
            resistance_components.extend(
                array(base, "additionalTargetResistances")
                    .iter()
                    .map(|v| v.as_f64().unwrap_or(0.0)),
            );
            let resistance_raw: f64 = resistance_components.iter().sum();
            **result = serde_json::json!({
                "isPierced":pierced,"rawAtkBase":raw,"finalSTR":str_,"finalINT":int_,"finalAGI":agi,"finalDEX":dex,"finalVIT":vit,
                "finalATK":final_atk,"finalMATK":final_matk,"finalCDMG":final_cdmg,
                "finalCrit":if base.context_flag("chkGuaranteedCrit") {serde_json::json!("확정치명타")} else {serde_json::json!(final_crit_rate)},
                "normalAttackCrit":normal_attack_crit_full,"finalASPD":final_aspd_full,"finalCSPD":cspd,"finalStab":stab,
                "finalMaxHP":max_hp_full,"finalMaxMP":max_mp,"finalMaxMPAfterBuff":max_mp,"baseAMPR":ampr_base,"equipmentAndBuffAMPR":equipment_ampr,
                "amprBeforeNormalAttackActive":ampr["afterPassive"],"normalAttackAmprActiveCandidates":ampr["activeCandidates"],"selectedNormalAttackAmprActive":ampr["selectedActive"],
                "amprBeforeDual":ampr["final"],"finalAMPR":ampr["final"].as_f64().unwrap()*if plan.dual {2.0}else{1.0},
                "finalMotionSpeed":motion,"finalCastReduction":cast,"finalWeaponAttack":weapon,"finalSubAtk":full_sub_atk,"finalSubStab":full_sub_stab,"isDualSword":plan.dual,
                "damageFactor":damage,"optimizationDamageFactor":damage*proc["expectedMultiplier"].as_f64().unwrap(),
                "procTriggeredDamageFactor":damage*proc["triggeredMultiplier"].as_f64().unwrap(),"procExpectedDamageFactor":damage*proc["expectedMultiplier"].as_f64().unwrap(),"procDamageProfile":proc,
                "targetResistance":{"components":resistance_components,"raw":resistance_raw,"effective":resistance_raw,"multiplier":resistance_multiplier(base,is_magic)},
                "poisonDamageProfile":{"available":!poison_sources.is_empty(),"sources":poison_sources,"defenseAverage":defense_average,"defenseRatio":defense_ratio,"resistanceAverage":resistance_average,"damage":if poison_sources.is_empty(){Value::Null}else{serde_json::json!((dex+(final_atk+final_matk)*defense_ratio)*(1.0-resistance_average/100.0))}},
                "optimizationUtilityValues":utility,
                "breakdown":{"weapon":weapon,"statAtk":stat_atk,"statMatk":stat_matk,"atkUp":atk_up,"matkUp":matk_up,
                    "preAtk":weapon+stat_atk+level+atk_up,"preMatk":floor_ratio(weapon,matk_ratio,1.0,0.0)+stat_matk+level+matk_up,
                    "wpnMatkContrib":floor_ratio(weapon,matk_ratio,1.0,0.0),"conversionFlatMatk":final_matk-(floor_percent(floor_ratio(weapon,matk_ratio,1.0,0.0)+stat_matk+level+matk_up,number(base,"matkP"),0.0)+number(base,"matkF")),
                    "baseASPD":plan.weapon_aspd,"preASPD":plan.weapon_aspd+floor(stat_aspd_prepared(plan.weapon,plan.sub_dual,str_,int_,agi,dex))+level,
                    "preCSPD":cspd_base,"agiCspdTip":floor(1.16*agi),"dexCspdTip":floor(2.94*dex),"armorASPD":armor_aspd,"motionBonus":motion_bonus.min(50.0),"totalAspdP":number(base,"aspdP")+armor_aspd,"statASPD":floor(stat_aspd_prepared(plan.weapon,plan.sub_dual,str_,int_,agi,dex)),
                    "baseCrit":base_crit,"crtCorrection":floor_ratio(number(base,"crtBase"),10.0,34.0,0.0),"baseCDMG":if str_>=agi {150.0+floor(str_/5.0)} else {150.0+floor((str_+agi)/10.0)},
                    "physStab":phys_stab,"elem":elem,"baseElem":number(base,"elemP"),"targetBonus":target_bonus.map(|(field,_)|number_at(base,field)).unwrap_or(0.0),"intElemBonus":floor(number(base,"intBase")/10.0),"awakening":awakening,"magicElement":magic_element,"weaponMagicElement":weapon_magic_element,"attacksWeakness":attacks_weakness,
                    "magicCritReflect":if is_magic {2.5*number(base,"spellBurstLevel")+if base.context_flag("targetWeakened")&&(main=="지팡이"||main=="마도구"||attacks_weakness){50.0}else{0.0}+if base.context_flag("targetWeakened")&&base.context_flag("dualBringerActive")&&sub=="마도구"&&str_>=int_{2.5*number(base,"dualBringerLevel")}else{0.0}}else{0.0},
                    "magicCdmgReflect":50.0+2.5*number(base,"spellBurstLevel")+if base.context_flag("dualBringerActive")&&int_>str_{2.5*number(base,"dualBringerLevel")}else{0.0},"spellReflect":2.5*number(base,"spellBurstLevel"),"weakenReflect":base.context_flag("targetWeakened")&&(main=="지팡이"||main=="마도구"||attacks_weakness),"effectiveDef":effective_def,"skillMult":final_skill_mult,"skillConst":final_skill_const,
                    "atkP":atk_p,"atkF":atk_f,"baseWpnAtkF":base_wpn_atk_f,"unsheatheP":unsheathe_p,"unsheatheF":unsheathe_f}
            });
        }
    }
    Ok(Some(CrystaOptimizationNativeSummary {
        optimization_damage_factor: damage * base.invariant(Invariant::Proc),
        final_max_hp: max_hp,
        final_max_mp: max_mp,
        ampr_before_dual,
        normal_attack_crit,
        final_aspd,
    }))
}

#[cfg(test)]
#[path = "evaluator_tests.rs"]
mod tests;

fn full_ampr(value: f64, profile: Option<&Value>) -> Value {
    let empty = Value::Null;
    let profile = profile.unwrap_or(&empty);
    let after = array(profile, "passive")
        .iter()
        .fold(floor(value), modifier_ampr);
    let candidates: Vec<Value> = array(profile, "activeCandidates")
        .iter()
        .map(|m| {
            let mut m = m.clone();
            m["result"] = serde_json::json!(modifier_ampr(after, &m));
            m
        })
        .collect();
    let selected = candidates.iter().reduce(|a, b| {
        let av = number(a, "result");
        let bv = number(b, "result");
        let id = |v: &Value| {
            v.get("id")
                .and_then(Value::as_str)
                .unwrap_or("undefined")
                .to_owned()
        };
        if bv > av || (bv == av && id(b) < id(a)) {
            b
        } else {
            a
        }
    });
    serde_json::json!({"beforePassive":floor(value),"afterPassive":after,"activeCandidates":candidates,"selectedActive":selected,"final":selected.map(|m|number(m,"result")).unwrap_or(after)})
}
fn full_proc(modifiers: Option<&Value>) -> Value {
    let mut triggered = 1.0;
    let mut expected = 1.0;
    let sources:Vec<Value>=modifiers.and_then(Value::as_array).map(Vec::as_slice).unwrap_or(&[]).iter().map(|m|{
        let chance=number(m,"chancePercent").clamp(0.0,100.0);let mult=finite_number(m,"multiplier",1.0);
        triggered*=mult;expected*=1.0+chance/100.0*(mult-1.0);
        serde_json::json!({"source":m.get("source").filter(|v|!v.is_null()&&v.as_str()!=Some("")).cloned().unwrap_or(serde_json::json!("확률 효과")),"level":number(m,"level").max(0.0),"chancePercent":chance,"multiplier":mult,"target":m.get("target").filter(|v|!v.is_null()).cloned().unwrap_or(serde_json::json!("attack"))})
    }).collect();
    serde_json::json!({"sources":sources,"triggeredMultiplier":triggered,"expectedMultiplier":expected})
}

pub fn evaluate_context(base: &Value, summary_only: bool) -> Result<Value, String> {
    if !base.is_object() {
        return Err("object calculation context required".into());
    }
    let mut result = Value::Null;
    let output = if summary_only {
        EvaluationOutput::Summary(&mut result)
    } else {
        EvaluationOutput::Full(&mut result)
    };
    evaluate_filtered_summary_impl::<true, _, _>(
        base,
        &NativeStats::new(),
        |_, _| true,
        None,
        output,
    )?;
    if summary_only {
        return Ok(result);
    }
    let mut ctx = base.clone();
    let b = &result["breakdown"];
    let conversion = array(base, "activeBuildConversions")
        .iter()
        .any(|v| text(v, "conversion") == "unsheatheToAtk");
    if conversion {
        for key in ["atkF", "baseWpnAtkF", "unsheatheP", "unsheatheF"] {
            ctx[key] = b[key].clone();
        }
    }
    if conversion || text(base, "subType") == "마도구" {
        ctx["atkP"] = b["atkP"].clone();
    }
    for key in ["elemP", "elemDmg", "elemDmgP"] {
        ctx[key] = b["elem"].clone();
    }
    result["ctx"] = ctx;
    Ok(result)
}
pub fn candidate_supply_bases(base: &Value) -> Result<Value, String> {
    if !base.is_object() {
        return Err("object calculation context required".into());
    }
    let mut result = Value::Null;
    evaluate_filtered_summary_impl::<true, _, _>(
        base,
        &NativeStats::new(),
        |_, _| true,
        None,
        EvaluationOutput::Supply(&mut result),
    )?;
    Ok(result)
}
pub fn normal_attack_ampr(value: f64, profile: &Value) -> Value {
    full_ampr(value, Some(profile))
}
pub fn resistance_profile(components: &Value) -> Value {
    let values: Vec<f64> = components
        .as_array()
        .map(Vec::as_slice)
        .unwrap_or(&[])
        .iter()
        .map(|v| v.as_f64().unwrap_or(0.0))
        .collect();
    let raw: f64 = values.iter().sum();
    serde_json::json!({"components":values,"raw":raw,"effective":raw,"multiplier":((1.0-raw/100.0)*1e12).round()/1e12})
}
