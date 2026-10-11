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
mod tests {
    #[test]
    fn prepared_decimal_multipliers_preserve_exact_floor_and_fallbacks() {
        use super::decimal_math::PreparedMultiplier;
        for rate in [
            0.0,
            -0.0,
            1.0,
            -1.0,
            0.29,
            1.1648,
            32.80499999999999,
            1e-100,
            1e100,
            f64::INFINITY,
            f64::NAN,
        ] {
            let prepared = PreparedMultiplier::new(rate);
            for value in [
                -1e100,
                -2147483647.0,
                -151.25,
                -0.0,
                0.0,
                28.99999999999999,
                151.25,
                9007199254740991.0,
                1e100,
                f64::INFINITY,
                f64::NAN,
            ] {
                let expected = floor_ratio(value, rate, 1.0, 0.0);
                let actual = prepared.apply(value);
                assert!(
                    actual.to_bits() == expected.to_bits() || actual.is_nan() && expected.is_nan(),
                    "{value} * {rate}: {actual} != {expected}"
                );
            }
        }
        let prepared = PreparedMultiplier::new(0.29);
        for value in -10000_i64..=10000 {
            assert_eq!(
                prepared.apply(value as f64),
                (value * 29).div_euclid(100) as f64
            );
        }
    }

    #[test]
    fn decimal_ratios_floor_the_mathematical_stage() {
        use super::{floor_percent, floor_ratio};
        assert_eq!(floor_percent(25.0, 16.0, 0.0), 29.0);
        assert_eq!(floor_percent(50.0, 14.0, 0.0), 57.0);
        assert_eq!(floor_percent(-25.0, 16.0, 0.0), -29.0);
        assert_eq!(floor_percent(25.0, 16.48, 0.0), 29.0);
        assert_eq!(floor_ratio(100.0, 0.29, 1.0, 0.0), 29.0);
        assert_eq!(floor_ratio(25.0, 1.1648, 1.0, 0.0), 29.0);
        assert_eq!(floor_ratio(28.99999999999999, 1.0, 1.0, 0.0), 28.0);
        assert_eq!(floor_ratio(-25.0, 1.1648, 1.0, 0.0), -30.0);
        assert_eq!(floor_ratio(1e30, 1e30, 1e60, 0.0), 1.0);
        assert_eq!(floor_ratio(1e-100, 1e100, 1.0, 0.0), 1.0);
        // Independent i128 oracle exercises both signs and the i64 fast-path limit.
        for v in [-2147483647_i128, -151, -25, 0, 25, 151, 2147483647] {
            for r in [-2147483647_i128, -116, 0, 116, 2147483647] {
                for d in [-100_i128, -3, 3, 100] {
                    let n = v * r + 7 * d;
                    let expected = (n / d - i128::from(n % d != 0 && (n < 0) != (d < 0))) as f64;
                    assert_eq!(floor_ratio(v as f64, r as f64, d as f64, 7.0), expected);
                }
            }
        }
    }

    #[test]
    fn search_projection_covers_evaluator_reads_and_dynamic_stat_totals() {
        // Fail when a new literal evaluator dependency is omitted from projection.
        let source = include_str!("evaluator.rs")
            .split("mod tests {")
            .next()
            .unwrap();
        let mut dependencies = std::collections::BTreeSet::new();
        for call in source.split("StatKey::").skip(1) {
            let key = call
                .split(|c: char| !c.is_ascii_uppercase() && c != '_')
                .next()
                .unwrap();
            if !key.is_empty() {
                dependencies.insert(key);
            }
        }
        assert!(dependencies.contains("MOTIONSPEED"));
        assert!(dependencies.contains("VITP"));
        for key in dependencies {
            let raw = NativeStats::from([(key.to_owned(), -17.25)]);
            assert_eq!(raw.evaluation_projection().get(key), raw.get(key), "{key}");
        }
    }

