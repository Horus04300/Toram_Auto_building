//! First Rust port of the D4 summary evaluator.
//!
//! It is intentionally limited to the formula surface covered by the
//! JavaScript-generated parity fixtures.  Callers must not use it for pruning
//! or recommendations until broader fixture/property gates are added.

use std::collections::BTreeMap;

use serde::Serialize;
use serde_json::Value;
#[path = "d4_native_stats.rs"]
#[allow(dead_code)] // The summary bridge does not link search-only operations.
mod native_stats;
pub use native_stats::NativeStats;

/// Immutable lookup cache. JSON remains the serialization contract; cached
/// fields preserve missing/null/type semantics and are rebuilt on deserialize.
pub trait ContextLookup {
    fn context_get(&self, key: &str) -> Option<&Value>;
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
        let main = text(base, "mainType");
        let sub = text(base, "subType");
        let is_magic = text(base, "atkType") == "MAG";
        let power = match text(base, "attackPowerMode") {
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
            conversion: number(base, "conversionLevel") > 0.0
                && matches!(main, "한손검" | "양손검" | "자동활" | "권갑"),
            armor_aspd: match text(base, "armorType") {
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
}

// Only base-context expressions belong here; no candidate stats are cached.
fn compute_invariant(base: &Value, kind: Invariant) -> f64 {
    match kind {
        Invariant::AtkUp => {
            floor(number(base, "strBase") * number(base, "atkUpSTR") / 100.0)
                + floor(number(base, "dexBase") * number(base, "atkUpDEX") / 100.0)
                + floor(number(base, "intBase") * number(base, "atkUpINT") / 100.0)
                + floor(number(base, "agiBase") * number(base, "atkUpAGI") / 100.0)
                + floor(number(base, "vitBase") * number(base, "atkUpVIT") / 100.0)
        }
        Invariant::MatkUp => {
            floor(number(base, "strBase") * number(base, "matkUpSTR") / 100.0)
                + floor(number(base, "dexBase") * number(base, "matkUpDEX") / 100.0)
                + floor(number(base, "intBase") * number(base, "matkUpINT") / 100.0)
                + floor(number(base, "agiBase") * number(base, "matkUpAGI") / 100.0)
                + floor(number(base, "vitBase") * number(base, "matkUpVIT") / 100.0)
        }
        Invariant::PhysResistance => resistance_multiplier(base, false),
        Invariant::MagicResistance => resistance_multiplier(base, true),
        Invariant::Proc => expected_proc_multiplier(base),
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
        #[cfg(test)]
        const PREPARED_KEYS: &[&str] = &[$($key,)*];
        #[derive(Clone, Debug, Serialize)]
        #[serde(transparent)]
        pub struct PreparedContext {
            original: Value,
            #[serde(skip)] invariants: [f64; 5],
            #[serde(skip)] plan: EvaluationPlan,
            #[serde(skip)] effects: PreparedEffects,
            $(#[serde(skip)] $field: PreparedField,)*
        }
        impl From<Value> for PreparedContext {
            fn from(original: Value) -> Self {
                Self { $($field: PreparedField::new(original.get($key)),)*
                    plan: EvaluationPlan::new(&original),
                    effects: PreparedEffects::new(&original),
                    invariants: [Invariant::AtkUp, Invariant::MatkUp, Invariant::PhysResistance, Invariant::MagicResistance, Invariant::Proc].map(|kind| compute_invariant(&original, kind)), original }
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
pub struct D4NativeSummary {
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

fn number<C: ContextLookup>(value: &C, key: &str) -> f64 {
    value.context_number(key)
}

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
            result = floor(result * (100.0 + self.percent) / 100.0);
        }
        if self.multiplier != 1.0 {
            result = floor(result * self.multiplier);
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
    skill_terms: Vec<SkillTerm>,
}
impl PreparedEffects {
    fn new(base: &Value) -> Self {
        let profile = base.get("normalAttackAmprProfile").unwrap_or(&Value::Null);
        let layers = base.get("damageMultiplierLayers").unwrap_or(&Value::Null);
        let skill_terms = array(base, "skillStats")
            .iter()
            .filter_map(|item| {
                let to_mult = match text(item, "target") {
                    "mult" => true,
                    "const" => false,
                    _ => return None,
                };
                let source = match text(item, "stat") {
                    "STR" => SkillSource::Fixed(number(base, "strBase")),
                    "INT" => SkillSource::Fixed(number(base, "intBase")),
                    "VIT" => SkillSource::Fixed(number(base, "vitBase")),
                    "AGI" => SkillSource::Fixed(number(base, "agiBase")),
                    "DEX" => SkillSource::Fixed(number(base, "dexBase")),
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
            layers: [
                finite_number(layers, "skill", number(base, "skillMult")),
                finite_number(layers, "passive", 1.0),
                finite_number(layers, "active", 1.0),
                finite_number(layers, "combo", 1.0),
            ],
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
        result = floor(result * (100.0 + percent) / 100.0);
    }
    if multiplier != 1.0 {
        result = floor(result * multiplier);
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
    fn stat_number(&self, key: &str) -> f64 {
        self.get(key).copied().unwrap_or(0.0)
    }
}
#[allow(dead_code)]
pub fn evaluate_summary_from_native_stats<C: ContextLookup>(
    base: &C,
    stats: &NativeStats,
) -> Result<D4NativeSummary, String> {
    if !base.is_object() {
        return Err("D4 native summary requires an object base context".into());
    }
    evaluate_summary_from_lookup(base, stats)
}

fn stat<T: StatLookup>(stats: &T, key: &str) -> f64 {
    stats.stat_number(key)
}

fn floor(value: f64) -> f64 {
    value.floor()
}

fn stat_total<T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    base_key: &str,
    percent_key: &str,
    flat_key: &str,
    stat_percent: &str,
    stat_flat: &str,
) -> f64 {
    floor(
        number(base, base_key)
            * (1.0 + (number(base, percent_key) + stat(stats, stat_percent)) / 100.0)
            + number(base, flat_key)
            + stat(stats, stat_flat),
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
        agi * 4.2 + str_ * 0.2
    } else {
        match main {
            WeaponKind::TwoHand => agi * 2.1 + str_ * 0.2,
            WeaponKind::Bow => agi * 3.1 + dex * 0.2,
            WeaponKind::Bowgun => agi * 2.2 + dex * 0.2,
            WeaponKind::Staff => agi * 1.8 + int_ * 0.2,
            WeaponKind::Device => agi * 4.0 + int_ * 0.2,
            WeaponKind::Knuckle => agi * 4.6 + dex * 0.1 + str_ * 0.1,
            WeaponKind::Halberd => agi * 3.5 + str_ * 0.2,
            WeaponKind::Katana => agi * 3.9 + dex * 0.3,
            _ => agi * 9.6,
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
pub fn evaluate_summary(base: &Value, stats: &Value) -> Result<D4NativeSummary, String> {
    if !base.is_object() || !stats.is_object() {
        return Err("D4 native summary requires object inputs".to_string());
    }
    evaluate_summary_from_lookup(base, stats)
}

/// Native D4 search keeps aggregate stats in this compact map form.  This
/// entry point deliberately avoids constructing a serde_json object for every
/// bound and leaf evaluation.
#[allow(dead_code)] // The summary bridge intentionally does not link the solver.
pub fn evaluate_summary_from_map<C: ContextLookup>(
    base: &C,
    stats: &BTreeMap<String, f64>,
) -> Result<D4NativeSummary, String> {
    if !base.is_object() {
        return Err("D4 native summary requires an object base context".to_string());
    }
    evaluate_summary_from_lookup(base, &DenseStats::new(stats))
}

fn evaluate_summary_from_lookup<T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
) -> Result<D4NativeSummary, String> {
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
) -> Result<Option<D4NativeSummary>, String> {
    if !base.is_object() {
        return Err("D4 native summary requires an object base context".into());
    }
    evaluate_filtered_summary(base, stats, accepts)
}

fn evaluate_filtered_summary<T: StatLookup, C: ContextLookup>(
    base: &C,
    stats: &T,
    mut accepts: impl FnMut(usize, i64) -> bool,
) -> Result<Option<D4NativeSummary>, String> {
    let plan = base.evaluation_plan().unwrap_or_else(|| {
        let mut plan = EvaluationPlan::new(base);
        // Keep the uncached Value path as a full-computation reference.
        plan.need_atk = true;
        plan.need_matk = true;
        plan
    });
    let vit = stat_total(base, stats, "vitBase", "vitP", "vitF", "VITP", "VIT");
    let level = number(base, "level");
    let base_max_hp = floor((vit + 22.41) * level / 3.0 + 93.0);
    let max_hp = (floor(
        base_max_hp * (1.0 + (number(base, "maxHpP") + stat(stats, "MAXHPP")) / 100.0)
            + number(base, "maxHpF")
            + stat(stats, "MAXHP"),
    ))
    .clamp(0.0, 99999.0) as i64;
    if !accepts(0, max_hp) {
        return Ok(None);
    }
    let int_ = stat_total(base, stats, "intBase", "intP", "intF", "INTP", "INT");
    let max_mp = floor(100.0 + level + int_ * 0.1 + number(base, "maxMpF") + stat(stats, "MAXMP"))
        .max(0.0) as i64;
    if !accepts(1, max_mp) {
        return Ok(None);
    }
    let base_ampr = floor(10.0 + max_mp as f64 / 100.0);
    let ampr = floor(base_ampr * (100.0 + number(base, "amprP") + stat(stats, "AMPRP")) / 100.0)
        + number(base, "amprF")
        + stat(stats, "AMPR");
    let ampr_before_dual = match base.prepared_effects() {
        Some(effects) => effects.ampr(ampr),
        None => resolve_normal_attack_ampr(ampr, base.context_get("normalAttackAmprProfile")),
    } as i64;

    if !accepts(2, ampr_before_dual) {
        return Ok(None);
    }

    let base_crit = 25.0 + floor(number(base, "crtBase") / 3.4);
    let normal_raw =
        floor(base_crit * (1.0 + (number(base, "critP") + stat(stats, "CRITP")) / 100.0))
            + number(base, "critF")
            + stat(stats, "CRIT");
    let normal_attack_crit = (normal_raw - number(base, "bossCritResist")) as i64;
    if !accepts(3, normal_attack_crit) {
        return Ok(None);
    }
    let str_ = stat_total(base, stats, "strBase", "strP", "strF", "STRP", "STR");
    let dex = stat_total(base, stats, "dexBase", "dexP", "dexF", "DEXP", "DEX");
    let agi = stat_total(base, stats, "agiBase", "agiP", "agiF", "AGIP", "AGI");
    let armor_aspd = plan.armor_aspd;
    let final_aspd = (floor(
        (plan.weapon_aspd
            + floor(stat_aspd_prepared(
                plan.weapon,
                plan.sub_dual,
                str_,
                int_,
                agi,
                dex,
            ))
            + level)
            * (1.0 + (number(base, "aspdP") + stat(stats, "ASPD_P") + armor_aspd) / 100.0),
    ) + number(base, "aspdF")
        + stat(stats, "ASPD")) as i64;
    if !accepts(4, final_aspd) {
        return Ok(None);
    }

    let mut atk_p = number(base, "atkP") + stat(stats, "ATKP");
    let mut atk_f = number(base, "atkF") + stat(stats, "ATK");
    let mut base_wpn_atk_f = number(base, "baseWpnAtkF");
    let mut unsheathe_p = number(base, "unsheatheP") + stat(stats, "UNSHEATHEP");
    let mut unsheathe_f = number(base, "unsheatheF") + stat(stats, "UNSHEATHE");
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
        let converted_p = floor(rate * unsheathe_p);
        let converted_f = floor(rate * unsheathe_f);
        unsheathe_p = 0.0;
        unsheathe_f = 0.0;
        atk_p += converted_p;
        base_wpn_atk_f += converted_p;
        atk_f += converted_f;
    }
    let main = text(base, "mainType");
    let sub = text(base, "subType");
    let watkp = number(base, "watkP") + stat(stats, "WATKP");
    let watk = number(base, "watkF") + stat(stats, "WATK");
    let effective_weapon = number(base, "wpnAtk") + base_wpn_atk_f;
    let main_weapon = effective_weapon + floor(effective_weapon * watkp / 100.0) + watk;
    let mut weapon = main_weapon
        + floor(effective_weapon * number(base, "wpnRefine").powi(2) / 100.0)
        + number(base, "wpnRefine");
    if plan.arrow {
        weapon += floor(number(base, "subAtk"));
    }
    let (stat_atk, stat_matk, matk_ratio) =
        atk_stat_prepared(plan.weapon, plan.sub_dual, str_, int_, agi, dex);
    let atk_up = base.invariant(Invariant::AtkUp);
    let matk_up = base.invariant(Invariant::MatkUp);
    if plan.sub_device {
        atk_p -= 15.0;
    }
    let mut final_atk = if plan.need_atk {
        floor((weapon + stat_atk + level + atk_up) * (1.0 + atk_p / 100.0)) + atk_f
    } else {
        0.0
    };
    let mut final_matk = if plan.need_matk {
        floor(
            (floor(weapon * matk_ratio) + stat_matk + level + matk_up)
                * (1.0 + (number(base, "matkP") + stat(stats, "MATKP")) / 100.0),
        ) + number(base, "matkF")
            + stat(stats, "MATK")
    } else {
        0.0
    };
    let conversion_level = number(base, "conversionLevel");
    if plan.need_matk && plan.conversion {
        let mut conversion_add = floor(weapon * conversion_level.powi(2) / 100.0);
        let mut conversion_int = 0.0;
        if main == "권갑" {
            conversion_add = floor(conversion_add / 2.0);
        } else {
            conversion_int = floor(int_ * conversion_level * 0.1);
        }
        final_matk += floor(conversion_add) + floor(conversion_int);
    }
    if plan.need_atk && plan.dual {
        let sub_weapon = number(base, "subAtk")
            + floor(number(base, "subAtk") * watkp / 100.0)
            + floor(number(base, "subAtk") * number(base, "subRefine").powi(2) / 200.0)
            + number(base, "subRefine")
            + watk;
        let sub_atk =
            floor((sub_weapon + floor(str_ + agi * 3.0) + level) * (1.0 + atk_p / 100.0)) + atk_f;
        let sub_stab = (floor(number(base, "subStab") * 0.5)
            + floor(str_ * 0.06)
            + floor(agi * 0.04)
            + number(base, "stability")
            + stat(stats, "STABILITY"))
        .min(100.0);
        final_atk += floor(sub_atk * sub_stab / 100.0);
    }
    let mut cdmg = floor(
        (if str_ >= agi {
            150.0 + floor(str_ / 5.0)
        } else {
            150.0 + floor((str_ + agi) / 10.0)
        }) * (1.0 + (number(base, "cdmgP") + stat(stats, "CDMGP")) / 100.0),
    ) + number(base, "cdmgF")
        + stat(stats, "CDMG");
    if cdmg > 300.0 {
        cdmg = 300.0 + floor((cdmg - 300.0) / 2.0);
    }
    let critical_multiplier = base
        .context_get("criticalChanceMultiplier")
        .and_then(Value::as_f64)
        .unwrap_or(1.0);
    let mut final_crit =
        floor((normal_raw + number(base, "criticalChanceBonus")) * critical_multiplier);
    if let Some(fixed) = base
        .context_get("fixedCriticalChance")
        .and_then(Value::as_f64)
    {
        if fixed.is_finite() {
            final_crit = fixed;
        }
    }
    if number(base, "minimumCriticalDamage") != 0.0 {
        cdmg = cdmg.max(number(base, "minimumCriticalDamage"));
    }
    let mut stab = (number(base, "wpnStab")
        + number(base, "stability")
        + stat(stats, "STABILITY")
        + number(base, "stabilityBonus")
        + floor(physical_stability_prepared(plan.weapon, str_, dex)))
    .min(100.0);
    if plan.arrow {
        stab = (stab + number(base, "subStab")).min(100.0);
    }
    let is_magic = plan.is_magic;
    let attacks_weakness =
        flag(base, "elementAwakening") || text(base, "attackElement") == "weakness";
    let mut elem = number(base, "elemP") + stat(stats, "ELEM_P");
    if attacks_weakness {
        elem += 25.0;
    }
    if flag(base, "elementAwakening") || flag(base, "magicElement") {
        elem += floor(number(base, "intBase") / 10.0);
    }
    let mut final_cdmg = cdmg;
    let mut final_crit_rate = final_crit;
    if is_magic {
        let spell = 2.5 * number(base, "spellBurstLevel");
        let weaken = if flag(base, "targetWeakened")
            && (main == "지팡이" || main == "마도구" || attacks_weakness)
        {
            50.0
        } else {
            0.0
        };
        let mut crit_reflect = spell + weaken;
        if flag(base, "targetWeakened")
            && flag(base, "dualBringerActive")
            && sub == "마도구"
            && str_ >= int_
        {
            crit_reflect += 2.5 * number(base, "dualBringerLevel");
        }
        final_crit_rate = floor(final_crit * (crit_reflect / 100.0));
        let mut cdmg_reflect = 50.0 + spell;
        if flag(base, "dualBringerActive") && int_ > str_ {
            cdmg_reflect += 2.5 * number(base, "dualBringerLevel");
        }
        final_cdmg = 100.0 + floor((cdmg - 100.0) * (cdmg_reflect / 100.0));
        stab = (floor(50.0 + stab / 2.0)).min(100.0);
    }
    if flag(base, "chkGuaranteedCrit") {
        final_crit_rate = 1000.0;
    }
    if flag(base, "noCritical") {
        final_crit_rate = 0.0;
    }
    let crit_ev = (final_crit_rate - number(base, "bossCritResist")).clamp(0.0, 100.0) / 100.0;
    let crit_mult = (crit_ev * final_cdmg + (1.0 - crit_ev) * 100.0) / 100.0;
    let target_def = if is_magic {
        number(base, "bossMdef")
    } else {
        number(base, "bossDef")
    };
    let pierce = if is_magic {
        number(base, "magPierce")
            + stat(stats, "MAG_PIERCE")
            + number(base, "magicPierceSkillBonus")
    } else {
        number(base, "physPierce")
            + stat(stats, "PHYS_PIERCE")
            + number(base, "physicalPierceSkillBonus")
    };
    let mut effective_def = floor(target_def * (1.0 - pierce / 100.0));
    if (is_magic && flag(base, "ignoreMdef")) || (!is_magic && flag(base, "ignoreDefense")) {
        effective_def = 0.0;
    } else if is_magic && flag(base, "halfMdefIgnored") {
        effective_def = floor(effective_def / 2.0);
    }
    effective_def = effective_def.max(0.0);
    let [mut final_skill_mult, passive_damage_mult, active_damage_mult, combo_damage_mult] =
        match base.prepared_effects() {
            Some(effects) => effects.layers,
            None => {
                let layers = base
                    .context_get("damageMultiplierLayers")
                    .unwrap_or(&Value::Null);
                [
                    finite_number(layers, "skill", number(base, "skillMult")),
                    finite_number(layers, "passive", 1.0),
                    finite_number(layers, "active", 1.0),
                    finite_number(layers, "combo", 1.0),
                ]
            }
        };
    let mut final_skill_const = number(base, "skillConst");
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
                "STR" => number(base, "strBase"),
                "INT" => number(base, "intBase"),
                "VIT" => number(base, "vitBase"),
                "AGI" => number(base, "agiBase"),
                "DEX" => number(base, "dexBase"),
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
    let mut raw = floor(
        (base_power + level - number(base, "bossLevel"))
            * base.invariant(if is_magic {
                Invariant::MagicResistance
            } else {
                Invariant::PhysResistance
            }),
    );
    if flag(base, "chkIsUnsheathe") {
        raw += unsheathe_f;
    }
    raw += final_skill_const - effective_def;
    raw = raw.max(1.0);
    let range = if flag(base, "useHigherRangeDamage") {
        (number(base, "srw") + stat(stats, "SRW")).max(number(base, "lrw") + stat(stats, "LRW"))
    } else if text(base, "rangeType") == "SHORT" {
        number(base, "srw") + stat(stats, "SRW")
    } else {
        number(base, "lrw") + stat(stats, "LRW")
    };
    let unsheathe = if flag(base, "chkIsUnsheathe") {
        1.0 + unsheathe_p / 100.0
    } else {
        1.0
    };
    let mut damage = floor(raw * crit_mult);
    for multiplier in [
        1.0 + elem / 100.0,
        final_skill_mult,
        unsheathe,
        (100.0 + stab) / 200.0,
        passive_damage_mult,
        1.0 + range / 100.0,
        active_damage_mult,
        1.0 + (number(base, "damageP") + stat(stats, "DAMAGE_P")) / 100.0,
        combo_damage_mult,
    ] {
        damage = floor(damage * multiplier);
    }
    Ok(Some(D4NativeSummary {
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
    use super::*;
    use serde_json::json;

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
    fn assert_summary(actual: D4NativeSummary, expected: D4NativeSummary) {
        assert_eq!(actual, expected);
    }

    #[test]
    fn matches_js_physical_short_fixture() {
        let actual=evaluate_summary(&base(), &json!({"ATKP":12,"ATK":40,"CDMG":25,"CRIT":18,"SRW":10,"PHYS_PIERCE":8,"MAXHP":1000,"MAXMP":400,"AMPR":20,"ASPD":120})).unwrap();
        assert_summary(
            actual,
            D4NativeSummary {
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
        assert_summary(evaluate_summary(&magic,&json!({"MATKP":20,"MATK":80,"CDMGP":15,"CRITP":10,"LRW":18,"MAG_PIERCE":25,"ELEM_P":12,"MAXMP":600,"AMPRP":20})).unwrap(),D4NativeSummary{optimization_damage_factor:4922.0,final_max_hp:2520,final_max_mp:4075,ampr_before_dual:260,normal_attack_crit:147,final_aspd:3997});
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
            D4NativeSummary {
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
        assert_summary(evaluate_summary(&unsheathe,&json!({"UNSHEATHEP":15,"UNSHEATHE":80,"CDMG":130,"CRIT":60,"SRW":20,"PHYS_PIERCE":10})).unwrap(),D4NativeSummary{optimization_damage_factor:17547.0,final_max_hp:22520,final_max_mp:3425,ampr_before_dual:244,normal_attack_crit:585,final_aspd:3967});
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
        assert_summary(evaluate_summary(&context,&json!({"ATKP":9,"ATK":30,"MATKP":15,"MATK":80,"UNSHEATHEP":6,"UNSHEATHE":20,"MAXMP":200,"AMPR":10,"CRIT":15,"CDMG":20,"LRW":4})).unwrap(),D4NativeSummary{optimization_damage_factor:9499.875,final_max_hp:22520,final_max_mp:3646,ampr_before_dual:345,normal_attack_crit:240,final_aspd:4042});
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
        assert_summary(evaluate_summary(&arrow,&json!({"ATKP":5,"MATKP":30,"MATK":90,"CRIT":25,"CDMG":35,"MAG_PIERCE":18,"LRW":12,"ELEM_P":8,"STABILITY":5})).unwrap(),D4NativeSummary{optimization_damage_factor:3662.0,final_max_hp:22520,final_max_mp:3467,ampr_before_dual:244,normal_attack_crit:250,final_aspd:4170});
        let bringer = extend(
            base(),
            json!({
                "mainType":"한손검","subType":"마도구","strBase":400,"intBase":250,"agiBase":80,"dexBase":180,"atkType":"MAG","attackPowerMode":"sum",
                "bossMdef":1800,"bossMagResist":8,"spellBurstLevel":8,"targetWeakened":true,"dualBringerActive":true,"dualBringerLevel":10,
                "ignoreMdef":true,"criticalChanceMultiplier":1.1
            }),
        );
        assert_summary(evaluate_summary(&bringer,&json!({"ATKP":10,"ATK":20,"MATKP":12,"MATK":50,"CRIT":80,"CDMG":40,"MAG_PIERCE":15})).unwrap(),D4NativeSummary{optimization_damage_factor:9528.0,final_max_hp:22520,final_max_mp:3450,ampr_before_dual:244,normal_attack_crit:305,final_aspd:4261});
    }
}
