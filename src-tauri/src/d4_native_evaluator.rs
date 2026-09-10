//! First Rust port of the D4 summary evaluator.
//!
//! It is intentionally limited to the formula surface covered by the
//! JavaScript-generated parity fixtures.  Callers must not use it for pruning
//! or recommendations until broader fixture/property gates are added.

use std::collections::BTreeMap;

use serde::Serialize;
use serde_json::Value;

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

fn number(value: &Value, key: &str) -> f64 {
    value.get(key).and_then(Value::as_f64).unwrap_or(0.0)
}

fn flag(value: &Value, key: &str) -> bool {
    value.get(key).and_then(Value::as_bool).unwrap_or(false)
}

fn text<'a>(value: &'a Value, key: &str) -> &'a str {
    value.get(key).and_then(Value::as_str).unwrap_or("")
}

fn finite_number(value: &Value, key: &str, default: f64) -> f64 {
    value
        .get(key)
        .and_then(Value::as_f64)
        .filter(|number| number.is_finite())
        .unwrap_or(default)
}

fn array<'a>(value: &'a Value, key: &str) -> &'a [Value] {
    value
        .get(key)
        .and_then(Value::as_array)
        .map(Vec::as_slice)
        .unwrap_or(&[])
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

fn resistance_multiplier(base: &Value, is_magic: bool) -> f64 {
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

fn expected_proc_multiplier(base: &Value) -> f64 {
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

fn stat<T: StatLookup>(stats: &T, key: &str) -> f64 {
    stats.stat_number(key)
}

fn floor(value: f64) -> f64 {
    value.floor()
}

fn stat_total<T: StatLookup>(
    base: &Value,
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

fn atk_stat(main: &str, sub: &str, str_: f64, int_: f64, agi: f64, dex: f64) -> (f64, f64, f64) {
    match main {
        "한손검" if sub == "한손검(듀얼소드)" => {
            (str_ + agi + dex * 2.0, int_ * 3.0 + dex, 0.0)
        }
        "한손검" => (str_ * 2.0 + dex * 2.0, int_ * 3.0 + dex, 0.0),
        "양손검" => (str_ * 3.0 + dex, int_ * 3.0 + dex, 0.0),
        "활" => (str_ + dex * 3.0, int_ * 3.0 + dex, 0.0),
        "자동활" => (dex * 4.0, int_ * 3.0 + dex, 0.0),
        "지팡이" => (str_ * 3.0 + int_, int_ * 4.0 + dex, 1.0),
        "마도구" => (int_ * 2.0 + agi * 2.0, int_ * 4.0 + dex, 1.0),
        // External evidence: docs/verification/weapon-stat-recommendation-audit-2026-09-09.md
        "권갑" => (agi * 2.0 + dex * 0.5, int_ * 4.0 + dex, 0.5),
        "선풍창" => (
            floor(str_ * 2.5) + floor(agi * 1.5),
            int_ * 2.0 + agi + dex,
            0.0,
        ),
        "발도검" => (floor(dex * 2.5) + floor(str_ * 1.5), int_ * 1.5 + dex, 0.0),
        _ => (str_, int_ * 3.0 + dex, 0.0),
    }
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

fn stat_aspd(main: &str, sub: &str, str_: f64, int_: f64, agi: f64, dex: f64) -> f64 {
    if main == "한손검" || sub == "한손검(듀얼소드)" {
        agi * 4.2 + str_ * 0.2
    } else {
        match main {
            "양손검" => agi * 2.1 + str_ * 0.2,
            "활" => agi * 3.1 + dex * 0.2,
            "자동활" => agi * 2.2 + dex * 0.2,
            "지팡이" => agi * 1.8 + int_ * 0.2,
            "마도구" => agi * 4.0 + int_ * 0.2,
            "권갑" => agi * 4.6 + dex * 0.1 + str_ * 0.1,
            "선풍창" => agi * 3.5 + str_ * 0.2,
            "발도검" => agi * 3.9 + dex * 0.3,
            _ => agi * 9.6,
        }
    }
}

fn physical_stability(main: &str, str_: f64, dex: f64) -> f64 {
    match main {
        "한손검" | "활" => (str_ + dex * 3.0) / 40.0,
        "양손검" | "마도구" => dex / 10.0,
        "자동활" | "지팡이" => str_ / 20.0,
        "권갑" => dex / 40.0,
        "선풍창" => (str_ + dex) / 40.0,
        "발도검" => (str_ * 3.0 + dex) / 40.0,
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
pub fn evaluate_summary_from_map(
    base: &Value,
    stats: &BTreeMap<String, f64>,
) -> Result<D4NativeSummary, String> {
    if !base.is_object() {
        return Err("D4 native summary requires an object base context".to_string());
    }
    evaluate_summary_from_lookup(base, stats)
}

fn evaluate_summary_from_lookup<T: StatLookup>(
    base: &Value,
    stats: &T,
) -> Result<D4NativeSummary, String> {
    let mut atk_p = number(base, "atkP") + stat(stats, "ATKP");
    let mut atk_f = number(base, "atkF") + stat(stats, "ATK");
    let mut base_wpn_atk_f = number(base, "baseWpnAtkF");
    let mut unsheathe_p = number(base, "unsheatheP") + stat(stats, "UNSHEATHEP");
    let mut unsheathe_f = number(base, "unsheatheF") + stat(stats, "UNSHEATHE");
    for effect in array(base, "activeBuildConversions") {
        if text(effect, "conversion") != "unsheatheToAtk" {
            continue;
        }
        let rate = number(effect, "value");
        let converted_p = floor(rate * unsheathe_p);
        let converted_f = floor(rate * unsheathe_f);
        unsheathe_p = 0.0;
        unsheathe_f = 0.0;
        atk_p += converted_p;
        base_wpn_atk_f += converted_p;
        atk_f += converted_f;
    }
    let str_ = stat_total(base, stats, "strBase", "strP", "strF", "STRP", "STR");
    let dex = stat_total(base, stats, "dexBase", "dexP", "dexF", "DEXP", "DEX");
    let int_ = stat_total(base, stats, "intBase", "intP", "intF", "INTP", "INT");
    let agi = stat_total(base, stats, "agiBase", "agiP", "agiF", "AGIP", "AGI");
    let vit = stat_total(base, stats, "vitBase", "vitP", "vitF", "VITP", "VIT");
    let level = number(base, "level");
    let max_mp = floor(100.0 + level + int_ * 0.1 + number(base, "maxMpF") + stat(stats, "MAXMP"))
        .max(0.0) as i64;
    let base_max_hp = floor((vit + 22.41) * level / 3.0 + 93.0);
    let max_hp = (floor(
        base_max_hp * (1.0 + (number(base, "maxHpP") + stat(stats, "MAXHPP")) / 100.0)
            + number(base, "maxHpF")
            + stat(stats, "MAXHP"),
    ))
    .clamp(0.0, 99999.0) as i64;
    let base_ampr = floor(10.0 + max_mp as f64 / 100.0);
    let ampr = floor(base_ampr * (100.0 + number(base, "amprP") + stat(stats, "AMPRP")) / 100.0)
        + number(base, "amprF")
        + stat(stats, "AMPR");
    let ampr_before_dual =
        resolve_normal_attack_ampr(ampr, base.get("normalAttackAmprProfile")) as i64;

    let main = text(base, "mainType");
    let sub = text(base, "subType");
    let watkp = number(base, "watkP") + stat(stats, "WATKP");
    let watk = number(base, "watkF") + stat(stats, "WATK");
    let effective_weapon = number(base, "wpnAtk") + base_wpn_atk_f;
    let main_weapon = effective_weapon + floor(effective_weapon * watkp / 100.0) + watk;
    let mut weapon = main_weapon
        + floor(effective_weapon * number(base, "wpnRefine").powi(2) / 100.0)
        + number(base, "wpnRefine");
    if sub == "화살" && (main == "활" || main == "자동활") {
        weapon += floor(number(base, "subAtk"));
    }
    let (stat_atk, stat_matk, matk_ratio) = atk_stat(main, sub, str_, int_, agi, dex);
    let atk_up = floor(number(base, "strBase") * number(base, "atkUpSTR") / 100.0)
        + floor(number(base, "dexBase") * number(base, "atkUpDEX") / 100.0)
        + floor(number(base, "intBase") * number(base, "atkUpINT") / 100.0)
        + floor(number(base, "agiBase") * number(base, "atkUpAGI") / 100.0)
        + floor(number(base, "vitBase") * number(base, "atkUpVIT") / 100.0);
    let matk_up = floor(number(base, "strBase") * number(base, "matkUpSTR") / 100.0)
        + floor(number(base, "dexBase") * number(base, "matkUpDEX") / 100.0)
        + floor(number(base, "intBase") * number(base, "matkUpINT") / 100.0)
        + floor(number(base, "agiBase") * number(base, "matkUpAGI") / 100.0)
        + floor(number(base, "vitBase") * number(base, "matkUpVIT") / 100.0);
    if sub == "마도구" {
        atk_p -= 15.0;
    }
    let mut final_atk = floor((weapon + stat_atk + level + atk_up) * (1.0 + atk_p / 100.0)) + atk_f;
    let mut final_matk = floor(
        (floor(weapon * matk_ratio) + stat_matk + level + matk_up)
            * (1.0 + (number(base, "matkP") + stat(stats, "MATKP")) / 100.0),
    ) + number(base, "matkF")
        + stat(stats, "MATK");
    let conversion_level = number(base, "conversionLevel");
    if conversion_level > 0.0 && matches!(main, "한손검" | "양손검" | "자동활" | "권갑")
    {
        let mut conversion_add = floor(weapon * conversion_level.powi(2) / 100.0);
        let mut conversion_int = 0.0;
        if main == "권갑" {
            conversion_add = floor(conversion_add / 2.0);
        } else {
            conversion_int = floor(int_ * conversion_level * 0.1);
        }
        final_matk += floor(conversion_add) + floor(conversion_int);
    }
    let dual = main == "한손검" && sub == "한손검(듀얼소드)";
    if dual {
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
    let base_crit = 25.0 + floor(number(base, "crtBase") / 3.4);
    let normal_raw =
        floor(base_crit * (1.0 + (number(base, "critP") + stat(stats, "CRITP")) / 100.0))
            + number(base, "critF")
            + stat(stats, "CRIT");
    let normal_attack_crit = (normal_raw - number(base, "bossCritResist")) as i64;
    let critical_multiplier = base
        .get("criticalChanceMultiplier")
        .and_then(Value::as_f64)
        .unwrap_or(1.0);
    let mut final_crit =
        floor((normal_raw + number(base, "criticalChanceBonus")) * critical_multiplier);
    if let Some(fixed) = base.get("fixedCriticalChance").and_then(Value::as_f64) {
        if fixed.is_finite() {
            final_crit = fixed;
        }
    }
    if number(base, "minimumCriticalDamage") != 0.0 {
        cdmg = cdmg.max(number(base, "minimumCriticalDamage"));
    }
    let armor_aspd = match text(base, "armorType") {
        "경량옷" => 50.0,
        "중량옷" => -50.0,
        _ => 0.0,
    };
    let final_aspd = (floor(
        (base_aspd(main) + floor(stat_aspd(main, sub, str_, int_, agi, dex)) + level)
            * (1.0 + (number(base, "aspdP") + stat(stats, "ASPD_P") + armor_aspd) / 100.0),
    ) + number(base, "aspdF")
        + stat(stats, "ASPD")) as i64;
    let mut stab = (number(base, "wpnStab")
        + number(base, "stability")
        + stat(stats, "STABILITY")
        + number(base, "stabilityBonus")
        + floor(physical_stability(main, str_, dex)))
    .min(100.0);
    if sub == "화살" && (main == "활" || main == "자동활") {
        stab = (stab + number(base, "subStab")).min(100.0);
    }
    let is_magic = text(base, "atkType") == "MAG";
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
    let layers = base.get("damageMultiplierLayers").unwrap_or(&Value::Null);
    let mut final_skill_mult = finite_number(layers, "skill", number(base, "skillMult"));
    let passive_damage_mult = finite_number(layers, "passive", 1.0);
    let active_damage_mult = finite_number(layers, "active", 1.0);
    let combo_damage_mult = finite_number(layers, "combo", 1.0);
    let mut final_skill_const = number(base, "skillConst");
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
    let base_power = match text(base, "attackPowerMode") {
        "sum" => final_atk + final_matk,
        "higher" => final_atk.max(final_matk),
        "atk" => final_atk,
        "wizardBlend" => final_atk * 0.25 + final_matk * 0.75,
        _ if is_magic => final_matk,
        _ => final_atk,
    };
    let mut raw = floor(
        (base_power + level - number(base, "bossLevel")) * resistance_multiplier(base, is_magic),
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
    Ok(D4NativeSummary {
        optimization_damage_factor: damage * expected_proc_multiplier(base),
        final_max_hp: max_hp,
        final_max_mp: max_mp,
        ampr_before_dual,
        normal_attack_crit,
        final_aspd,
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

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