    #[test]
    fn score_only_utility_matches_raw_reference_at_every_rejection_stage() {
        let base = serde_json::json!({"level":100,"mainType":"한손검","wpnAtk":100,"strBase":200,
            "normalAttackAmprProfile":{"passive":[{"percent":13.7,"multiplier":1.2,"flat":-2.5}],"activeCandidates":[{"id":"a","multiplier":1.2,"flat":0.5}]}});
        for mp in [100.0, 2000.0, 2300.0, 5000.0] {
            for percent in [-100.0, 0.0, 250.0] {
                let stats = NativeStats::from([
                    ("MAXMP".into(), mp),
                    ("AMPRP".into(), percent),
                    ("AMPR".into(), 7.5),
                ]);
                let prepared = PreparedContext::from(base.clone());
                for stop in 0..=5 {
                    let mut expected = Vec::new();
                    let raw = evaluate_utility_feasible_summary(&prepared, &stats, |i, v| {
                        expected.push((i, v));
                        i != stop
                    })
                    .unwrap();
                    let mut actual = Vec::new();
                    let score = evaluate_utility_feasible_score(&prepared, &stats, |i, v| {
                        actual.push((i, v));
                        i != stop
                    })
                    .unwrap();
                    assert_eq!(actual, expected);
                    assert_eq!(
                        score.map(|s| s.optimization_damage_factor),
                        raw.as_ref().map(|s| s.optimization_damage_factor)
                    );
                    if let Some(raw) = raw {
                        let full = evaluate_summary_from_native_stats(&prepared, &stats).unwrap();
                        assert_eq!(raw.ampr_before_dual, full.ampr_before_dual);
                    }
                }
            }
        }
    }
    use super::*;
    use serde_json::json;

    #[test]
    fn lazy_sum_score_and_utility_stages_match_materialized_sum() {
        for base in [
            json!({"level":325,"mainType":"한손검","strBase":327,"dexBase":510,"wpnAtk":690,"wpnRefine":15}),
            json!({"level":325,"mainType":"지팡이","atkType":"MAG","intBase":400,"wpnRefine":3.25}),
            json!({"level":325,"mainType":"한손검","subType":"한손검(듀얼소드)","subAtk":123,"subRefine":-1.25,"subStab":70}),
            json!({"level":325,"mainType":"자동활","subType":"마도구","conversionLevel":4.125,"attackPowerMode":"sum"}),
        ] {
            let base = PreparedContext::from(base);
            let mut left = NativeStats::new();
            let mut right = NativeStats::new();
            for (i, key) in DENSE_STAT_KEYS.iter().enumerate() {
                left.insert((*key).into(), i as f64 * 3.25 - 17.0);
                if i % 3 != 0 {
                    right.insert((*key).into(), i as f64 * (-2.125) + 7.0);
                }
            }
            let mut summed = left.clone();
            summed.add_assign(&right);
            for stop in 0..=5 {
                let mut expected_values = Vec::new();
                let expected = evaluate_utility_feasible_score(&base, &summed, |i, v| {
                    expected_values.push((i, v.to_bits()));
                    i != stop
                })
                .unwrap();
                let mut values = Vec::new();
                let actual =
                    evaluate_utility_feasible_score_from_sum(&base, &left, &right, |i, v| {
                        values.push((i, v.to_bits()));
                        i != stop
                    })
                    .unwrap();
                assert_eq!(values, expected_values);
                assert_eq!(
                    actual.map(|s| s.optimization_damage_factor.to_bits()),
                    expected.map(|s| s.optimization_damage_factor.to_bits())
                );
            }
        }
    }

