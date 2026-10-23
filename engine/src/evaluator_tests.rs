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
            let actual = evaluate_utility_feasible_score_from_sum(&base, &left, &right, |i, v| {
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
                    resolve_normal_attack_ampr(value, raw.get("normalAttackAmprProfile")).to_bits()
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
    assert_summary(
        evaluate_summary(
            &unsheathe,
            &json!({"UNSHEATHEP":15,"UNSHEATHE":80,"CDMG":130,"CRIT":60,"SRW":20,"PHYS_PIERCE":10}),
        )
        .unwrap(),
        CrystaOptimizationNativeSummary {
            optimization_damage_factor: 17547.0,
            final_max_hp: 22520,
            final_max_mp: 3425,
            ampr_before_dual: 244,
            normal_attack_crit: 585,
            final_aspd: 3967,
        },
    );
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
    assert_summary(
        evaluate_summary(
            &bringer,
            &json!({"ATKP":10,"ATK":20,"MATKP":12,"MATK":50,"CRIT":80,"CDMG":40,"MAG_PIERCE":15}),
        )
        .unwrap(),
        CrystaOptimizationNativeSummary {
            optimization_damage_factor: 9572.0,
            final_max_hp: 22520,
            final_max_mp: 3450,
            ampr_before_dual: 244,
            normal_attack_crit: 305,
            final_aspd: 4261,
        },
    );
}
