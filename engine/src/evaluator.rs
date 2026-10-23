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
mod decimal_math {
    use num_bigint::{BigInt, Sign};
    use std::{cell::RefCell, collections::HashMap};
    thread_local! {
        static PARTS: RefCell<HashMap<u64, (i128, i128)>> = RefCell::new(HashMap::new());
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
        let (digits, scale) = decimal_text(value);
        let n = digits.parse::<i128>().ok()?;
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

// Only base-context expressions belong here; no candidate stats are cached.
fn compute_invariant(base: &Value, kind: Invariant) -> f64 {
    match kind {
        Invariant::AtkUp => {
            floor_ratio(
                number_at(base, ContextKey::field_str_base),
                number_at(base, ContextKey::field_atk_up_s_t_r),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_dex_base),
                number_at(base, ContextKey::field_atk_up_d_e_x),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_int_base),
                number_at(base, ContextKey::field_atk_up_i_n_t),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_agi_base),
                number_at(base, ContextKey::field_atk_up_a_g_i),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_vit_base),
                number_at(base, ContextKey::field_atk_up_v_i_t),
                100.0,
                0.0,
            )
        }
        Invariant::MatkUp => {
            floor_ratio(
                number_at(base, ContextKey::field_str_base),
                number_at(base, ContextKey::field_matk_up_s_t_r),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_dex_base),
                number_at(base, ContextKey::field_matk_up_d_e_x),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_int_base),
                number_at(base, ContextKey::field_matk_up_i_n_t),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_agi_base),
                number_at(base, ContextKey::field_matk_up_a_g_i),
                100.0,
                0.0,
            ) + floor_ratio(
                number_at(base, ContextKey::field_vit_base),
                number_at(base, ContextKey::field_matk_up_v_i_t),
                100.0,
                0.0,
            )
        }
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
        let profile = base.get("normalAttackAmprProfile").unwrap_or(&Value::Null);
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
            StatKey::MATK_UP_DEX,
            StatKey::MATK_UP_AGI,
            StatKey::MATK_UP_INT,
            StatKey::MATK_UP_VIT,
        ]
    } else {
        [
            StatKey::ATK_UP_STR,
            StatKey::ATK_UP_DEX,
            StatKey::ATK_UP_AGI,
            StatKey::ATK_UP_INT,
            StatKey::ATK_UP_VIT,
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
    ["STR", "DEX", "AGI", "INT", "VIT"]
        .iter()
        .zip(values)
        .map(|(name, value)| {
            let prefix = if magic { "matkUp" } else { "atkUp" };
            floor_ratio(
                number(base, &format!("{}Base", name.to_lowercase())),
                number(base, &format!("{prefix}{name}")) + value,
                100.0,
                0.0,
            )
        })
        .sum()
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
    evaluate_filtered_summary_impl::<true, T, C>(base, stats, accepts, None)
}

fn evaluate_filtered_summary_impl<const RAW_AMPR: bool, T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    mut accepts: impl FnMut(usize, i64) -> bool,
    caps: Option<&[f64; 6]>,
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
    let max_hp = (floor_percent(
        base_max_hp,
        number_at(base, ContextKey::field_max_hp_p) + stat_at(stats, StatKey::MAXHPP),
        number_at(base, ContextKey::field_max_hp_f) + stat_at(stats, StatKey::MAXHP),
    ))
    .clamp(0.0, 99999.0) as i64;
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
    let normal_attack_crit =
        (normal_raw - number_at(base, ContextKey::field_boss_crit_resist)) as i64;
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
    let final_aspd = (floor_percent(
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
        + stat_at(stats, StatKey::ASPD)) as i64;
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
        let sub_atk =
            floor_percent(sub_weapon + floor(str_ + agi * 3.0) + level, atk_p, 0.0) + atk_f;
        let sub_stab = (floor(number_at(base, ContextKey::field_sub_stab) * 0.5)
            + floor_ratio(str_, 6.0, 100.0, 0.0)
            + floor_ratio(agi, 4.0, 100.0, 0.0)
            + number_at(base, ContextKey::field_stability)
            + stat_at(stats, StatKey::STABILITY))
        .min(100.0);
        final_atk += floor_ratio(sub_atk, sub_stab, 100.0, 0.0);
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
    let attacks_weakness =
        awakening || text_at(base, ContextKey::field_attack_element) == "weakness";
    let mut elem = number_at(base, ContextKey::field_elem_p) + stat_at(stats, StatKey::ELEM_P);
    if attacks_weakness {
        elem += 25.0;
    }
    if awakening || magic_element {
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