    #[test]
    fn nested_effects_match_raw_json_and_restore() {
        let stats = json!({"STR":17.5,"INT":-3.0,"VIT":21,"DEXP":7.5,"AGI":11,"UNSHEATHEP":17.0,"UNSHEATHE":33.0,"MAXMP":-21,"AMPRP":13});
        for nested in [
            json!({}),
            json!({"normalAttackAmprProfile":null,"damageMultiplierLayers":false,"skillStats":{},"activeBuildConversions":7}),
            json!({
                "normalAttackAmprProfile":{"passive":[null,{"percent":13.7,"multiplier":1.2,"flat":-2.5},{"percent":-17,"multiplier":"bad","flat":3.1}],"activeCandidates":[{"id":"z","multiplier":1.2,"flat":0.5},{"id":"a","multiplier":1.2,"flat":0.5},{"id":null,"percent":11},{}]},
                "damageMultiplierLayers":{"skill":null,"passive":1.13,"active":0.97,"combo":"bad"},
                "activeBuildConversions":[null,{"conversion":"other","value":99},{"conversion":"unsheatheToAtk","value":0.3},{"conversion":"unsheatheToAtk","value":0.7}],
                "skillStats":[{"stat":"STR","target":"mult","ratio":0.001},{"stat":"totalINT","target":"const","ratio":1.3},{"stat":"totalSTR","target":"mult","ratio":0.0007},{"stat":"totalDEX","target":"const","ratio":0.15},{"stat":"totalVIT","target":"const","ratio":-0.2},{"stat":"totalAGI","target":"mult","ratio":0.002},{"stat":"unknown","target":"mult","ratio":12},{"stat":"STR","target":"ignored","ratio":99},null]
            }),
        ] {
            let raw = extend(base(), nested);
            let prepared = PreparedContext::from(raw.clone());
            let restored: PreparedContext =
                serde_json::from_value(serde_json::to_value(&prepared).unwrap()).unwrap();
            assert_eq!(serde_json::to_value(&restored).unwrap(), raw);
            let expected = evaluate_summary(&raw, &stats).unwrap();
            for cached in [&prepared, &restored] {
                assert_summary(
                    evaluate_summary_from_lookup(cached, &stats).unwrap(),
                    expected.clone(),
                );
                for value in [-0.0, -13.7, 0.5, 177.9, 1e100] {
                    assert_eq!(
                        cached.effects.ampr(value).to_bits(),
                        resolve_normal_attack_ampr(value, raw.get("normalAttackAmprProfile"))
                            .to_bits()
                    );
                }
            }
        }
    }

    #[test]
    fn staged_rejection_skips_later_utility_stat_reads() {
        struct StageOnly(usize);
        impl StatLookup for StageOnly {
            fn stat_number(&self, key: &str) -> f64 {
                let stage = match key {
                    "VITP" | "VIT" | "MAXHPP" | "MAXHP" => 0,
                    "INTP" | "INT" | "MAXMP" => 1,
                    "AMPRP" | "AMPR" => 2,
                    "CRITP" | "CRIT" => 3,
                    "STRP" | "STR" | "DEXP" | "DEX" | "AGIP" | "AGI" | "ASPD_P" | "ASPD" => 4,
                    _ => panic!("damage stat read after utility rejection: {key}"),
                };
                assert!(stage <= self.0, "later utility read: {key}");
                0.0
            }
        }
        let base = PreparedContext::from(json!({"level":325,"mainType":"한손검"}));
        for stop in 0..5 {
            let mut calls = 0;
            let result = evaluate_filtered_summary(&base, &StageOnly(stop), |index, _| {
                assert_eq!(index, calls);
                calls += 1;
                index != stop
            })
            .unwrap();
            assert!(result.is_none());
            assert_eq!(calls, stop + 1);
        }
    }

    #[test]
    fn utility_rejection_skips_damage_stat_reads() {
        struct UtilityOnly;
        impl StatLookup for UtilityOnly {
            fn stat_number(&self, key: &str) -> f64 {
                assert!(
                    matches!(
                        key,
                        "STRP"
                            | "STR"
                            | "DEXP"
                            | "DEX"
                            | "INTP"
                            | "INT"
                            | "AGIP"
                            | "AGI"
                            | "VITP"
                            | "VIT"
                            | "MAXMP"
                            | "MAXHPP"
                            | "MAXHP"
                            | "AMPRP"
                            | "AMPR"
                            | "CRITP"
                            | "CRIT"
                            | "ASPD_P"
                            | "ASPD"
                    ),
                    "damage stat read before rejection: {key}"
                );
                0.0
            }
        }
        let base = PreparedContext::from(json!({"level":325,"mainType":"한손검"}));
        assert!(evaluate_filtered_summary(&base, &UtilityOnly, |_, _| false)
            .unwrap()
            .is_none());
        assert!(
            evaluate_feasible_summary(&json!(null), &NativeStats::default(), |_, _| false).is_err()
        );
    }

    #[test]
    fn prepared_scalars_preserve_types_defaults_bits_and_roundtrip() {
        let keys = PREPARED_KEYS
            .iter()
            .copied()
            .chain(["futureField"])
            .collect::<Vec<_>>();
        for value in [
            None,
            Some(Value::Null),
            Some(json!(false)),
            Some(json!(true)),
            Some(json!(0)),
            Some(json!(-0.0)),
            Some(json!(-123.25)),
            Some(json!(u64::MAX)),
            Some(json!("42")),
            Some(json!([1])),
            Some(json!({"x":1})),
        ] {
            let mut raw = json!({});
            if let Some(value) = value {
                for key in &keys {
                    raw[*key] = value.clone();
                }
            }
            let prepared = PreparedContext::from(raw.clone());
            let serialized = serde_json::to_value(&prepared).unwrap();
            assert_eq!(serialized, raw);
            let restored: PreparedContext = serde_json::from_value(serialized).unwrap();
            for cached in [&prepared, &restored] {
                for &(typed, name) in PREPARED_FIELDS {
                    assert_eq!(
                        cached.number_at(typed).to_bits(),
                        raw.number_at(typed).to_bits(),
                        "{name}"
                    );
                    assert_eq!(cached.flag_at(typed), raw.flag_at(typed), "{name}");
                    assert_eq!(cached.get_at(typed), raw.get_at(typed), "{name}");
                }
                for key in &keys {
                    assert_eq!(
                        number(cached, key).to_bits(),
                        number(&raw, key).to_bits(),
                        "{key}"
                    );
                    assert_eq!(flag(cached, key), flag(&raw, key), "{key}");
                    assert_eq!(
                        finite_number(cached, key, 7.0).to_bits(),
                        finite_number(&raw, key, 7.0).to_bits()
                    );
                    assert_eq!(text(cached, key), text(&raw, key));
                    assert_eq!(array(cached, key), array(&raw, key));
                    assert_eq!(cached.context_get(key), raw.get(key));
                }
            }
        }
    }

    #[test]
    fn dense_stats_preserve_sparse_values_and_future_keys_bit_for_bit() {
        let keys = DENSE_STAT_KEYS
            .iter()
            .copied()
            .chain(["FUTURE_STAT"])
            .collect::<Vec<_>>();
        for value in [
            -0.0,
            0.0,
            -123.25,
            1e16,
            f64::MIN_POSITIVE,
            f64::INFINITY,
            f64::NAN,
        ] {
            for selected in &keys {
                let source = BTreeMap::from([(selected.to_string(), value)]);
                let dense = DenseStats::new(&source);
                for key in &keys {
                    assert_eq!(
                        dense.stat_number(key).to_bits(),
                        source.stat_number(key).to_bits()
                    );
                }
            }
        }
        let source = keys
            .iter()
            .enumerate()
            .map(|(index, key)| (key.to_string(), index as f64 - 20.5))
            .collect::<BTreeMap<_, _>>();
        let dense = DenseStats::new(&source);
        for key in keys {
            assert_eq!(
                dense.stat_number(key).to_bits(),
                source.stat_number(key).to_bits()
            );
        }
    }

    #[test]
    fn prepared_context_preserves_json_types_defaults_and_roundtrip() {
        for original in [
            json!({}),
            json!({"level": null, "noCritical": 1, "mainType": false}),
            json!({"level": "325", "noCritical": true, "mainType": "한손검",
                "criticalChanceMultiplier": 0, "normalAttackAmprProfile": {"passive": []},
                "unknownFutureField": {"nested": [1, null, "x"]}}),
            json!({"level": -0.0, "skillMult": 1.25, "additionalTargetResistances": [1, 2]}),
            json!({"level": 325.25, "maxMpF": -125.125, "crtBase": -85.5,
                "wpnRefine": 3.5, "subRefine": -2.25, "conversionLevel": 4.125}),
            json!({"level": 1e20, "maxMpF": -1e20, "crtBase": null,
                "wpnRefine": "15", "subRefine": false, "conversionLevel": -0.0}),
            json!({"strBase": 255, "dexBase": 500, "atkUpSTR": -1.25, "matkUpDEX": 2.75,
                "bossPhysResist": 10, "bossMagResist": -25,
                "additionalTargetResistances": [0.125, null, "10", -2],
                "procDamageModifiers": [{"chancePercent": 125, "multiplier": 1.3},
                    {"chancePercent": -10}, {"chancePercent": 35, "multiplier": 2}]}),
        ] {
            let prepared = PreparedContext::from(original.clone());
            let encoded = serde_json::to_value(&prepared).unwrap();
            assert_eq!(encoded, original);
            let restored: PreparedContext = serde_json::from_value(encoded).unwrap();
            for kind in [
                Invariant::AtkUp,
                Invariant::MatkUp,
                Invariant::PhysResistance,
                Invariant::MagicResistance,
                Invariant::Proc,
                Invariant::BaseCrit,
                Invariant::MainRefineSquared,
                Invariant::SubRefineSquared,
                Invariant::ConversionSquared,
                Invariant::MpFlat,
            ] {
                assert_eq!(
                    restored.invariant(kind).to_bits(),
                    original.invariant(kind).to_bits()
                );
            }
            for key in original
                .as_object()
                .unwrap()
                .keys()
                .map(String::as_str)
                .chain(["level", "noCritical", "mainType", "missing", "skillMult"])
            {
                assert_eq!(restored.context_get(key), original.get(key));
                assert_eq!(
                    number(&restored, key).to_bits(),
                    number(&original, key).to_bits()
                );
                assert_eq!(flag(&restored, key), flag(&original, key));
                assert_eq!(text(&restored, key), text(&original, key));
                assert_eq!(
                    finite_number(&restored, key, 1.0),
                    finite_number(&original, key, 1.0)
                );
                assert_eq!(array(&restored, key), array(&original, key));
            }
        }
        for invalid in [Value::Null, json!([]), json!(1), json!(false)] {
            let prepared = PreparedContext::from(invalid);
            assert!(evaluate_summary_from_map(&prepared, &BTreeMap::new()).is_err());
        }
    }

    #[test]
    fn evaluation_plan_roundtrip_preserves_fallbacks_and_candidate_boundaries() {
        for main in [json!("한손검"), json!("unknown"), Value::Null, json!(42)] {
            for mode in [
                json!("atk"),
                json!("sum"),
                json!("higher"),
                json!("wizardBlend"),
                Value::Null,
                json!(false),
            ] {
                for kind in ["PHYS", "MAG"] {
                    let context = extend(
                        base(),
                        json!({
                            "mainType": main, "subType":"마도구", "atkType":kind,
                            "attackPowerMode":mode, "strBase":250, "intBase":250,
                            "conversionLevel":10, "dualBringerActive":true,
                            "dualBringerLevel":10, "targetWeakened":true
                        }),
                    );
                    let prepared = PreparedContext::from(context.clone());
                    let encoded = serde_json::to_value(&prepared).unwrap();
                    assert_eq!(encoded, context);
                    let restored: PreparedContext = serde_json::from_value(encoded).unwrap();
                    for offset in [-1.0, 0.0, 1.0] {
                        let stats = BTreeMap::from([
                            ("STR".into(), offset),
                            ("INT".into(), -offset),
                            ("ATK".into(), -25.0),
                            ("MATK".into(), 100.0),
                            ("VITP".into(), 25.0),
                            ("MAXMP".into(), -99.0),
                            ("MOTIONSPEED".into(), 17.0),
                            ("PHYS_RES".into(), -20.0),
                            ("UNKNOWN_FUTURE".into(), 77.0),
                        ]);
                        let expected = evaluate_summary_from_map(&context, &stats).unwrap();
                        assert_eq!(
                            evaluate_summary_from_map(&prepared, &stats).unwrap(),
                            expected
                        );
                        assert_eq!(
                            evaluate_summary_from_map(&restored, &stats).unwrap(),
                            expected
                        );
                        let raw: NativeStats = stats.into_iter().collect();
                        let projected = raw.evaluation_projection();
                        assert_eq!(
                            evaluate_summary_from_native_stats(&prepared, &projected).unwrap(),
                            expected
                        );
                        assert_eq!(
                            utility_values(&prepared, &projected).unwrap(),
                            utility_values(&prepared, &raw).unwrap()
                        );
                    }
                }
            }
        }
    }

    #[test]
    fn weapon_stat_coefficients_match_external_evidence() {
        assert_eq!(
            atk_stat("권갑", "없음", 100.0, 0.0, 0.0, 0.0),
            (0.0, 0.0, 0.5)
        );
        assert_eq!(atk_stat("선풍창", "없음", 0.0, 100.0, 0.0, 0.0).1, 200.0);
        assert_eq!(atk_stat("선풍창", "없음", 0.0, 0.0, 100.0, 0.0).1, 100.0);
        for (int, expected) in [(1.0, 1.5), (2.0, 3.0), (255.0, 382.5), (500.0, 750.0)] {
            assert_eq!(atk_stat("발도검", "없음", 0.0, int, 0.0, 0.0).1, expected);
        }
    }

    fn base() -> Value {
        json!({"level":325,"strBase":255,"dexBase":500,"wpnAtk":600,"wpnRefine":15,"wpnStab":80,"mainType":"한손검","subType":"없음","armorType":"경량옷","bossLevel":325,"bossDef":2000,"bossMdef":2000,"critF":200,"aspdF":3000,"maxHpF":20000,"maxMpF":3000,"amprF":200,"skillMult":1,"atkType":"PHYS","rangeType":"SHORT"})
    }
    fn extend(mut target: Value, changes: Value) -> Value {
        target
            .as_object_mut()
            .unwrap()
            .extend(changes.as_object().unwrap().clone());
        target
    }
    fn assert_summary(
        actual: CrystaOptimizationNativeSummary,
        expected: CrystaOptimizationNativeSummary,
    ) {
        assert_eq!(actual, expected);
    }

    #[test]
    fn matches_js_physical_short_fixture() {
        let actual=evaluate_summary(&base(), &json!({"ATKP":12,"ATK":40,"CDMG":25,"CRIT":18,"SRW":10,"PHYS_PIERCE":8,"MAXHP":1000,"MAXMP":400,"AMPR":20,"ASPD":120})).unwrap();
        assert_summary(
            actual,
            CrystaOptimizationNativeSummary {
                optimization_damage_factor: 6105.0,
                final_max_hp: 23520,
                final_max_mp: 3825,
                ampr_before_dual: 268,
                normal_attack_crit: 243,
                final_aspd: 3834,
            },
        );
    }

    #[test]
    fn matches_js_magic_and_dual_boundaries() {
        let magic = extend(
            base(),
            json!({"mainType":"지팡이","wpnAtk":450,"wpnRefine":10,"wpnStab":60,"strBase":50,"intBase":500,"agiBase":100,"dexBase":200,"atkType":"MAG","rangeType":"LONG","bossMdef":2500,"bossMagResist":20,"spellBurstLevel":10,"targetWeakened":true,"attackElement":"weakness","magicElement":true,"critF":120,"maxHpF":0}),
        );
        assert_summary(evaluate_summary(&magic,&json!({"MATKP":20,"MATK":80,"CDMGP":15,"CRITP":10,"LRW":18,"MAG_PIERCE":25,"ELEM_P":12,"MAXMP":600,"AMPRP":20})).unwrap(),CrystaOptimizationNativeSummary{optimization_damage_factor:4922.0,final_max_hp:2520,final_max_mp:4075,ampr_before_dual:260,normal_attack_crit:147,final_aspd:3997});
        let dual = extend(
            base(),
            json!({"subType":"한손검(듀얼소드)","subAtk":420,"subRefine":12,"subStab":70,"agiBase":300,"armorType":"중량옷"}),
        );
        assert_summary(
            evaluate_summary(
                &dual,
                &json!({"ATKP":8,"WATKP":5,"STABILITY":12,"AMPR":15,"ASPD_P":20,"CRIT":30}),
            )
            .unwrap(),
            CrystaOptimizationNativeSummary {
                optimization_damage_factor: 8138.0,
                final_max_hp: 22520,
                final_max_mp: 3425,
                ampr_before_dual: 259,
                normal_attack_crit: 255,
                final_aspd: 4215,
            },
        );
    }

    #[test]
    fn matches_js_unsheathe_critical_damage_cap_fixture() {
        let unsheathe = extend(
            base(),
            json!({"mainType":"발도검","chkIsUnsheathe":true,"strBase":400,"dexBase":400,"critF":500,"cdmgF":220,"bossDef":1200}),
        );
        assert_summary(evaluate_summary(&unsheathe,&json!({"UNSHEATHEP":15,"UNSHEATHE":80,"CDMG":130,"CRIT":60,"SRW":20,"PHYS_PIERCE":10})).unwrap(),CrystaOptimizationNativeSummary{optimization_damage_factor:17547.0,final_max_hp:22520,final_max_mp:3425,ampr_before_dual:244,normal_attack_crit:585,final_aspd:3967});
    }

    #[test]
    fn matches_js_active_conversion_and_multiplier_layers_fixture() {
        let context = extend(
            base(),
            json!({
                "mainType":"한손검","subType":"마도구","strBase":300,"intBase":210,"agiBase":50,"dexBase":200,"wpnAtk":500,"wpnRefine":12,
                "bossDef":3500,"bossPhysResist":15,"additionalTargetResistances":[5,-2],"chkIsUnsheathe":true,"unsheatheP":14,"unsheatheF":60,
            "activeBuildConversions":[{"conversion":"unsheatheToAtk","value":0.5}],"conversionLevel":5,"fixedCriticalChance":70,"minimumCriticalDamage":260,
                "normalAttackAmprProfile":{"passive":[{"percent":10},{"flat":7}],"activeCandidates":[{"id":"zeta","percent":20},{"id":"alpha","multiplier":1.2}]},
                "ignoreDefense":true,"useHigherRangeDamage":true,"srw":8,"lrw":18,"attackPowerMode":"higher",
            "damageMultiplierLayers":{"skill":1.18,"passive":1.05,"active":1.1,"combo":0.8},"skillStats":[{"stat":"totalSTR","target":"mult","ratio":0.0005},{"stat":"DEX","target":"const","ratio":0.1}],
            "procDamageModifiers":[{"source":"half","chancePercent":50,"multiplier":2},{"source":"minus","chancePercent":25,"multiplier":0.5}]
            }),
        );
        assert_summary(evaluate_summary(&context,&json!({"ATKP":9,"ATK":30,"MATKP":15,"MATK":80,"UNSHEATHEP":6,"UNSHEATHE":20,"MAXMP":200,"AMPR":10,"CRIT":15,"CDMG":20,"LRW":4})).unwrap(),CrystaOptimizationNativeSummary{optimization_damage_factor:9499.875,final_max_hp:22520,final_max_mp:3646,ampr_before_dual:345,normal_attack_crit:240,final_aspd:4042});
    }

    #[test]
    fn matches_js_magic_arrow_and_dual_bringer_fixtures() {
        let arrow = extend(
            base(),
            json!({
                "mainType":"활","subType":"화살","subAtk":180,"subStab":20,"strBase":150,"intBase":420,"agiBase":100,"dexBase":350,"wpnAtk":470,"wpnStab":55,
                "atkType":"MAG","attackPowerMode":"wizardBlend","bossMdef":3200,"bossMagResist":10,"additionalTargetResistances":[7],"halfMdefIgnored":true,
                "spellBurstLevel":12,"targetWeakened":true,"attackElement":"weakness","fixedCriticalChance":160,"magicPierceSkillBonus":12,
            "rangeType":"LONG","damageMultiplierLayers":{"passive":1.03,"active":1.07,"combo":0.9},"skillStats":[{"stat":"totalINT","target":"const","ratio":0.2}]
            }),
        );
        assert_summary(evaluate_summary(&arrow,&json!({"ATKP":5,"MATKP":30,"MATK":90,"CRIT":25,"CDMG":35,"MAG_PIERCE":18,"LRW":12,"ELEM_P":8,"STABILITY":5})).unwrap(),CrystaOptimizationNativeSummary{optimization_damage_factor:3662.0,final_max_hp:22520,final_max_mp:3467,ampr_before_dual:244,normal_attack_crit:250,final_aspd:4170});
        let bringer = extend(
            base(),
            json!({
                "mainType":"한손검","subType":"마도구","strBase":400,"intBase":250,"agiBase":80,"dexBase":180,"atkType":"MAG","attackPowerMode":"sum",
                "bossMdef":1800,"bossMagResist":8,"spellBurstLevel":8,"targetWeakened":true,"dualBringerActive":true,"dualBringerLevel":10,
                "ignoreMdef":true,"criticalChanceMultiplier":1.1
            }),
        );
        // CDMG reflection: (270 - 100) * 70 / 100 = 119 exactly, hence 219%.
        // ATK 3297 + MATK 1455 -> floor(4752 * 92 / 100) = 4371;
        // floor(4371 * 219 / 100) = 9572.
        assert_summary(evaluate_summary(&bringer,&json!({"ATKP":10,"ATK":20,"MATKP":12,"MATK":50,"CRIT":80,"CDMG":40,"MAG_PIERCE":15})).unwrap(),CrystaOptimizationNativeSummary{optimization_damage_factor:9572.0,final_max_hp:22520,final_max_mp:3450,ampr_before_dual:244,normal_attack_crit:305,final_aspd:4261});
    }
}
