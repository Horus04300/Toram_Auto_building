use super::*;
use serde_json::json;

#[test]
fn local_bounds_cover_every_subspace_with_variable_bases_and_nonlinear_edges() {
    let mut patches = vec![
        json!({}),
        json!({"atkType":"MAG","mainType":"지팡이","intBase":327}),
        json!({"subType":"한손검(듀얼소드)","subAtk":100,"subStab":80}),
        json!({"mainType":"발도검","chkIsUnsheathe":true,"rangeType":"LONG"}),
        json!({"intP":-25.25,"strF":0.75,"agiBase":99,"agiP":0.5}),
        json!({"normalAttackAmprProfile":{"passive":[{"percent":13.7,"flat":-2.5,"multiplier":1.2}],"activeCandidates":[{"multiplier":2},{"flat":25}]}}),
        json!({"normalAttackAmprProfile":{"activeCandidates":[{"multiplier":-1,"flat":500}]}}),
        json!({"skillStats":[{"stat":"totalSTR","target":"mult","ratio":0.01},{"stat":"totalINT","target":"const","ratio":0.5}]}),
    ];
    for main in ["strBase", "dexBase", "agiBase", "intBase", "vitBase"] {
        for sub in ["strBase", "dexBase", "agiBase", "intBase", "vitBase"] {
            if main == sub {
                continue;
            }
            let mut patch = json!({"strBase":1,"dexBase":1,"agiBase":1,"intBase":1,"vitBase":1});
            patch[main] = json!(510);
            patch[sub] = json!(327);
            patches.push(patch);
        }
    }
    let mut tightened = 0;
    let mut impossible = 0;
    for patch in patches {
        let mut problem = small_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["skillMult"] = json!(5);
        base["skillConst"] = json!(100);
        for (key, value) in patch.as_object().unwrap() {
            base[key] = value.clone();
        }
        problem.base_context = PreparedContext::from(base);
        for (g, group) in problem.groups.iter_mut().enumerate() {
            group.packages=serde_json::from_value(json!([
                {"id":format!("{g}-a"),"statDelta":{"ATKP":30,"ATK":50,"CDMG":20,"SRW":-10,"STRP":-25,"INT":-2,"INTP":1.25,"MAXMP":100,"AMPR":15,"MAXHP":3200,"CRIT":20,"STABILITY":20}},
                {"id":format!("{g}-b"),"statDelta":{"ATKP":-15,"ATK":200,"CDMG":-10,"SRW":20,"STRP":10,"AGIP":10,"DEX":1,"INT":1,"INTP":11.25,"MAXMP":-100.25,"AMPR":-5.25,"MAXHP":-3200,"CRIT":-10,"STABILITY":-10}}
            ])).unwrap();
        }
        let raw = serde_json::to_value(&problem.groups).unwrap();
        let roots = problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let nodes: [Vec<NodeId>; 4] = std::array::from_fn(|g| {
            let end = roots
                .get(g + 1)
                .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
            (roots[g].0 as usize..end)
                .map(|n| NodeId(n as u32))
                .collect()
        });
        let mut feasible = 0;
        for a in &nodes[0] {
            for b in &nodes[1] {
                for c in &nodes[2] {
                    for d in &nodes[3] {
                        let clusters = [*a, *b, *c, *d];
                        let candidates = box_candidate_indices(&problem.trees, &clusters);
                        let local = local_box_bound(&problem, &clusters, &requirements).unwrap();
                        let mut best = f64::NEG_INFINITY;
                        for a in &candidates[0] {
                            for b in &candidates[1] {
                                for c in &candidates[2] {
                                    for d in &candidates[3] {
                                        let stats = selection_stats(&problem, &[*a, *b, *c, *d]);
                                        if let Some(actual) = evaluate_feasible_summary(
                                            &problem.base_context,
                                            &stats,
                                            |i, v| requirements.accepts_value(i, v),
                                        )
                                        .unwrap()
                                        {
                                            best = best.max(actual.optimization_damage_factor);
                                        }
                                    }
                                }
                            }
                        }
                        if best.is_finite() {
                            feasible += 1;
                            assert!(
                                local
                                    .as_ref()
                                    .expect("local bound lost a feasible subspace")
                                    .optimization_damage_factor
                                    + 1e-7
                                    >= best
                            );
                            let old = evaluate_box(&problem, &clusters, Some(&requirements))
                                .unwrap()
                                .unwrap();
                            tightened += usize::from(
                                local.unwrap().optimization_damage_factor + 1e-7
                                    < old.optimization_damage_factor,
                            );
                        } else {
                            impossible += usize::from(local.is_none());
                        }
                    }
                }
            }
        }
        assert!(feasible > 0);
        assert_eq!(serde_json::to_value(&problem.groups).unwrap(), raw);
    }
    assert!(tightened > 0);
    assert!(impossible > 0);
}

#[test]
fn local_bounds_exact_ties_order_threads_and_checkpoint_control_match_oracle() {
    let mut problem = joint_problem();
    problem.scenario_snapshot["requirements"]["maxMp"] = json!(1900);
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut oracle = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    enumerate_box_reference(
        0,
        &roots,
        &problem,
        &requirements,
        &mut [0; 4],
        &Stats::new(),
        &mut oracle,
        &mut 0,
    )
    .unwrap();
    assert!(oracle.best_selected.is_some());
    problem.metadata.experimental_local_bounds = true;
    for reversed in [false, true] {
        if reversed {
            for group in &mut problem.groups {
                group.packages.reverse();
            }
        }
        let result = solve_exact(&problem).unwrap();
        assert_eq!(result.score, Some(oracle.best_score));
        assert_eq!(result.best_build.unwrap().id, oracle.best_id);
        for threads in [1, 2, 8, 16, 64] {
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            let ready = session.ready_work_count();
            let cancel = Arc::new(AtomicBool::new(true));
            session
                .run_parallel_slice_with_control(8, threads, Some(&cancel), None)
                .unwrap();
            assert_eq!(session.ready_work_count(), ready);
            session
                .run_parallel_slice_with_control(8, threads, None, Some(Instant::now()))
                .unwrap();
            assert_eq!(session.ready_work_count(), ready);
            session.run_parallel_slice(1, threads).unwrap();
            let checkpoint = serde_json::from_str(
                &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
            )
            .unwrap();
            let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
            assert!(restored.problem.metadata.experimental_local_bounds);
            while !restored.is_complete() {
                let result = restored.run_parallel_slice(8, threads).unwrap();
                assert!(result.upper_bound.unwrap() >= oracle.best_score);
            }
            assert_eq!(restored.snapshot().score, Some(oracle.best_score));
            assert_eq!(restored.snapshot().best_build.unwrap().id, oracle.best_id);
        }
    }
}

#[test]
fn local_bounds_restrict_work_and_fall_back_without_claiming_infeasibility() {
    let mut problem = wide_problem();
    problem.metadata.experimental_local_bounds = true;
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&Value::Null);
    let ordinary = evaluate_box(&problem, &roots, Some(&requirements))
        .unwrap()
        .unwrap()
        .optimization_damage_factor;
    for incumbent in [f64::NEG_INFINITY, ordinary * 0.5, ordinary * 2.0] {
        let actual = evaluate_search_box(&problem, &roots, &requirements, incumbent)
            .unwrap()
            .unwrap();
        assert_eq!(actual.optimization_damage_factor, ordinary);
    }
    // Missing/oversized inputs disable the optional certified plan.
    problem.groups[0].packages[0]
        .stat_delta
        .insert("ATK".into(), 1e13);
    problem.prepare_trees().unwrap();
    let local = local_box_bound(&problem, &problem.trees.roots, &requirements)
        .unwrap()
        .unwrap();
    assert_eq!(local.optimization_damage_factor, f64::INFINITY);
}

#[test]
fn supply_state_joins_cover_negative_resources_and_both_join_paths() {
    let roots = [NodeId(0), NodeId(1), NodeId(2), NodeId(3)];
    for count in [3, 12] {
        let groups: Vec<Vec<_>> = (0..4)
            .map(|g| {
                (0..count)
                    .map(|i| SupplyStatePoint {
                        mp: i * 3 - 12 + g,
                        ampr: count - i - g - 3,
                        score: f64::from((i * 11 + g * 7) % 23 - 10),
                    })
                    .collect()
            })
            .collect();
        let profiles: Vec<_> = groups
            .iter()
            .map(|points| Some(state_frontier(points.clone())))
            .collect();
        let maxima = profiles
            .iter()
            .map(|p| {
                p.as_ref()
                    .unwrap()
                    .iter()
                    .copied()
                    .max_by(|a, b| a.score.total_cmp(&b.score))
            })
            .collect();
        let states = SupplyStateBounds {
            profiles,
            maxima,
            resources: std::array::from_fn(|_| Form {
                constant: 0.0,
                coefficients: [0.0; 52],
                error: 0.0,
            }),
            constant: 0.0,
            power_stage: false,
        };
        for mp in [-40, 0, 20, 100] {
            for ampr in [-20, 0, 12, 40] {
                let requirements = Requirements::new(&json!({"maxMp":mp*16,"amprBeforeDual":ampr}));
                let bound = states.score(&roots, &requirements);
                let mut best = f64::NEG_INFINITY;
                for a in &groups[0] {
                    for b in &groups[1] {
                        for c in &groups[2] {
                            for d in &groups[3] {
                                if a.mp + b.mp + c.mp + d.mp >= mp
                                    && a.ampr + b.ampr + c.ampr + d.ampr >= ampr
                                {
                                    best = best.max(a.score + b.score + c.score + d.score);
                                }
                            }
                        }
                    }
                }
                assert!(
                    bound.is_none_or(|upper| upper >= best),
                    "feasible upper lost: {count}/{mp}/{ampr}"
                );
                if best == f64::NEG_INFINITY {
                    assert_eq!(bound, Some(best));
                }
            }
        }
    }
    let points = vec![
        SupplyStatePoint {
            mp: 0,
            ampr: 0,
            score: 0.0
        };
        257
    ];
    assert!(state_pair(&points, &points).is_none());
}

#[test]
fn supply_state_bounds_cover_every_feasible_ancestor_across_contexts() {
    let mut strengthened = 0;
    let mut patches = vec![
        json!({}),
        json!({"atkType":"MAG","mainType":"지팡이","intBase":327,"strBase":1,"dexBase":1}),
        json!({"subType":"한손검(듀얼소드)","subAtk":150,"subStab":80}),
        json!({"mainType":"발도검","chkIsUnsheathe":true,"rangeType":"LONG"}),
        json!({"intBase":99,"intP":-25.25,"intF":0.75}),
        json!({"normalAttackAmprProfile":{"passive":[{"percent":13.7,"flat":-2.5,"multiplier":1.2}],"activeCandidates":[{"multiplier":2},{"flat":25}]}}),
        json!({"normalAttackAmprProfile":{"activeCandidates":[{"multiplier":-1,"flat":200}]}}),
    ];
    for main in ["strBase", "dexBase", "agiBase", "intBase", "vitBase"] {
        for sub in ["strBase", "dexBase", "agiBase", "intBase", "vitBase"] {
            if main == sub {
                continue;
            }
            let mut patch = json!({"strBase":1,"dexBase":1,"agiBase":1,"intBase":1,"vitBase":1});
            patch[main] = json!(510);
            patch[sub] = json!(327);
            patches.push(patch);
        }
    }
    for patch in patches {
        let mut problem = joint_problem();
        problem.metadata.experimental_supply_states = true;
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        for (key, value) in patch.as_object().unwrap() {
            base[key] = value.clone();
        }
        problem.base_context = PreparedContext::from(base);
        let baseline = utility_values(&problem.base_context, &Stats::new()).unwrap();
        problem.scenario_snapshot =
            json!({"requirements":{"maxMp":baseline[1]-150.0,"amprBeforeDual":baseline[2]}});
        for (g, group) in problem.groups.iter_mut().enumerate() {
            group.packages = group.packages.iter().skip(1).step_by(2).cloned().collect();
            for (i, p) in group.packages.iter_mut().enumerate() {
                for (key, value) in [
                    ("MAXMP", i as f64 * 100.0 - 125.25),
                    ("AMPR", i as f64 * 5.0 - 4.25),
                    ("STRP", i as f64 - 1.5),
                    ("INT", g as f64 * 0.5),
                    ("INTP", i as f64 * 2.25),
                    ("AGIP", i as f64),
                    ("DEX", i as f64),
                    ("VIT", g as f64),
                    ("ASPD_P", i as f64 * 3.0),
                    ("UNSHEATHE", i as f64 * 5.0),
                ] {
                    p.stat_delta.insert(key.into(), value);
                }
            }
        }
        let raw = serde_json::to_value(&problem.groups).unwrap();
        let roots = problem.prepare_trees().unwrap();
        assert!(problem.trees.states.is_some());
        assert_eq!(serde_json::to_value(&problem.groups).unwrap(), raw);
        let mut unconditioned = problem.clone();
        Arc::make_mut(&mut unconditioned.trees).states = None;
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let nodes: [Vec<NodeId>; 4] = std::array::from_fn(|g| {
            let end = roots
                .get(g + 1)
                .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
            (roots[g].0 as usize..end)
                .map(|i| NodeId(i as u32))
                .collect()
        });
        let mut feasible_count = 0;
        for a in 0..4 {
            for b in 0..4 {
                for c in 0..4 {
                    for d in 0..4 {
                        let selected = [a, b, c, d];
                        let stats = selection_stats(&problem, &selected);
                        let Some(actual) =
                            evaluate_feasible_summary(&problem.base_context, &stats, |i, v| {
                                requirements.accepts_value(i, v)
                            })
                            .unwrap()
                        else {
                            continue;
                        };
                        feasible_count += 1;
                        let ancestors: [Vec<_>; 4] = std::array::from_fn(|g| {
                            nodes[g]
                                .iter()
                                .copied()
                                .filter(|n| {
                                    let mut indices = Vec::new();
                                    cluster_indices(&problem.trees, *n, &mut indices);
                                    indices.contains(&selected[g])
                                })
                                .collect()
                        });
                        for a in &ancestors[0] {
                            for b in &ancestors[1] {
                                for c in &ancestors[2] {
                                    for d in &ancestors[3] {
                                        let box_ = [*a, *b, *c, *d];
                                        let bound =
                                            evaluate_box(&problem, &box_, Some(&requirements))
                                                .unwrap()
                                                .expect("lost feasible ancestor");
                                        assert!(
                                            bound.optimization_damage_factor + 1e-7
                                                >= actual.optimization_damage_factor
                                        );
                                        let old = evaluate_box(
                                            &unconditioned,
                                            &box_,
                                            Some(&requirements),
                                        )
                                        .unwrap()
                                        .unwrap();
                                        strengthened += usize::from(
                                            bound.optimization_damage_factor + 1e-7
                                                < old.optimization_damage_factor,
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        assert!(feasible_count > 0);
    }
    assert!(strengthened > 0, "prototype must tighten a feasible space");
}

#[test]
fn supply_state_exact_ties_order_threads_control_and_resume_match_oracle() {
    let mut problem = joint_problem();
    problem.scenario_snapshot["requirements"]["maxMp"] = json!(1900);
    let original = serde_json::to_value(&problem.groups).unwrap();
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut reference = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    enumerate_box_reference(
        0,
        &roots,
        &problem,
        &requirements,
        &mut [0; 4],
        &Stats::new(),
        &mut reference,
        &mut 0,
    )
    .unwrap();
    let oracle = solve_exact(&problem).unwrap();
    assert_eq!(oracle.score, Some(reference.best_score));
    assert_eq!(oracle.best_build.as_ref().unwrap().id, reference.best_id);
    assert!(oracle.best_build.is_some());
    problem.metadata.experimental_supply_states = true;
    for reversed in [false, true] {
        if reversed {
            for group in &mut problem.groups {
                group.packages.reverse();
            }
        }
        let serial = solve_exact(&problem).unwrap();
        assert_eq!(serial.score, oracle.score);
        assert_eq!(
            serial.best_build.unwrap().id,
            oracle.best_build.as_ref().unwrap().id
        );
        for threads in [1, 2, 8, 16, 64] {
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            assert!(session.problem.trees.states.is_some());
            let ready = session.ready_work_count();
            let cancel = Arc::new(AtomicBool::new(true));
            session
                .run_parallel_slice_with_control(8, threads, Some(&cancel), None)
                .unwrap();
            assert_eq!(session.ready_work_count(), ready);
            session
                .run_parallel_slice_with_control(8, threads, None, Some(Instant::now()))
                .unwrap();
            assert_eq!(session.ready_work_count(), ready);
            session.run_parallel_slice(1, threads).unwrap();
            let checkpoint = serde_json::from_str(
                &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
            )
            .unwrap();
            let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
            assert!(restored.problem.metadata.experimental_supply_states);
            assert!(restored.problem.trees.states.is_some());
            while !restored.is_complete() {
                let result = restored.run_parallel_slice(8, threads).unwrap();
                assert!(result.upper_bound.unwrap() >= oracle.score.unwrap());
            }
            assert_eq!(restored.snapshot().score, oracle.score);
            assert_eq!(
                restored.snapshot().best_build.unwrap().id,
                oracle.best_build.as_ref().unwrap().id
            );
        }
    }
    for group in &mut problem.groups {
        group.packages.reverse();
    }
    assert_eq!(serde_json::to_value(&problem.groups).unwrap(), original);
    // Unsupported magnitude/missing requirements disable only the new bound.
    problem.groups[0].packages[0]
        .stat_delta
        .insert("MAXMP".into(), 1e9);
    problem.prepare_trees().unwrap();
    assert!(problem.trees.states.is_none());
    problem.scenario_snapshot["requirements"]["maxMp"] = Value::Null;
    problem.prepare_trees().unwrap();
    assert!(problem.trees.states.is_none());
}

#[test]
fn cached_split_gain_matches_stronger_child_envelope_reduction() {
    for mut problem in [wide_problem(), joint_problem()] {
        problem.prepare_trees().unwrap();
        let score = |node: &TreeNode| {
            let positive = node
                .envelope
                .iter()
                .map(|(key, value)| (key.to_owned(), value.max(0.0)))
                .collect();
            heuristic_score(&positive, "damage")
        };
        let mut nonzero = 0;
        for node in &problem.trees.nodes {
            let expected = match (node.left, node.right) {
                (Some(left), Some(right)) => {
                    score(node) - score(&problem.trees[left]).min(score(&problem.trees[right]))
                }
                _ => f64::NEG_INFINITY,
            };
            assert_eq!(node.split_slack.to_bits(), expected.to_bits());
            nonzero += usize::from(expected.is_finite() && expected != 0.0);
        }
        if problem.trees.joint.is_some() {
            assert!(nonzero > 0);
        }
    }
}

#[test]
fn split_order_isolates_a_weaker_child_and_preserves_cartesian_coverage() {
    let mut problem = small_problem();
    for (g, values) in [vec![1.0, 3.0], vec![0.0, 10.0], vec![2.0; 4], vec![1.0]]
        .into_iter()
        .enumerate()
    {
        problem.groups[g].packages = values
            .into_iter()
            .enumerate()
            .map(|(i, value)| NativePackage {
                id: format!("{g}-{i}"),
                evaluation_delta: None,
                search_values: Vec::new(),
                stat_delta: Stats::from([("ATKP".into(), value)]),
            })
            .collect();
    }
    let roots = problem.prepare_trees().unwrap();
    // The old max-child reduction is zero in all three available groups
    // and picks the four-package group. The new score exposes the 0/10
    // tradeoff first, followed by 1/3, with no per-box extra evaluations.
    for root in &roots[..3] {
        let node = &problem.trees[*root];
        assert_eq!(
            node.split_score
                - problem.trees[node.left.unwrap()]
                    .split_score
                    .max(problem.trees[node.right.unwrap()].split_score),
            0.0
        );
    }
    assert_eq!(split_indices(&problem.trees, &roots), [Some(1), Some(0)]);
    let mut covered = HashSet::new();
    for child in ChildBoxes::new(&problem.trees, &roots) {
        let candidates: [Vec<usize>; 4] = std::array::from_fn(|g| {
            let mut out = Vec::new();
            cluster_indices(&problem.trees, child[g], &mut out);
            out
        });
        for a in &candidates[0] {
            for b in &candidates[1] {
                for c in &candidates[2] {
                    for d in &candidates[3] {
                        assert!(covered.insert([*a, *b, *c, *d]), "overlapping child boxes");
                    }
                }
            }
        }
    }
    assert_eq!(
        covered.len(),
        16,
        "every parent combination must survive the split"
    );
}

fn workload_branch_problem() -> NativeProblem {
    let mut problem = small_problem();
    let groups = [
        vec![Stats::new(), Stats::from([("ATKP".into(), 40.0)])],
        vec![
            Stats::from([("ATKP".into(), 20.0)]),
            Stats::from([("MATKP".into(), 20.0)]),
        ],
        vec![
            Stats::new(),
            Stats::new(),
            Stats::from([("ATKP".into(), 25.0)]),
            Stats::from([("ATKP".into(), 25.0)]),
        ],
        vec![Stats::from([("ATKP".into(), 1.0)])],
    ];
    for (g, stats) in groups.into_iter().enumerate() {
        problem.groups[g].packages = stats
            .into_iter()
            .enumerate()
            .map(|(i, stat_delta)| NativePackage {
                id: format!("{g}-{i}"),
                evaluation_delta: None,
                search_values: Vec::new(),
                stat_delta,
            })
            .collect();
    }
    problem
}

#[test]
fn gap_branching_balances_children_and_accounts_for_candidate_counts() {
    let mut problem = workload_branch_problem();
    let roots = problem.prepare_trees().unwrap();
    // Group 0 isolates a 40k loss in one candidate; group 1 loses 20k
    // in both candidates; group 2 isolates a 25k loss in two candidates.
    // A far incumbent rewards group 2's larger reduction footprint.
    // Near the incumbent, surplus loss is capped and both group 1
    // children matter. The original one-child ranking does neither.
    assert_eq!(split_indices(&problem.trees, &roots), [Some(0), Some(2)]);
    assert_eq!(
        ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 0.0).splits,
        [Some(2), Some(1)]
    );
    assert_eq!(
        ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 99.0).splits,
        [Some(1), Some(2)]
    );
}

#[test]
fn gap_branching_keeps_fallback_for_unavailable_nonfinite_and_closed_gaps() {
    let mut problem = workload_branch_problem();
    let roots = problem.prepare_trees().unwrap();
    let fallback = split_indices(&problem.trees, &roots);
    for (upper, best) in [
        (100.0, f64::NEG_INFINITY),
        (f64::INFINITY, 99.0),
        (100.0, f64::NAN),
        (f64::NAN, 99.0),
        (100.0, 100.0),
        (100.0, 101.0),
        (0.0, -1.0),
        (-1.0, -2.0),
    ] {
        assert_eq!(
            ChildBoxes::with_score_gap(&problem.trees, &roots, upper, best).splits,
            fallback
        );
    }
    for id in roots {
        Arc::make_mut(&mut problem.trees).nodes[id.0 as usize].split_score = 0.0;
    }
    assert_eq!(
        ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 99.0).splits,
        fallback
    );
    Arc::make_mut(&mut problem.trees).nodes[roots[0].0 as usize].split_score = f64::INFINITY;
    assert_eq!(
        ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 99.0).splits,
        fallback
    );
}

#[test]
fn gap_branching_preserves_all_combinations_when_incumbent_changes() {
    let mut problem = workload_branch_problem();
    let roots = problem.prepare_trees().unwrap();
    for offset in 0..4 {
        let mut pending = vec![roots];
        let mut covered = HashSet::new();
        let mut visited = 0;
        while let Some(clusters) = pending.pop() {
            let best = [f64::NEG_INFINITY, 0.0, 99.0, 100.0][(visited + offset) % 4];
            visited += 1;
            let children = ChildBoxes::with_score_gap(&problem.trees, &clusters, 100.0, best);
            if children.len() == 0 {
                let selected = std::array::from_fn::<_, GROUP_COUNT, _>(|g| {
                    problem.trees[clusters[g]].package.unwrap()
                });
                assert!(
                    covered.insert(selected),
                    "adaptive split overlaps another child"
                );
            } else {
                pending.extend(children);
            }
        }
        let expected: HashSet<_> = (0..2)
            .flat_map(|a| (0..2).flat_map(move |b| (0..4).map(move |c| [a, b, c, 0])))
            .collect();
        assert_eq!(
            covered, expected,
            "changing gap must preserve all 16 completions exactly once"
        );
    }
}

#[test]
fn impossible_children_skip_stat_evaluation_and_frontier_insertion() {
    let mut problem = joint_problem();
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut pending = vec![roots];
    let mut checked = 0;
    let incumbent = SharedIncumbent {
        score_bits: AtomicU64::new(f64::NEG_INFINITY.to_bits()),
        record: Mutex::new(SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        }),
    };
    while let Some(clusters) = pending.pop() {
        if !problem.trees.joint_utilities_possible(&clusters)
            || box_combinations(&problem.trees, &clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT
        {
            continue;
        }
        let boxes: Vec<_> = ChildBoxes::new(&problem.trees, &clusters).collect();
        let impossible = boxes
            .iter()
            .filter(|child| !problem.trees.joint_utilities_possible(child))
            .count();
        if impossible > 0 {
            let mut counters = LocalSearchCounters {
                joint_probes: 8,
                joint_rejections: 8,
                ..LocalSearchCounters::default()
            };
            let mut children = Vec::new();
            assert!(expand_parallel_node_inner(
                &WorkItem {
                    upper: f64::INFINITY,
                    clusters
                },
                LOOKAHEAD_MAX_DEPTH,
                &problem,
                &requirements,
                &incumbent,
                &mut counters,
                None,
                None,
                &mut children
            )
            .unwrap());
            assert_eq!(counters.evaluations, (boxes.len() - impossible) as u64);
            assert!(counters.pruned_by_constraint >= impossible as u64);
            assert!(children
                .iter()
                .all(|child| problem.trees.joint_utilities_possible(&child.clusters)));
            checked += 1;
        }
        pending.extend(boxes);
    }
    assert!(
        checked > 0,
        "must exercise branches rejected before evaluator calls"
    );
}

#[test]
fn joint_pressure_requires_observed_rejections_and_turns_off_when_rare() {
    let mut counters = LocalSearchCounters::default();
    for i in 0..8 {
        assert!(!counters.joint_pressure());
        counters.count_joint_probe(i < 2);
    }
    assert!(counters.joint_pressure());
    for _ in 0..8 {
        counters.count_joint_probe(false);
    }
    assert!(!counters.joint_pressure());
    counters.count_joint_probe(true);
    assert!(counters.joint_pressure());
    // Probe statistics do not fabricate full evaluations or deletions.
    assert_eq!(counters.evaluations, 0);
    assert_eq!(counters.pruned_by_constraint, 0);
}

fn joint_problem() -> NativeProblem {
    let mut problem = wide_problem();
    let mut base = serde_json::to_value(&problem.base_context).unwrap();
    base["critF"] = json!(0);
    base["amprF"] = json!(0);
    base["skillMult"] = json!(1);
    problem.base_context = PreparedContext::from(base);
    problem.scenario_snapshot =
        json!({"requirements":{"amprBeforeDual":66,"normalAttackCrit":100}});
    for (g, group) in problem.groups.iter_mut().enumerate() {
        for (i, package) in group.packages.iter_mut().enumerate() {
            // Conflicting supply, forced penalties, duplicate score/ID ties,
            // percentage critical contribution, and MP-dependent AMPR.
            let n = (i / 2) as f64;
            package.stat_delta = Stats::from([
                ("AMPR".into(), n * 9.0 - 3.0),
                ("CRIT".into(), 42.0 - n * 15.0),
                ("CRITP".into(), if i % 2 == 0 { -20.0 } else { 0.0 }),
                ("MAXMP".into(), if g % 2 == 0 { -100.0 } else { 100.0 }),
                ("ATKP".into(), n * 7.0),
            ]);
        }
    }
    problem
}

#[test]
fn joint_bound_covers_every_feasible_completion_and_cuts_conflicting_boxes() {
    let mut total_cuts = 0;
    for (crt, crit, ampr, mp) in [
        (0, 100.0, 66.0, 2000),
        (34, 95.5, 65.5, 1900),
        (100, 100.0, 70.0, 1500),
    ] {
        let mut problem = joint_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["crtBase"] = json!(crt);
        base["maxMpF"] = json!(mp);
        problem.base_context = PreparedContext::from(base);
        problem.scenario_snapshot["requirements"]["normalAttackCrit"] = json!(crit);
        problem.scenario_snapshot["requirements"]["amprBeforeDual"] = json!(ampr);
        let roots = problem.prepare_trees().unwrap();
        let joint = problem
            .trees
            .joint
            .as_ref()
            .expect("fixture must activate bound");
        let nodes: [Vec<NodeId>; 4] = std::array::from_fn(|g| {
            let end = roots
                .get(g + 1)
                .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
            (roots[g].0 as usize..end)
                .map(|i| NodeId(i as u32))
                .collect()
        });
        let mut feasible_boxes = HashSet::new();
        let mut feasible_completions = 0;
        for a in 0..8 {
            for b in 0..8 {
                for c in 0..8 {
                    for d in 0..8 {
                        let selected = [a, b, c, d];
                        let utility = utility_values(
                            &problem.base_context,
                            &selection_stats(&problem, &selected),
                        )
                        .unwrap();
                        if utility[2] < ampr || utility[3] < crit {
                            continue;
                        }
                        feasible_completions += 1;
                        let ancestors: [Vec<NodeId>; 4] = std::array::from_fn(|g| {
                            nodes[g]
                                .iter()
                                .copied()
                                .filter(|n| {
                                    let mut indices = Vec::new();
                                    cluster_indices(&problem.trees, *n, &mut indices);
                                    indices.contains(&selected[g])
                                })
                                .collect()
                        });
                        for a in &ancestors[0] {
                            for b in &ancestors[1] {
                                for c in &ancestors[2] {
                                    for d in &ancestors[3] {
                                        let box_ = [*a, *b, *c, *d];
                                        assert!(joint.possible(&box_), "feasible completion lost");
                                        feasible_boxes.insert(box_.map(|n| n.0));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        assert!(feasible_completions > 0);
        for a in &nodes[0] {
            for b in &nodes[1] {
                for c in &nodes[2] {
                    for d in &nodes[3] {
                        let box_ = [*a, *b, *c, *d];
                        if joint.possible(&box_) {
                            continue;
                        }
                        assert!(!feasible_boxes.contains(&box_.map(|n| n.0)));
                        let utility = utility_values(
                            &problem.base_context,
                            &box_stats(&problem.trees, &box_),
                        )
                        .unwrap();
                        if utility[2] >= ampr && utility[3] >= crit {
                            total_cuts += 1;
                        }
                    }
                }
            }
        }
    }
    assert!(total_cuts > 0, "must tighten independent utility envelopes");
}

#[test]
fn joint_bound_preserves_oracle_ties_order_threads_and_checkpoint_resume() {
    let mut problem = joint_problem();
    problem.metadata.initial_package_ids =
        vec!["0-3".into(), "1-3".into(), "2-5".into(), "3-5".into()];
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut oracle = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    enumerate_box_reference(
        0,
        &roots,
        &problem,
        &requirements,
        &mut [0; 4],
        &Stats::new(),
        &mut oracle,
        &mut 0,
    )
    .unwrap();
    assert!(oracle.best_selected.is_some());
    for reverse in [false, true] {
        if reverse {
            for group in &mut problem.groups {
                group.packages.reverse();
            }
        }
        let serial = solve_exact(&problem).unwrap();
        assert_eq!(serial.score, Some(oracle.best_score));
        assert_eq!(serial.best_build.unwrap().id, oracle.best_id);
        for threads in [1, 2, 8, 16, 64] {
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            let ready = session.ready_work_count();
            let cancel = Arc::new(AtomicBool::new(true));
            session
                .run_parallel_slice_with_control(8, threads, Some(&cancel), None)
                .unwrap();
            assert_eq!(session.ready_work_count(), ready);
            session
                .run_parallel_slice_with_control(8, threads, None, Some(Instant::now()))
                .unwrap();
            assert_eq!(session.ready_work_count(), ready);
            session.run_parallel_slice(1, threads).unwrap();
            let checkpoint = serde_json::from_str(
                &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
            )
            .unwrap();
            let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
            assert!(restored.problem.trees.joint.is_some());
            while !restored.is_complete() {
                let result = restored.run_parallel_slice(8, threads).unwrap();
                assert!(result.upper_bound.unwrap() >= oracle.best_score);
            }
            assert_eq!(restored.snapshot().score, Some(oracle.best_score));
            assert_eq!(restored.snapshot().best_build.unwrap().id, oracle.best_id);
        }
    }
}

#[test]
fn constrained_offense_covers_feasible_scores_in_every_ancestor_box() {
    let mut tightened = 0;
    for (case, patch) in [
        json!({}),
        json!({"atkType":"MAG","mainType":"지팡이","intBase":200}),
        json!({"rangeType":"LONG","mainType":"발도검","chkIsUnsheathe":true}),
        json!({"subType":"한손검(듀얼소드)","subAtk":100,"subStab":80}),
        json!({"normalAttackAmprProfile":{"activeCandidates":[{"id":"Blade:8","flat":25,"percent":0,"multiplier":1}]}}),
        json!({"normalAttackAmprProfile":{"passive":[{"percent":13.7,"flat":-2.5,"multiplier":1.2}],"activeCandidates":[{"id":"a","multiplier":2},{"id":"b","flat":25}]}}),
        json!({"normalAttackAmprProfile":{"passive":[{"percent":-25,"multiplier":0.75,"flat":50}],"activeCandidates":[{"id":"a","multiplier":0,"flat":100}]}}),
        json!({"normalAttackAmprProfile":{"activeCandidates":[{"id":"a","multiplier":-1,"flat":200}]}}),
        json!({}),
        json!({}),
        json!({}),
        json!({"crtBase":-100,"critF":300}),
        json!({"intBase":-100,"maxMpF":1900}),
        json!({}),
    ].into_iter().enumerate() {
        let mut problem = joint_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        for (key, value) in patch.as_object().unwrap() {
            base[key] = value.clone();
        }
        problem.base_context = PreparedContext::from(base);
        problem.scenario_snapshot["requirements"]["normalAttackCrit"] = json!(95.5);
        problem.scenario_snapshot["requirements"]["amprBeforeDual"] = json!(65.5);
        if case == 9 { problem.scenario_snapshot["requirements"]["amprBeforeDual"] = Value::Null; }
        if case == 10 { problem.scenario_snapshot["requirements"]["normalAttackCrit"] = Value::Null; }
        for group in &mut problem.groups {
            for (i, package) in group.packages.iter_mut().enumerate() {
                let n = (i / 2) as f64;
                for (key, value) in [
                    ("ATKP", n * 7.0 - 4.0),
                    ("MATKP", n * 7.0 - 4.0),
                    ("SRW", 9.0 - n * 4.0),
                    ("LRW", 9.0 - n * 4.0),
                    ("CDMG", n * 3.0 - 7.0),
                ] {
                    package.stat_delta.insert(key.into(), value);
                }
                if case >= 8 {
                    for (key, delta) in [("AMPR",0.1),("CRIT",-0.25),("CRITP",0.125),("ATKP",0.5),("CDMG",-0.1)] {
                        let value=package.stat_delta.get(key).copied().unwrap_or(0.0);
                        package.stat_delta.insert(key.into(),value+delta);
                    }
                }
                if case == 12 { package.stat_delta.insert("INTP".into(), n*20.0-30.0); }
                if case == 13 {
                    package.stat_delta.insert("CRITP".into(),n*3000.125);
                    package.stat_delta.insert("ATKP".into(),n*1_000_001.5);
                }
            }
        }
        let roots = problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let joint = problem.trees.joint.as_ref().unwrap();
        let ancestors: [Vec<Vec<NodeId>>; 4] = std::array::from_fn(|g| {
            let end = roots
                .get(g + 1)
                .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
            (0..8)
                .map(|selected| {
                    (roots[g].0 as usize..end)
                        .map(|n| NodeId(n as u32))
                        .filter(|n| {
                            let mut indices = Vec::new();
                            cluster_indices(&problem.trees, *n, &mut indices);
                            indices.contains(&selected)
                        })
                        .collect()
                })
                .collect()
        });
        let mut bounds = BTreeMap::new();
        let mut feasible_count = 0;
        for a in 0..8 {
            for b in 0..8 {
                for c in 0..8 {
                    for d in 0..8 {
                        let selected = [a, b, c, d];
                        let actual = selection_stats(&problem, &selected);
                        let Some(summary) = evaluate_feasible_summary(
                            &problem.base_context,
                            &actual,
                            |i, v| requirements.accepts_value(i, v),
                        )
                        .unwrap() else {
                            continue;
                        };
                        feasible_count += 1;
                        for a in &ancestors[0][a] {
                            for b in &ancestors[1][b] {
                                for c in &ancestors[2][c] {
                                    for d in &ancestors[3][d] {
                                        let box_ = [*a, *b, *c, *d];
                                        assert!(joint.possible(&box_), "feasible completion pruned in case {case}");
                                        let (stats,upper)=bounds.entry(box_).or_insert_with(|| {
                    let mut plain = box_.iter().fold(Stats::new(),|sum,node|add_stats(sum,&problem.trees[*node].envelope));
                    let original=plain.clone();joint.tighten_offense(&box_,&mut plain);
                    let mut reference=original.clone();
                    joint.tighten_offense_reference(&box_,&mut reference);
                    for key in joint.offense.keys {
                        assert_eq!(plain.get(key).map(|v|v.to_bits()), reference.get(key).map(|v|v.to_bits()), "offense bound differs in case {case}: {key}");
                    }
                    if plain != original {tightened += 1;}
                    let score=evaluate_feasible_summary(&problem.base_context,&plain,|i,v|requirements.accepts_value(i,v)).unwrap().expect("feasible completion requires a feasible envelope").optimization_damage_factor;
                    (plain,score)
                });
                                        for key in joint.offense.keys {
                                            assert!(
                                                stats.get(key).copied().unwrap_or(0.0)
                                                    >= actual.get(key).copied().unwrap_or(0.0),
                                                "feasible coordinate clipped: {key}"
                                            );
                                        }
                                        assert!(
                                            *upper >= summary.optimization_damage_factor,
                                            "feasible damage exceeds tightened upper"
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        assert!(feasible_count > 0);
    }
    assert!(tightened > 0, "must tighten a coordinate envelope");
}

#[test]
fn axis_offense_bounds_tighten_when_the_other_utility_is_slack() {
    for constrained in ["AMPR", "CRIT"] {
        let mut problem = joint_problem();
        // Synthetic proof fixture only: lower the other goal below base
        // supply, without adding bonuses to any measured user input.
        let slack_goal = if constrained == "AMPR" {
            "normalAttackCrit"
        } else {
            "amprBeforeDual"
        };
        problem.scenario_snapshot["requirements"][slack_goal] = json!(1);
        for group in &mut problem.groups {
            for (i, package) in group.packages.iter_mut().enumerate() {
                let supply = (i / 2) as f64 * 10.0;
                let slack = if i % 2 == 0 { 100.0 } else { 0.0 };
                package.stat_delta = Stats::from([
                    (constrained.into(), supply),
                    (
                        (if constrained == "AMPR" {
                            "CRIT"
                        } else {
                            "AMPR"
                        })
                        .into(),
                        slack,
                    ),
                    ("ATKP".into(), 30.0 - supply),
                ]);
            }
        }
        let roots = problem.prepare_trees().unwrap();
        let joint = problem.trees.joint.as_ref().unwrap();
        let p = roots.iter().map(|n| joint.crit_p[n.0 as usize]).sum();
        let minima = &joint.minima[joint.bucket_index(p)];
        let mut legacy = f64::INFINITY;
        for (scale, k) in OFFENSE_SCALES.into_iter().enumerate() {
            for (direction, minimum) in minima.iter().enumerate().take(MIXED_DIRECTIONS) {
                let index = scale * JOINT_DIRECTIONS + direction;
                let support: f64 = roots
                    .iter()
                    .map(|n| joint.offense.maxima[n.0 as usize][0][index])
                    .sum();
                legacy = legacy.min(((support - minimum) / k).floor());
            }
        }
        let mut stats = roots.iter().fold(Stats::new(), |sum, node| {
            add_stats(sum, &problem.trees[*node].envelope)
        });
        legacy = legacy.min(stats["ATKP"]);
        joint.tighten_offense(&roots, &mut stats);
        assert!(
            stats["ATKP"] < legacy,
            "axis direction must tighten {constrained} tradeoff"
        );
        // Compare exact search with exhaustive completion enumeration as well.
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut expected = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; 4],
            &Stats::new(),
            &mut expected,
            &mut 0,
        )
        .unwrap();
        assert!(expected.best_selected.is_some());
        let result = solve_exact(&problem).unwrap();
        assert_eq!(result.score, Some(expected.best_score));
        assert_eq!(result.best_build.unwrap().id, expected.best_id);
    }
}

#[test]
fn offense_kernel_matches_reference_for_every_direction_and_raw_cap() {
    let mut problem = joint_problem();
    let roots = problem.prepare_trees().unwrap();
    let mut joint = problem.trees.joint.as_ref().unwrap().clone();
    joint.crit_p.fill(0.0);
    joint.minima.fill([0.0; JOINT_DIRECTIONS]);
    joint.offense.axis_enabled = [true; 3];
    for direction in 0..OFFENSE_DIRECTIONS {
        for support in [-9.0, -1.0, 0.0, 1.0, 9.0] {
            for (group, node) in roots.iter().enumerate() {
                for maxima in &mut joint.offense.maxima[node.0 as usize] {
                    maxima.fill(1_000_000.0);
                    maxima[direction] = if group == 0 { support } else { 0.0 };
                }
            }
            for unit in [1.0, 1.0 / 1024.0, 1_048_576.0] {
                for coordinate in joint.offense.coordinates.iter_mut().flatten() {
                    coordinate.unit = unit;
                }
                for mask in 0..8 {
                    joint.offense.enabled = std::array::from_fn(|i| mask & (1 << i) != 0);
                    for original in [-0.0, 0.0, -64.125, 64.125] {
                        // Both omitted and present coordinates preserve their raw cap.
                        for omitted in 0..=3 {
                            let mut actual = Stats::new();
                            for (i, key) in joint.offense.keys.iter().enumerate() {
                                if i != omitted {
                                    actual.insert((*key).into(), original);
                                }
                            }
                            let mut reference = actual.clone();
                            joint.tighten_offense(&roots, &mut actual);
                            joint.tighten_offense_reference(&roots, &mut reference);
                            for key in joint.offense.keys {
                                assert_eq!(actual.get(key).map(|v| v.to_bits()), reference.get(key).map(|v| v.to_bits()), "direction={direction}, unit={unit}, mask={mask}, cap={original}");
                            }
                        }
                    }
                }
            }
        }
    }
}

#[test]
fn constrained_offense_relaxes_fractional_and_large_coordinates_without_changing_raw() {
    for value in [0.5, 1_000_001.0] {
        let mut problem = joint_problem();
        problem.groups[0].packages[0]
            .stat_delta
            .insert("ATKP".into(), value);
        let original = serde_json::to_value(&problem).unwrap();
        let roots = problem.prepare_trees().unwrap();
        let joint = problem.trees.joint.as_ref().unwrap();
        assert!(joint.offense.enabled[0]);
        let mut stats = roots.iter().fold(Stats::new(), |sum, node| {
            add_stats(sum, &problem.trees[*node].envelope)
        });
        joint.tighten_offense(&roots, &mut stats);
        assert!(stats.get("ATKP").copied().unwrap().is_finite());
        assert_eq!(serde_json::to_value(&problem).unwrap(), original);
    }
    let mut problem = joint_problem();
    problem.metadata.modeled_keys = vec!["CRIT".into()];
    let roots = problem.prepare_trees().unwrap();
    assert_eq!(box_stats(&problem.trees, &roots).get("ATKP"), None);
}

#[test]
fn joint_bound_supports_previous_bypasses_without_changing_packages() {
    for patch in [
        json!({"AMPR":0.5}),
        json!({"CRIT":0.5}),
        json!({"CRITP":0.5}),
        json!({"CRITP":10000}),
        json!({"AMPR":1000001}),
    ] {
        let mut problem = joint_problem();
        for (key, value) in patch.as_object().unwrap() {
            problem.groups[0].packages[0]
                .stat_delta
                .insert(key.clone(), value.as_f64().unwrap());
        }
        let raw = serde_json::to_value(&problem).unwrap();
        problem.prepare_trees().unwrap();
        assert!(problem.trees.joint.is_some());
        assert_eq!(serde_json::to_value(&problem).unwrap(), raw);
    }
    for patch in [
        json!({"intBase":-1}),
        json!({"crtBase":-1}),
        json!({"amprF":1000}),
        json!({"normalAttackAmprProfile":{"passive":[{"percent":10}]}}),
    ] {
        let mut problem = joint_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base.as_object_mut()
            .unwrap()
            .extend(patch.as_object().unwrap().clone());
        problem.base_context = PreparedContext::from(base);
        problem.prepare_trees().unwrap();
        assert!(problem.trees.joint.is_some());
    }
    // Additional bound does not inherit an incomplete split-key list.
    let mut problem = joint_problem();
    problem.metadata.modeled_keys = vec!["ATKP".into()];
    problem.prepare_trees().unwrap();
    assert!(problem.trees.joint.is_some());
}

#[test]
fn generalized_bounds_match_oracle_and_resume_with_real_modifier_forms() {
    for profile in [
        json!({"activeCandidates":[{"id":"Blade:8","flat":25}]}),
        json!({"passive":[{"percent":-25,"flat":50,"multiplier":0.75}],"activeCandidates":[{"id":"z","multiplier":1.2},{"id":"a","flat":25}]}),
    ] {
        let mut problem = joint_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["normalAttackAmprProfile"] = profile;
        problem.base_context = PreparedContext::from(base);
        for group in &mut problem.groups {
            for package in &mut group.packages {
                let ampr = package.stat_delta.get("AMPR").copied().unwrap();
                package.stat_delta.insert("AMPR".into(), ampr + 0.125);
                package.stat_delta.insert("CDMG".into(), 0.25);
            }
        }
        let roots = problem.prepare_trees().unwrap();
        assert!(problem.trees.joint.is_some());
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut oracle = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; 4],
            &Stats::new(),
            &mut oracle,
            &mut 0,
        )
        .unwrap();
        assert!(oracle.best_selected.is_some());
        for group in &mut problem.groups {
            group.packages.reverse();
        }
        let serial = solve_exact(&problem).unwrap();
        assert_eq!(serial.score, Some(oracle.best_score));
        assert_eq!(serial.best_build.unwrap().id, oracle.best_id);
        for threads in [1, 4, 64] {
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            session.run_parallel_slice(1, threads).unwrap();
            let mut session =
                NativeSearchSession::from_checkpoint(session.checkpoint().unwrap()).unwrap();
            while !session.is_complete() {
                let result = session.run_parallel_slice(16, threads).unwrap();
                assert!(result.upper_bound.unwrap() >= oracle.best_score);
            }
            assert_eq!(session.snapshot().score, Some(oracle.best_score));
            assert_eq!(session.snapshot().best_build.unwrap().id, oracle.best_id);
        }
    }
}

#[test]
fn joint_bound_proves_infeasibility_without_fabricating_an_incumbent() {
    let mut problem = joint_problem();
    for group in &mut problem.groups {
        for package in &mut group.packages {
            package
                .stat_delta
                .insert("CRIT".into(), package.stat_delta["CRIT"] - 4.0);
        }
    }
    let serial = solve_exact(&problem).unwrap();
    assert_eq!(serial.status, "invalid");
    assert!(serial.score.is_none());
    let mut session = NativeSearchSession::new(problem).unwrap();
    assert!(session.problem.trees.joint.is_some());
    assert_eq!(session.snapshot().status, "no-incumbent-yet");
    session
        .run_parallel_slice_with_control(8, 4, None, Some(Instant::now()))
        .unwrap();
    assert_eq!(session.snapshot().status, "no-incumbent-yet");
    while !session.is_complete() {
        session.run_parallel_slice(8, 4).unwrap();
    }
    let result = session.snapshot();
    assert_eq!(result.status, "invalid");
    assert!(result.best_build.is_none());
}

#[test]
fn arena_layout_capacity_and_path_restore_are_checked() {
    assert_eq!(std::mem::size_of::<WorkItem>(), 24);
    assert_eq!(tree_capacity([1, 2, 3, 4]).unwrap(), 16);
    assert!(tree_capacity([0]).is_err());
    assert!(tree_capacity([usize::MAX]).is_err());
    assert!(tree_capacity([u32::MAX as usize, 1]).is_err());
    let mut problem = wide_problem();
    let roots = problem.prepare_trees().unwrap();
    let arena = &problem.trees;
    assert_eq!(arena.nodes.len(), 4 * (2 * 8 - 1));
    for group in 0..GROUP_COUNT {
        let start = roots[group].0 as usize;
        let end = roots
            .get(group + 1)
            .map_or(arena.nodes.len(), |id| id.0 as usize);
        for index in start..end {
            let id = NodeId(index as u32);
            let node = &arena[id];
            assert_eq!(find_tree_node(arena, roots[group], &node.path), Some(id));
            if let (Some(left), Some(right)) = (node.left, node.right) {
                assert_eq!(left.0, id.0 + 1);
                assert_eq!(right.0, left.0 + (2 * arena[left].size - 1) as u32);
                assert_eq!(node.size, arena[left].size + arena[right].size);
            }
            for other in index..end {
                assert_eq!(
                    id.cmp(&NodeId(other as u32)),
                    node.path.cmp(&arena.nodes[other].path)
                );
            }
        }
        for invalid in ["", "x", "r2", "r0000", "r0x"] {
            assert_eq!(find_tree_node(arena, roots[group], invalid), None);
        }
    }
    let clone = problem.clone();
    assert!(Arc::ptr_eq(&clone.trees, &problem.trees));
    let wire = serde_json::to_value(&problem).unwrap();
    assert!(wire.get("trees").is_none());
    let restored: NativeProblem = serde_json::from_value(wire).unwrap();
    assert!(restored.trees.nodes.is_empty());
}

#[test]
fn projected_search_preserves_raw_output_and_rebuilds_after_checkpoint() {
    let mut problem = wide_problem();
    for group in &mut problem.groups {
        for (index, package) in group.packages.iter_mut().enumerate() {
            package.stat_delta = Stats::from([
                ("ATKP".into(), 1.0),
                ("MAXMP".into(), -20.0),
                ("MOTIONSPEED".into(), 7.5),
                ("DROP_RATE".into(), index as f64 + 2.0),
                ("PHYS_RES".into(), -3.25),
                ("UNKNOWN_FUTURE".into(), -0.0),
            ]);
        }
    }
    // Tree/order metadata is deliberately narrower than evaluator dependencies.
    problem.metadata.modeled_keys = vec!["ATKP".into()];
    let original = serde_json::to_value(&problem).unwrap();
    let expected_stats = selection_stats(&problem, &[0; GROUP_COUNT]);
    let expected_score = evaluate_summary_from_map(&problem.base_context, &expected_stats)
        .unwrap()
        .optimization_damage_factor;
    let check = |result: NativeSolveResult| {
        assert!(result.exact);
        assert_eq!(result.score, Some(expected_score));
        assert_eq!(result.upper_bound, Some(expected_score));
        let build = result.best_build.unwrap();
        assert_eq!(build.id, build_id(&problem.groups, &[0; GROUP_COUNT]));
        assert_eq!(build.stat_delta, expected_stats);
    };
    check(solve_exact(&problem).unwrap());
    for threads in [1, 4, 64] {
        check(solve_exact_parallel(&problem, threads).unwrap().result);
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        assert_eq!(serde_json::to_value(&session.problem).unwrap(), original);
        let package = &session.problem.groups[0].packages[0];
        assert_eq!(package.evaluation_stats().get("DROP_RATE"), None);
        assert_eq!(package.evaluation_stats().get("MAXMP"), Some(&-20.0));
        assert_eq!(package.evaluation_stats().get("MOTIONSPEED"), Some(&7.5));
        session.run_parallel_slice(1, threads).unwrap();
        let wire = serde_json::to_value(session.checkpoint().unwrap()).unwrap();
        assert_eq!(wire["problem"], original);
        let checkpoint: NativeSearchCheckpoint = serde_json::from_value(wire).unwrap();
        assert!(checkpoint.problem.groups[0].packages[0]
            .evaluation_delta
            .is_none());
        let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
        assert!(restored.problem.groups[0].packages[0]
            .evaluation_delta
            .is_some());
        while !restored.is_complete() {
            restored.run_parallel_slice(128, threads).unwrap();
        }
        check(restored.snapshot());
    }
    assert_eq!(serde_json::to_value(problem).unwrap(), original);
}

#[test]
fn local_counter_overflow_and_merge_match_atomic_counts() {
    let mut local = LocalSearchCounters::default();
    let shared = ParallelCounters::default();
    macro_rules! check {
        ($field:ident, $increment:ident) => {
            local.$field = u64::MAX;
            shared.$field.store(u64::MAX, AtomicOrdering::Relaxed);
            local.$increment();
            (&shared).$increment();
            assert_eq!(local.$field, shared.$field.load(AtomicOrdering::Relaxed));
            assert_eq!(local.$field, 0);
            local.$increment();
        };
    }
    check!(evaluations, count_evaluations);
    check!(visited, count_visited);
    check!(pruned_by_bound, count_pruned_by_bound);
    check!(pruned_by_constraint, count_pruned_by_constraint);
    check!(enumerated, count_enumerated);
    check!(splits, count_splits);
    shared.merge_search_counts(local);
    for counter in [
        &shared.evaluations,
        &shared.visited,
        &shared.pruned_by_bound,
        &shared.pruned_by_constraint,
        &shared.enumerated,
        &shared.splits,
    ] {
        assert_eq!(counter.load(AtomicOrdering::Relaxed), 1);
    }
    assert_eq!(shared.steals.load(AtomicOrdering::Relaxed), 0);
}

#[test]
fn prepared_requirements_preserve_missing_invalid_and_boundary_values() {
    let summary = CrystaOptimizationNativeSummary {
        optimization_damage_factor: 1.0,
        final_max_hp: 100,
        final_max_mp: 200,
        ampr_before_dual: 30,
        normal_attack_crit: 40,
        final_aspd: 500,
    };
    let keys = [
        "maxHp",
        "maxMp",
        "amprBeforeDual",
        "normalAttackCrit",
        "aspd",
    ];
    let values = [100., 200., 30., 40., 500.];
    for (key, limit) in keys.iter().zip(values) {
        for value in [
            Value::Null,
            json!("100"),
            json!(false),
            json!(limit - 0.5),
            json!(limit),
            json!(limit + 0.5),
        ] {
            let input = json!({*key: value});
            let expected = keys.iter().zip(values).all(|(key, actual)| {
                input
                    .get(key)
                    .and_then(Value::as_f64)
                    .is_none_or(|required| actual >= required)
            });
            assert_eq!(feasible(&summary, &Requirements::new(&input)), expected);
        }
    }
}

#[test]
fn individual_hp_bound_respects_real_two_slot_packages() {
    let mut problem = small_problem();
    problem.base_context = PreparedContext::from(
        json!({"level":100,"vitBase":1,"mainType":"한손검","wpnAtk":100,"strBase":100,"critF":100}),
    );
    problem.scenario_snapshot = json!({"requirements":{"maxHp":5000}});
    problem.metadata.modeled_keys = vec!["MAXHP".into(), "MAXHPP".into()];
    for group in &mut problem.groups {
        group.packages = vec![
            NativePackage {
                evaluation_delta: None,
                search_values: Vec::new(),
                id: format!("{}:flat", group._id),
                stat_delta: serde_json::from_value(json!({"MAXHP":1000})).unwrap(),
            },
            NativePackage {
                evaluation_delta: None,
                search_values: Vec::new(),
                id: format!("{}:percent", group._id),
                stat_delta: serde_json::from_value(json!({"MAXHPP":100})).unwrap(),
            },
        ];
    }
    // Coordinate envelope: 8365. Actual maximum with VIT=1: 4873.
    let session = NativeSearchSession::new(problem.clone()).unwrap();
    assert!(session.is_complete());
    assert_eq!(session.snapshot().status, "invalid");
    assert_eq!(session.snapshot().visited_nodes, 0);
    problem.scenario_snapshot["requirements"]["maxHp"] = json!(4873);
    let result = solve_exact(&problem).unwrap();
    assert!(result.exact);
}

#[test]
fn utility_caps_reject_impossible_targets_and_allow_motion_equivalence() {
    for (key, value) in [
        ("maxMp", 2001.),
        ("normalAttackCrit", 101.),
        ("aspd", 10001.),
    ] {
        let mut problem = small_problem();
        problem.scenario_snapshot = json!({"requirements":{key:value}});
        let session = NativeSearchSession::new(problem).unwrap();
        assert!(session.is_complete(), "{key}");
        assert_eq!(session.snapshot().status, "invalid");
    }
    let mut problem = small_problem();
    let mut base = serde_json::to_value(&problem.base_context).unwrap();
    base["motionSpeed"] = json!(50);
    base["godspeedWieldLevel"] = json!(10);
    base["maxMpF"] = json!(3000);
    problem.base_context = PreparedContext::from(base);
    problem.scenario_snapshot = json!({"requirements":{"maxMp":2300,"aspd":10000}});
    assert!(solve_exact(&problem).unwrap().exact);
    problem.scenario_snapshot["requirements"]["maxMp"] = json!(2301);
    assert_eq!(
        NativeSearchSession::new(problem).unwrap().snapshot().status,
        "invalid"
    );
}

#[test]
fn linear_crit_support_cuts_incompatible_flat_and_percent_suppliers() {
    let mut problem = small_problem();
    let mut base = serde_json::to_value(&problem.base_context).unwrap();
    base["critF"] = json!(0);
    base["skillMult"] = json!(1);
    problem.base_context = PreparedContext::from(base);
    for group in &mut problem.groups[..2] {
        group.packages = serde_json::from_value(json!([
            {"id":format!("{}-flat",group._id),"statDelta":{"CRIT":35}},
            {"id":format!("{}-percent",group._id),"statDelta":{"CRITP":100,"ATKP":40}}
        ]))
        .unwrap();
    }
    problem.prepare_trees().unwrap();
    let roots = problem.trees.roots;
    let independent = roots.iter().fold(Stats::new(), |stats, node| {
        add_stats(stats, &problem.trees[*node].envelope)
    });
    assert!(utility_values(&problem.base_context, &independent).unwrap()[3] >= 100.0);
    let joint = problem.trees.joint.as_ref().unwrap();
    assert!(joint.linear_crit.is_some());
    assert!(!joint.possible(&roots));
    assert_eq!(solve_exact(&problem).unwrap().status, "invalid");
    for group in &mut problem.groups[..2] {
        group.packages.push(NativePackage {
            id: format!("{}-both", group._id),
            stat_delta: Stats::from([
                ("CRIT".into(), 20.0),
                ("CRITP".into(), 80.0),
                ("ATKP".into(), 10.0),
            ]),
            evaluation_delta: None,
            search_values: Vec::new(),
        });
    }
    problem.prepare_trees().unwrap();
    let roots = problem.trees.roots;
    assert!(problem.trees.joint_utilities_possible(&roots));
    assert!(
        box_stats(&problem.trees, &roots)
            .get("ATKP")
            .copied()
            .unwrap()
            < 82.0
    );
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut oracle = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    enumerate_box_reference(
        0,
        &roots,
        &problem,
        &requirements,
        &mut [0; GROUP_COUNT],
        &Stats::new(),
        &mut oracle,
        &mut 0,
    )
    .unwrap();
    for threads in [1, 2, 8, 64] {
        let result = solve_exact_parallel(&problem, threads).unwrap().result;
        assert!(result.exact);
        assert_eq!(result.score, Some(oracle.best_score));
        assert_eq!(result.best_build.unwrap().id, oracle.best_id);
    }
}

#[test]
fn linear_crit_inequality_matches_evaluator_and_falls_back_outside_integer_budget() {
    for (crt, percent, flat, resistance, minimum) in [
        (0.0, -50.0, 120.0, 70.0, 100.0),
        (68.0, 0.0, 15.0, 8.0, 50.5),
        (13.0, 5.0, -3.0, 2.0, 12.2),
        (-100.0, 25.0, 80.0, 10.0, 30.1),
        (-85.0, 0.0, 80.0, 5.0, 25.0),
    ] {
        let mut problem = small_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        for (key, value) in [
            ("crtBase", crt),
            ("critP", percent),
            ("critF", flat),
            ("bossCritResist", resistance),
        ] {
            base[key] = json!(value);
        }
        problem.base_context = PreparedContext::from(base);
        let bound = LinearCritBound::prepare(&problem, minimum).unwrap();
        for f in [-100, -1, 0, 1, 37, 100, 1_000_000] {
            for p in [
                -1_000_000, -300, -101, -100, -1, 0, 3, 40, 100, 500, 1_000_000,
            ] {
                let stats = Stats::from([("CRIT".into(), f as f64), ("CRITP".into(), p as f64)]);
                let accepts = utility_values(&problem.base_context, &stats).unwrap()[3] >= minimum;
                assert_eq!(
                    accepts,
                    bound.scale * f as f64 + bound.percent_weight * p as f64 >= bound.minimum
                );
            }
        }
        for key in ["critP", "critF", "bossCritResist"] {
            let mut copy = problem.clone();
            let mut base = serde_json::to_value(&copy.base_context).unwrap();
            base[key] = json!(0.25);
            copy.base_context = PreparedContext::from(base);
            assert!(LinearCritBound::prepare(&copy, minimum).is_none());
        }
        for (key, value) in [
            ("CRIT", 0.25),
            ("CRITP", 0.25),
            ("CRIT", 1_000_001.0),
            ("CRITP", 1_000_001.0),
        ] {
            let mut copy = problem.clone();
            copy.groups[0].packages[0]
                .stat_delta
                .insert(key.into(), value);
            assert!(LinearCritBound::prepare(&copy, minimum).is_none());
        }
        for minimum in [0.0, -1.0, 100.1, f64::INFINITY, f64::NAN] {
            assert!(LinearCritBound::prepare(&problem, minimum).is_none());
        }
    }
    // Exact integer oracle at both sides of divisibility boundaries.
    for numerator in [
        -20_000_000_000_000_i64,
        -1_000_000,
        0,
        1_000_000,
        20_000_000_000_000,
    ] {
        for divisor in 1..=400 {
            let multiple = numerator / divisor * divisor;
            for offset in [-1, 0, 1] {
                let n = multiple + offset;
                assert_eq!(
                    (n as f64 / divisor as f64).floor(),
                    n.div_euclid(divisor) as f64
                );
            }
        }
    }
}

fn small_problem() -> NativeProblem {
    serde_json::from_value(json!({
        "baseContext":{"level":100,"mainType":"한손검","subType":"없음","armorType":"일반옷","wpnAtk":100,"wpnRefine":0,"wpnStab":100,"strBase":0,"dexBase":0,"intBase":0,"agiBase":0,"vitBase":100,"critF":100,"atkType":"PHYS","rangeType":"SHORT","bossLevel":100,"bossDef":0,"bossMdef":0,"aspdF":1000,"maxHpF":10000,"maxMpF":2000,"amprF":100},
        "scenarioSnapshot":{"requirements":{"maxHp":10000,"maxMp":2000,"amprBeforeDual":100,"normalAttackCrit":100,"aspd":1000}},
        "groups":[
          {"id":"a","packages":[{"id":"a","statDelta":{"ATKP":1}},{"id":"z","statDelta":{"ATKP":1}}]},
          {"id":"b","packages":[{"id":"b","statDelta":{"ATKP":1}}]},
          {"id":"c","packages":[{"id":"c","statDelta":{"ATKP":1}}]},
          {"id":"d","packages":[{"id":"d","statDelta":{"ATKP":1}}]}
        ]
    }))
    .unwrap()
}

#[test]
fn pair_seed_escapes_feasible_single_swap_local_optimum_and_preserves_oracle() {
    let mut problem = small_problem();
    let mut base = serde_json::to_value(&problem.base_context).unwrap();
    base["skillMult"] = json!(1);
    problem.base_context = PreparedContext::from(base);
    problem.groups[0].packages = serde_json::from_value(json!([
        {"id":"a0", "statDelta":{"ATKP":20}},
        {"id":"a1", "statDelta":{"AMPR":20}}
    ]))
    .unwrap();
    problem.groups[1].packages = serde_json::from_value(json!([
        {"id":"b0", "statDelta":{"AMPR":20}},
        {"id":"b1", "statDelta":{"ATKP":30}}
    ]))
    .unwrap();
    for group in &mut problem.groups[2..] {
        group.packages = (0..8)
            .map(|index| NativePackage {
                id: format!("{}-{index}", group._id),
                stat_delta: Stats::new(),
                evaluation_delta: None,
                search_values: Vec::new(),
            })
            .collect();
    }
    problem.scenario_snapshot["requirements"]["amprBeforeDual"] =
        json!(utility_values(&problem.base_context, &Stats::new()).unwrap()[2] + 20.0);
    problem.prepare_evaluation_stats();
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut state = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    let baseline = [0; GROUP_COUNT];
    consider(
        &problem,
        &requirements,
        &mut state,
        &baseline,
        &selection_evaluation_stats(&problem, &baseline),
    )
    .unwrap();
    assert!(state.best_selected.is_some());
    let original_score = state.best_score;
    let mut single = state.clone();
    for group in 0..2 {
        let mut selected = baseline;
        selected[group] = 1;
        consider(
            &problem,
            &requirements,
            &mut single,
            &selected,
            &selection_evaluation_stats(&problem, &selected),
        )
        .unwrap();
    }
    assert_eq!(single.best_score, original_score);
    let original_packages = serde_json::to_value(&problem.groups).unwrap();
    improve_pair_seed(&problem, &requirements, &mut state).unwrap();
    assert!(state.best_score > original_score);
    assert_eq!(&state.best_selected.unwrap()[..2], &[1, 1]);
    assert_eq!(
        serde_json::to_value(&problem.groups).unwrap(),
        original_packages
    );
    assert!(state.evaluations <= 1 + 2 * (20 + 6 * 33 * 33));
    let mut oracle = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    let mut count = 0;
    enumerate_box_reference(
        0,
        &roots,
        &problem,
        &requirements,
        &mut [0; GROUP_COUNT],
        &Stats::new(),
        &mut oracle,
        &mut count,
    )
    .unwrap();
    assert_eq!(count, 256);
    assert_eq!(state.best_score, oracle.best_score);
    assert_eq!(state.best_id, oracle.best_id);
    for reverse in [false, true] {
        if reverse {
            for group in &mut problem.groups {
                group.packages.reverse();
            }
        }
        let result = solve_exact(&problem).unwrap();
        assert!(result.exact);
        assert_eq!(result.score, Some(oracle.best_score));
        assert_eq!(result.best_build.unwrap().id, oracle.best_id);
        let result = solve_exact_parallel(&problem, 8).unwrap().result;
        assert!(result.exact);
        assert_eq!(result.score, Some(oracle.best_score));
        assert_eq!(result.best_build.unwrap().id, oracle.best_id);
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        while !session.snapshot().exact {
            session
                .run_parallel_slice_with_control(8, 32, None, None)
                .unwrap();
        }
        assert_eq!(session.snapshot().best_build.unwrap().id, oracle.best_id);
    }
}

#[test]
fn infeasible_seed_repair_handles_complementary_swaps_and_preserves_exact_search() {
    let mut problem = small_problem();
    let values = utility_values(&problem.base_context, &Stats::new()).unwrap();
    problem.scenario_snapshot =
        json!({"requirements":{"maxHp":values[0]*2.0,"amprBeforeDual":values[2]*2.0}});
    problem.groups[0].packages = serde_json::from_value(json!([
        {"id":"a0","statDelta":{}},
        {"id":"a1","statDelta":{"MAXHP":values[0]*2.0,"AMPR":-values[2],"ASPD":-100000}}
    ]))
    .unwrap();
    problem.groups[1].packages = serde_json::from_value(json!([
        {"id":"b0","statDelta":{}},
        {"id":"b1","statDelta":{"MAXHP":-values[0],"AMPR":values[2]*2.0,"ASPD":-100000}}
    ]))
    .unwrap();
    for group in &mut problem.groups[2..] {
        group.packages = (0..8)
            .map(|i| NativePackage {
                id: format!("{}-{i}", group._id),
                stat_delta: Stats::new(),
                evaluation_delta: None,
                search_values: Vec::new(),
            })
            .collect();
    }
    problem.prepare_evaluation_stats();
    let roots = problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut state = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    for selected in initial_selections(&problem) {
        consider(
            &problem,
            &requirements,
            &mut state,
            &selected,
            &selection_evaluation_stats(&problem, &selected),
        )
        .unwrap();
    }
    assert!(state.best_selected.is_none());
    let packages = serde_json::to_value(&problem.groups).unwrap();
    repair_infeasible_seed(&problem, &requirements, &mut state).unwrap();
    assert!(state.best_selected.is_some());
    assert_eq!(&state.best_selected.unwrap()[..2], &[1, 1]);
    assert_eq!(serde_json::to_value(&problem.groups).unwrap(), packages);
    let mut oracle = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    let mut count = 0;
    enumerate_box_reference(
        0,
        &roots,
        &problem,
        &requirements,
        &mut [0; GROUP_COUNT],
        &Stats::new(),
        &mut oracle,
        &mut count,
    )
    .unwrap();
    assert_eq!(count, 256);
    for reverse in [false, true] {
        if reverse {
            for group in &mut problem.groups {
                group.packages.reverse();
            }
        }
        let session = NativeSearchSession::new(problem.clone()).unwrap();
        assert!(
            session.snapshot().best_build.is_some(),
            "seed must exist before any node visit"
        );
        assert_eq!(session.snapshot().visited_nodes, 0);
        let result = solve_exact(&problem).unwrap();
        assert_eq!(result.score, Some(oracle.best_score));
        assert_eq!(result.best_build.unwrap().id, oracle.best_id);
        for threads in [1, 2, 4, 8, 16, 64] {
            let result = solve_exact_parallel(&problem, threads).unwrap().result;
            assert!(result.exact);
            assert_eq!(result.score, Some(oracle.best_score));
            assert_eq!(result.best_build.unwrap().id, oracle.best_id);
        }
        let restored: NativeSearchCheckpoint =
            serde_json::from_str(&serde_json::to_string(&session.checkpoint().unwrap()).unwrap())
                .unwrap();
        let mut session = NativeSearchSession::from_checkpoint(restored).unwrap();
        while !session.is_complete() {
            session.run_parallel_slice(8, 4).unwrap();
        }
        assert_eq!(session.snapshot().best_build.unwrap().id, oracle.best_id);
    }
    problem.scenario_snapshot["requirements"]["maxHp"] = json!(1000000);
    let session = NativeSearchSession::new(problem).unwrap();
    assert!(session.is_complete());
    assert_eq!(session.snapshot().status, "invalid");
    assert!(session.snapshot().best_build.is_none());
}

#[test]
fn pair_seed_skips_tiny_or_infeasible_inputs() {
    let mut problem = small_problem();
    problem.prepare_evaluation_stats();
    problem.prepare_trees().unwrap();
    let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
    let mut state = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    improve_pair_seed(&problem, &requirements, &mut state).unwrap();
    assert_eq!(state.evaluations, 0);
    consider(
        &problem,
        &requirements,
        &mut state,
        &[0; GROUP_COUNT],
        &selection_evaluation_stats(&problem, &[0; GROUP_COUNT]),
    )
    .unwrap();
    let before = serde_json::to_value(&state).unwrap();
    improve_pair_seed(&problem, &requirements, &mut state).unwrap();
    assert_eq!(serde_json::to_value(&state).unwrap(), before);
}

#[allow(clippy::too_many_arguments)] // Recursive complete enumeration shares its immutable search inputs.
fn enumerate_box_reference(
    index: usize,
    clusters: &[NodeId; GROUP_COUNT],
    problem: &NativeProblem,
    requirements: &Requirements,
    selected: &mut [usize; GROUP_COUNT],
    stats: &Stats,
    state: &mut SearchState,
    enumerated: &mut u64,
) -> Result<(), String> {
    if index == GROUP_COUNT {
        *enumerated += 1;
        return consider(problem, requirements, state, selected, stats);
    }
    let mut indices = Vec::with_capacity(problem.trees[clusters[index]].size);
    cluster_indices(&problem.trees, clusters[index], &mut indices);
    for package_index in indices {
        selected[index] = package_index;
        let next = add_stats(
            stats.clone(),
            &problem.groups[index].packages[package_index].stat_delta,
        );
        enumerate_box_reference(
            index + 1,
            clusters,
            problem,
            requirements,
            selected,
            &next,
            state,
            enumerated,
        )?;
    }
    Ok(())
}

#[test]
fn prepared_small_box_lists_match_tree_walking_enumeration() {
    for sizes in [
        [1, 1, 1, 1],
        [1, 1, 1, 64],
        [1, 1, 64, 1],
        [1, 64, 1, 1],
        [64, 1, 1, 1],
        [2, 2, 2, 8],
        [4, 4, 2, 2],
        [3, 1, 7, 3],
    ] {
        let mut problem = small_problem();
        for (group_index, group) in problem.groups.iter_mut().enumerate() {
            group.packages = (0..sizes[group_index])
                .rev()
                .map(|index| NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: format!("{group_index}-{index}"),
                    stat_delta: Stats::from([
                        ("ATKP".into(), (index % 3) as f64 * 0.25),
                        ("MAXHP".into(), -(index as f64) * 200.0),
                    ]),
                })
                .collect();
        }
        let session = NativeSearchSession::new(problem.clone()).unwrap();
        let problem = session.problem.clone();
        let clusters = &session.heap.peek().unwrap().clusters;
        let candidates = SmallBoxCandidates::new(&problem.trees, clusters);
        assert_eq!(
            candidates.as_slices(),
            box_candidate_indices(&problem.trees, clusters)
                .each_ref()
                .map(|items| items.as_slice())
        );
        let mut actual = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        let mut expected = actual.clone();
        let (mut count, mut reference_count) = (0, 0);
        enumerate_box(
            0,
            &candidates.as_slices(),
            &problem,
            &session.requirements,
            &mut [0; GROUP_COUNT],
            &Stats::new(),
            &mut actual,
            &mut count,
        )
        .unwrap();
        enumerate_box_reference(
            0,
            clusters,
            &problem,
            &session.requirements,
            &mut [0; GROUP_COUNT],
            &Stats::new(),
            &mut expected,
            &mut reference_count,
        )
        .unwrap();
        assert_eq!(count, sizes.iter().product::<usize>() as u64);
        assert_eq!(count, reference_count);
        assert_eq!(
            serde_json::to_value(actual).unwrap(),
            serde_json::to_value(expected).unwrap()
        );
    }
}

fn wide_problem() -> NativeProblem {
    let mut problem = small_problem();
    for (group_index, group) in problem.groups.iter_mut().enumerate() {
        group.packages = (0..8)
            .map(|package_index| NativePackage {
                evaluation_delta: None,
                search_values: Vec::new(),
                id: format!("{group_index}-{package_index}"),
                stat_delta: Stats::new(),
            })
            .collect();
    }
    problem
}

#[test]
fn deferred_snapshots_preserve_frontier_counters_and_control() {
    let mut eager = NativeSearchSession::new(wide_problem()).unwrap();
    let mut deferred = NativeSearchSession::new(wide_problem()).unwrap();
    let cancel = Arc::new(AtomicBool::new(true));
    for mode in 0..3 {
        let signal = (mode == 0).then_some(&cancel);
        let deadline = (mode == 1).then(Instant::now);
        let result = eager
            .run_parallel_slice_with_control(8, 1, signal, deadline)
            .unwrap();
        deferred
            .advance_parallel_slice_with_control(8, 1, signal, deadline)
            .unwrap();
        let mut expected = serde_json::to_value(result).unwrap();
        let mut actual = serde_json::to_value(deferred.snapshot()).unwrap();
        expected["elapsedMs"] = 0.into();
        actual["elapsedMs"] = 0.into();
        assert_eq!(actual, expected);
        let mut expected = serde_json::to_value(eager.checkpoint().unwrap()).unwrap();
        let mut actual = serde_json::to_value(deferred.checkpoint().unwrap()).unwrap();
        expected["elapsed_ms"] = 0.into();
        actual["elapsed_ms"] = 0.into();
        assert_eq!(actual, expected);
    }
    while !deferred.is_complete() {
        deferred
            .advance_parallel_slice_with_control(64, 1, None, None)
            .unwrap();
    }
    while !eager.is_complete() {
        eager.run_parallel_slice(64, 1).unwrap();
    }
    let mut expected = serde_json::to_value(eager.snapshot()).unwrap();
    let mut actual = serde_json::to_value(deferred.snapshot()).unwrap();
    expected["elapsedMs"] = 0.into();
    actual["elapsedMs"] = 0.into();
    assert_eq!(actual, expected);
    deferred
        .advance_parallel_slice_with_control(64, 1, None, None)
        .unwrap();
    assert!(deferred.snapshot().exact);
}

#[test]
fn persistent_pool_reuses_workers_and_rebuilds_after_checkpoint() {
    let mut session = NativeSearchSession::new(wide_problem()).unwrap();
    session.run_parallel_slice(1, 2).unwrap();
    let ids = session
        .pool
        .as_ref()
        .unwrap()
        .workers
        .iter()
        .map(|worker| worker.thread().id())
        .collect::<Vec<_>>();
    session.run_parallel_slice(1, 2).unwrap();
    assert_eq!(
        ids,
        session
            .pool
            .as_ref()
            .unwrap()
            .workers
            .iter()
            .map(|worker| worker.thread().id())
            .collect::<Vec<_>>()
    );
    let checkpoint = session.checkpoint().unwrap();
    let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
    assert!(restored.pool.is_none());
    while !restored.is_complete() {
        restored.run_parallel_slice(128, 4).unwrap();
    }
    let expected = solve_exact(&wide_problem()).unwrap();
    assert_eq!(restored.snapshot().score, expected.score);
    assert_eq!(
        restored.snapshot().best_build.unwrap().id,
        expected.best_build.unwrap().id
    );
}

#[test]
fn shared_messages_cover_ragged_batches_in_input_order() {
    let problem = wide_problem();
    let mut session = NativeSearchSession::new(problem.clone()).unwrap();
    let problem = session.problem.clone();
    let root = session.heap.pop().unwrap();
    let incumbent = Arc::new(SharedIncumbent {
        score_bits: AtomicU64::new(session.state.best_score.to_bits()),
        record: Mutex::new(session.state.clone()),
    });
    for workers in [1, 2, 8, 16, 64] {
        let mut pool = NodePool::new(&problem, session.requirements, workers).unwrap();
        let mut outcomes = Vec::new();
        for count in [0, 1, 7, 31, 33, 65, 257] {
            let nodes = (0..count)
                .map(|index| {
                    let mut node = root;
                    if index % 3 != 0 {
                        node.upper = f64::NEG_INFINITY;
                    }
                    node
                })
                .collect::<Vec<_>>();
            let nodes = Arc::new(nodes);
            let counters = Arc::new(ParallelCounters::default());
            pool.run(&nodes, &mut outcomes, &incumbent, &counters, None, None)
                .unwrap();
            assert_eq!(Arc::strong_count(&nodes), 1);
            let expected = ParallelCounters::default();
            for node in nodes.iter() {
                expand_parallel_node(
                    node,
                    &problem,
                    &session.requirements,
                    &incumbent,
                    &mut &expected,
                    None,
                    None,
                )
                .unwrap();
            }
            for (actual, reference) in [
                (&counters.evaluations, &expected.evaluations),
                (&counters.visited, &expected.visited),
                (&counters.pruned_by_bound, &expected.pruned_by_bound),
                (
                    &counters.pruned_by_constraint,
                    &expected.pruned_by_constraint,
                ),
                (&counters.enumerated, &expected.enumerated),
                (&counters.splits, &expected.splits),
            ] {
                assert_eq!(
                    actual.load(AtomicOrdering::Relaxed),
                    reference.load(AtomicOrdering::Relaxed)
                );
            }
            assert_eq!(outcomes.len(), count);
            for (index, outcome) in outcomes.drain(..).enumerate() {
                assert_eq!(
                    outcome.unwrap().unwrap().unwrap().range.len(),
                    if index % 3 == 0 { 64 } else { 0 }
                );
            }
            // One root visit per input plus 4+16 lookahead visits for each
            // unpruned root: detects duplicated or omitted execution too.
            assert_eq!(
                counters.visited.load(AtomicOrdering::Relaxed),
                (count + count.div_ceil(3) * 20) as u64
            );
            let cancelled = Arc::new(AtomicBool::new(true));
            for (signal, deadline) in [(Some(&cancelled), None), (None, Some(Instant::now()))] {
                pool.run(
                    &nodes,
                    &mut outcomes,
                    &incumbent,
                    &counters,
                    signal,
                    deadline,
                )
                .unwrap();
                assert_eq!(Arc::strong_count(&nodes), 1);
                assert_eq!(outcomes.len(), count);
                assert!(outcomes
                    .drain(..)
                    .all(|result| result.unwrap().unwrap().is_none()));
            }
        }
    }
}

#[test]
fn worker_buffers_reuse_storage_and_preserve_child_order() {
    let session = NativeSearchSession::new(wide_problem()).unwrap();
    let root = *session.heap.peek().unwrap();
    let incumbent = Arc::new(SharedIncumbent {
        score_bits: AtomicU64::new(session.state.best_score.to_bits()),
        record: Mutex::new(session.state.clone()),
    });
    let expected = expand_parallel_node(
        &root,
        &session.problem,
        &session.requirements,
        &incumbent,
        &mut LocalSearchCounters::default(),
        None,
        None,
    )
    .unwrap()
    .unwrap();
    assert_eq!(expected.len(), 64);
    let mut pool = NodePool::new(&session.problem, session.requirements, 1).unwrap();
    let nodes = Arc::new(vec![root; 7]);
    let counters = Arc::new(ParallelCounters::default());
    let mut outcomes = Vec::new();
    let mut storage = None;
    for _ in 0..3 {
        pool.run(&nodes, &mut outcomes, &incumbent, &counters, None, None)
            .unwrap();
        assert_eq!(pool.buffers.len(), 1);
        let buffer = &pool.buffers[0];
        assert!(buffer.outcomes.is_empty());
        let current = (buffer.children.as_ptr(), buffer.outcomes.as_ptr());
        if let Some(previous) = storage {
            assert_eq!(current, previous);
        }
        storage = Some(current);
        for (index, outcome) in outcomes.drain(..).enumerate() {
            let children = outcome.unwrap().unwrap().unwrap();
            assert_eq!(children.buffer, 0);
            assert_eq!(children.range, index * 64..(index + 1) * 64);
            assert!(buffer.children[children.range].iter().eq(expected.iter()));
        }
    }
}

#[test]
fn interrupted_expansion_rolls_back_only_current_buffer_suffix() {
    struct StopAfter<'a> {
        cancel: &'a AtomicBool,
        evaluations: usize,
    }
    impl SearchCounters for StopAfter<'_> {
        fn count_evaluations(&mut self) {
            self.evaluations += 1;
            if self.evaluations == 7 {
                self.cancel.store(true, AtomicOrdering::Release);
            }
        }
        fn count_visited(&mut self) {}
        fn count_pruned_by_bound(&mut self) {}
        fn count_pruned_by_constraint(&mut self) {}
        fn count_enumerated(&mut self) {}
        fn count_splits(&mut self) {}
    }
    let session = NativeSearchSession::new(wide_problem()).unwrap();
    let root = *session.heap.peek().unwrap();
    let incumbent = SharedIncumbent {
        score_bits: AtomicU64::new(session.state.best_score.to_bits()),
        record: Mutex::new(session.state.clone()),
    };
    let cancel = AtomicBool::new(false);
    let mut counters = StopAfter {
        cancel: &cancel,
        evaluations: 0,
    };
    let mut children = vec![root];
    assert!(!expand_parallel_node_into(
        &root,
        &session.problem,
        &session.requirements,
        &incumbent,
        &mut counters,
        Some(&cancel),
        None,
        &mut children
    )
    .unwrap());
    assert_eq!(counters.evaluations, 7);
    assert_eq!(children.len(), 1);
    assert!(children[0] == root);
    // Four descendants were appended before cancellation; the retained
    // capacity proves this exercised rollback after actual output growth.
    assert!(children.capacity() > 1);
}

#[test]
fn cancelled_batches_reuse_buffers_and_preserve_checkpoint() {
    let mut session = NativeSearchSession::new(wide_problem()).unwrap();
    let before = session.checkpoint().unwrap();
    let cancel = Arc::new(AtomicBool::new(true));
    session
        .advance_parallel_slice_with_control(64, 2, Some(&cancel), None)
        .unwrap();
    let nodes_ptr = session.batch_nodes.as_ptr();
    let results_ptr = session.batch_outcomes.as_ptr();
    for workers in [2, 8, 1, 16, 64, 2] {
        session
            .advance_parallel_slice_with_control(64, workers, Some(&cancel), None)
            .unwrap();
        assert!(session.batch_nodes.is_empty());
        assert!(session.batch_outcomes.is_empty());
        assert_eq!(session.batch_nodes.as_ptr(), nodes_ptr);
        assert_eq!(session.batch_outcomes.as_ptr(), results_ptr);
        let after = session.checkpoint().unwrap();
        assert_eq!(
            serde_json::to_value(&after.frontier).unwrap(),
            serde_json::to_value(&before.frontier).unwrap()
        );
        assert_eq!(
            serde_json::to_value(&after.state).unwrap(),
            serde_json::to_value(&before.state).unwrap()
        );
    }
}

#[test]
fn worker_errors_preserve_parent_frontier() {
    let mut session = NativeSearchSession::new(wide_problem()).unwrap();
    let ready = session.ready_work_count();
    session.problem.base_context = PreparedContext::from(Value::Null);
    assert!(session.run_parallel_slice(8, 2).is_err());
    assert_eq!(session.ready_work_count(), ready);
    assert!(!session.snapshot().exact);
}

#[test]
fn selective_lookahead_covers_equal_bound_space_without_duplicates() {
    let problem = wide_problem();
    let mut session = NativeSearchSession::new(problem.clone()).unwrap();
    let problem = session.problem.clone();
    let root = session.heap.pop().unwrap();
    let incumbent = SharedIncumbent {
        score_bits: AtomicU64::new(session.state.best_score.to_bits()),
        record: Mutex::new(session.state.clone()),
    };
    let children = expand_parallel_node(
        &root,
        &problem,
        &session.requirements,
        &incumbent,
        &mut &ParallelCounters::default(),
        None,
        None,
    )
    .unwrap()
    .unwrap();
    assert_eq!(children.len(), 64);
    let mut covered = HashSet::new();
    for child in children {
        assert!(child.upper >= session.state.best_score);
        let indices: [Vec<usize>; 4] = std::array::from_fn(|i| {
            let mut list = Vec::new();
            cluster_indices(&problem.trees, child.clusters[i], &mut list);
            list
        });
        for a in &indices[0] {
            for b in &indices[1] {
                for c in &indices[2] {
                    for d in &indices[3] {
                        assert!(covered.insert([*a, *b, *c, *d]));
                    }
                }
            }
        }
    }
    assert_eq!(covered.len(), 8_usize.pow(4));
}

#[test]
fn lookahead_window_depth_and_small_box_boundaries() {
    let mut session = NativeSearchSession::new(wide_problem()).unwrap();
    let mut root = session.heap.pop().unwrap();
    for best in [-100.0_f64, 0.0, 100.0] {
        root.upper = best + best.abs() * LOOKAHEAD_RELATIVE_GAP;
        assert!(should_look_ahead(&session.problem.trees, &root, best, 0));
        assert!(should_look_ahead(&session.problem.trees, &root, best, 1));
        assert!(!should_look_ahead(&session.problem.trees, &root, best, 2));
        root.upper += 0.0001;
        assert!(!should_look_ahead(&session.problem.trees, &root, best, 0));
    }
    for best in [f64::INFINITY, f64::NEG_INFINITY, f64::NAN] {
        assert!(!should_look_ahead(&session.problem.trees, &root, best, 0));
    }
    let mut small = NativeSearchSession::new(small_problem()).unwrap();
    let node = small.heap.pop().unwrap();
    assert!(!should_look_ahead(
        &small.problem.trees,
        &node,
        node.upper,
        0
    ));
}

#[test]
fn constraint_lookahead_removes_only_infeasible_space_and_keeps_upper() {
    let mut problem = wide_problem();
    for group in &mut problem.groups {
        for (i, package) in group.packages.iter_mut().enumerate() {
            package
                .stat_delta
                .insert("MAXHP".into(), -(i as f64) * 1200.0);
        }
    }
    let mut session = NativeSearchSession::new(problem.clone()).unwrap();
    let problem = session.problem.clone();
    let root = session.heap.pop().unwrap();
    let incumbent = SharedIncumbent {
        score_bits: AtomicU64::new(f64::NEG_INFINITY.to_bits()),
        record: Mutex::new(SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        }),
    };
    let mut coverage = Vec::new();
    for pressure in [false, true] {
        let mut counters = LocalSearchCounters {
            pruned_by_constraint: if pressure { 10000 } else { 0 },
            evaluations: 1000,
            ..LocalSearchCounters::default()
        };
        let children = expand_parallel_node(
            &root,
            &problem,
            &session.requirements,
            &incumbent,
            &mut counters,
            None,
            None,
        )
        .unwrap()
        .unwrap();
        let mut covered = HashSet::new();
        for child in children {
            let indices = box_candidate_indices(&problem.trees, &child.clusters);
            for &a in &indices[0] {
                for &b in &indices[1] {
                    for &c in &indices[2] {
                        for &d in &indices[3] {
                            let selected = [a, b, c, d];
                            assert!(covered.insert(selected));
                            let stats = selection_stats(&problem, &selected);
                            if let Some(score) =
                                evaluate_feasible_summary(&problem.base_context, &stats, |i, v| {
                                    session.requirements.accepts_value(i, v)
                                })
                                .unwrap()
                            {
                                assert!(child.upper >= score.optimization_damage_factor);
                            }
                        }
                    }
                }
            }
        }
        coverage.push(covered);
    }
    assert!(coverage[1].len() < coverage[0].len());
    for selected in coverage[0].difference(&coverage[1]) {
        let stats = selection_stats(&problem, selected);
        assert!(
            evaluate_feasible_summary(&problem.base_context, &stats, |i, v| session
                .requirements
                .accepts_value(i, v))
            .unwrap()
            .is_none()
        );
    }
    let cancelled = AtomicBool::new(true);
    assert!(expand_parallel_node(
        &root,
        &problem,
        &session.requirements,
        &incumbent,
        &mut LocalSearchCounters::default(),
        Some(&cancelled),
        None
    )
    .unwrap()
    .is_none());
}

#[test]
fn solves_small_problem_exactly_with_lexical_tie() {
    let problem = small_problem();
    let result = solve_exact(&problem).unwrap();
    assert!(result.exact);
    assert_eq!(result.best_build.unwrap().id, "a||b||c||d");
}

#[test]
fn small_stat_bonuses_do_not_receive_main_stat_split_priority() {
    let context = json!({"strBase":327,"dexBase":510,"agiBase":1,"intBase":1,"vitBase":1});
    assert!(split_importance("@AGI:0", &context) < split_importance("@STR:0", &context) / 100.0);
    assert_eq!(
        split_importance("@INT:0", &context),
        split_importance("INTP", &context)
    );
    let switched = json!({"strBase":1,"dexBase":1,"agiBase":510,"intBase":327,"vitBase":1});
    assert!(split_importance("AGI", &switched) > split_importance("STR", &switched) * 100.0);
    assert_eq!(split_importance("STR", &json!({})), 3.0);
    let stats = [
        ("STR", "strBase"),
        ("DEX", "dexBase"),
        ("AGI", "agiBase"),
        ("INT", "intBase"),
        ("VIT", "vitBase"),
    ];
    for (main, main_base) in stats {
        for (secondary, secondary_base) in stats {
            if main == secondary {
                continue;
            }
            let mut context = json!({"strBase":1,"dexBase":1,"agiBase":1,"intBase":1,"vitBase":1});
            context[main_base] = json!(510);
            context[secondary_base] = json!(327);
            for (minor, _) in stats {
                if minor != main && minor != secondary {
                    assert!(
                        split_importance(main, &context)
                            > split_importance(minor, &context) * 100.0
                    );
                }
            }
        }
    }
}

#[test]
fn candidate_coordinates_only_order_trees_and_preserve_oracle_resume() {
    let mut problem = joint_problem();
    let oracle = solve_exact(&problem).unwrap();
    problem.metadata.search_keys = vec!["@CRIT:0".into(), "@ASPD:1".into()];
    // Deliberately unrelated to damage: these values can only order splits.
    for group in &mut problem.groups {
        for (index, package) in group.packages.iter_mut().enumerate() {
            package.search_values = vec![(index % 3) as f64, -(index as f64)];
        }
    }
    let raw = serde_json::to_value(&problem.groups).unwrap();
    for reverse in [false, true] {
        if reverse {
            for group in &mut problem.groups {
                group.packages.reverse();
            }
        }
        for threads in [1, 2, 8, 64] {
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            assert_eq!(
                session.problem.trees.ordering_keys,
                problem.metadata.search_keys
            );
            session.run_parallel_slice(1, threads).unwrap();
            let wire = serde_json::to_string(&session.checkpoint().unwrap()).unwrap();
            let mut restored =
                NativeSearchSession::from_checkpoint(serde_json::from_str(&wire).unwrap()).unwrap();
            assert_eq!(
                restored.problem.trees.ordering_keys,
                problem.metadata.search_keys
            );
            while !restored.is_complete() {
                let result = restored.run_parallel_slice(8, threads).unwrap();
                assert!(result.upper_bound.unwrap() >= oracle.score.unwrap());
            }
            let result = restored.snapshot();
            assert_eq!(result.score, oracle.score);
            assert_eq!(
                serde_json::to_value(result.best_build).unwrap(),
                serde_json::to_value(&oracle.best_build).unwrap()
            );
        }
    }
    for group in &mut problem.groups {
        group.packages.reverse();
    }
    assert_eq!(serde_json::to_value(&problem.groups).unwrap(), raw);
    for invalid in [Vec::new(), vec![f64::NAN, 0.0]] {
        problem.groups[0].packages[0].search_values = invalid;
        let session = NativeSearchSession::new(problem.clone()).unwrap();
        assert!(session.problem.trees.ordering_keys.is_empty());
        let result = solve_exact(&problem).unwrap();
        assert_eq!(result.score, oracle.score);
        assert_eq!(
            result.best_build.unwrap().id,
            oracle.best_build.as_ref().unwrap().id
        );
    }
}

#[test]
fn envelope_preserves_forced_penalties_and_missing_coordinate_zero() {
    let packages: Vec<NativePackage> = serde_json::from_value(json!([
        {"id":"a","statDelta":{"ATKP":-10,"MAXMP":-200}},
        {"id":"b","statDelta":{"ATKP":-5}},
        {"id":"c","statDelta":{"ATKP":-5,"MAXMP":-100}}
    ]))
    .unwrap();
    let keys = vec!["ATKP".into(), "MAXMP".into()];
    let envelope = group_envelope(&packages, &[0, 1, 2], &keys);
    assert_eq!(envelope.get("ATKP"), Some(&-5.0));
    assert_eq!(envelope.get("MAXMP").copied().unwrap_or(0.0), 0.0);
    assert_eq!(
        group_envelope(&packages, &[0], &keys),
        packages[0].stat_delta
    );
    assert!(group_envelope(&packages, &[], &keys).is_empty());
}

#[test]
fn bound_merge_preserves_group_order_and_sparse_penalties() {
    let mut problem = small_problem();
    for (group, atk) in problem.groups.iter_mut().zip([1e16, -1e16, 1.0, 0.0]) {
        group.packages = vec![NativePackage {
            evaluation_delta: None,
            search_values: Vec::new(),
            id: group._id.clone(),
            stat_delta: Stats::from([("ATK".into(), atk)]),
        }];
    }
    problem.groups[2].packages[0]
        .stat_delta
        .insert("MAXMP".into(), -100.0);
    let keys = vec!["ATK".into(), "MAXMP".into()];
    let mut arena = TreeArena::default();
    let trees = std::array::from_fn(|index| {
        build_tree(
            &mut arena,
            &problem.groups[index].packages,
            vec![0],
            &keys,
            &BTreeMap::new(),
            &problem.base_context,
            "r".into(),
        )
    });
    // ATK order matters: (1e16 + -1e16) + 1 is 1, not 0.
    let stats = box_stats(&arena, &trees);
    assert_eq!(stats["ATK"], 1.0);
    assert_eq!(stats["MAXMP"], -100.0);
    assert_eq!(
        add_stats(Stats::new(), &Stats::from([("ATK".into(), -0.0)]))["ATK"].to_bits(),
        0.0_f64.to_bits()
    );
}

#[test]
fn numeric_path_order_matches_lexical_heap_order() {
    fn old_cmp(trees: &TreeArena, left: &WorkItem, right: &WorkItem) -> Ordering {
        left.upper.total_cmp(&right.upper).then_with(|| {
            for (a, b) in left.clusters.iter().zip(&right.clusters) {
                let order = trees[*b].path.cmp(&trees[*a].path);
                if order != Ordering::Equal {
                    return order;
                }
            }
            Ordering::Equal
        })
    }
    // Include uneven trees, prefix/descendant pairs and empty/single roots.
    for count in 0..=65 {
        let packages = (0..count)
            .map(|index| NativePackage {
                evaluation_delta: None,
                search_values: Vec::new(),
                id: index.to_string(),
                stat_delta: Stats::new(),
            })
            .collect::<Vec<_>>();
        let mut arena = TreeArena::default();
        let root = build_tree(
            &mut arena,
            &packages,
            (0..count).collect(),
            &[],
            &BTreeMap::new(),
            &serde_json::json!({}),
            "r".into(),
        );
        let nodes = (0..arena.nodes.len())
            .map(|id| NodeId(id as u32))
            .collect::<Vec<_>>();
        assert_eq!(root, NodeId(0));
        for (rank, node) in nodes.iter().enumerate() {
            assert_eq!(node.0 as usize, rank);
            for other in &nodes {
                assert_eq!(node.cmp(other), arena[*node].path.cmp(&arena[*other].path));
            }
        }
        let old_cmp = |a: &WorkItem, b: &WorkItem| old_cmp(&arena, a, b);
        let uppers = [
            0.0,
            -0.0,
            1.0,
            1.0,
            f64::INFINITY,
            f64::NEG_INFINITY,
            f64::NAN,
        ];
        let boxes = (0..128)
            .map(|index| WorkItem {
                upper: uppers[index % uppers.len()],
                clusters: std::array::from_fn(|group| {
                    nodes[(index * (group * 2 + 1) + group) % nodes.len()]
                }),
            })
            .collect::<Vec<_>>();
        for a in &boxes {
            for b in &boxes {
                assert_eq!(a.cmp(b), old_cmp(a, b));
                assert_eq!(a == b, old_cmp(a, b) == Ordering::Equal);
            }
        }
        let mut expected = boxes.clone();
        expected.sort_by(old_cmp);
        let mut frontier = WorkHeap::new();
        let mut reference = BinaryHeap::new();
        // Mixed insertion/removal covers partial child groups, duplicates,
        // equal upper bounds, signed zero and the existing total NaN order.
        for (index, item) in boxes.iter().enumerate() {
            frontier.push(*item);
            reference.push(*item);
            if index % 3 == 0 {
                assert_eq!(
                    old_cmp(&frontier.pop().unwrap(), &reference.pop().unwrap()),
                    Ordering::Equal
                );
            }
            assert_eq!(frontier.len(), reference.len());
        }
        frontier.extend(boxes.iter().cloned());
        reference.extend(boxes.iter().cloned());
        while let Some(item) = reference.pop() {
            assert_eq!(old_cmp(frontier.peek().unwrap(), &item), Ordering::Equal);
            assert_eq!(old_cmp(&frontier.pop().unwrap(), &item), Ordering::Equal);
        }
        assert!(frontier.is_empty());
        assert!(frontier.pop().is_none());
        assert!(frontier.peek().is_none());
        frontier.push(boxes[0]);
        assert_eq!(
            old_cmp(&frontier.pop().unwrap(), &boxes[0]),
            Ordering::Equal
        );
        let mut heap = BinaryHeap::from(boxes);
        while let Some(actual) = heap.pop() {
            assert_eq!(old_cmp(&actual, &expected.pop().unwrap()), Ordering::Equal);
        }
    }
}

#[test]
fn lazy_children_preserve_order_and_cover_each_binary_split_once() {
    // All 16 leaf/branch patterns across the four equipment groups.
    for mask in 0_u32..16 {
        let mut problem = small_problem();
        for (index, group) in problem.groups.iter_mut().enumerate() {
            group.packages = (0..if mask & (1 << index) != 0 { 2 } else { 1 })
                .map(|value| NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: value.to_string(),
                    stat_delta: Stats::new(),
                })
                .collect();
        }
        let mut arena = TreeArena::default();
        let roots = std::array::from_fn(|index| {
            build_tree(
                &mut arena,
                &problem.groups[index].packages,
                (0..problem.groups[index].packages.len()).collect(),
                &[],
                &BTreeMap::new(),
                &problem.base_context,
                "r".into(),
            )
        });
        let selected: Vec<_> = (0..GROUP_COUNT)
            .filter(|index| mask & (1 << index) != 0)
            .take(2)
            .collect();
        let count = if selected.is_empty() {
            0
        } else {
            1 << selected.len()
        };
        let mut children = ChildBoxes::new(&arena, &roots);
        assert_eq!(children.len(), count);
        let mut covered = 0;
        for ordinal in 0..count {
            let child = children.next().unwrap();
            assert_eq!(children.len(), count - ordinal - 1);
            covered += child
                .iter()
                .map(|node| arena[*node].size)
                .product::<usize>();
            for index in 0..GROUP_COUNT {
                let expected = match selected.iter().position(|split| *split == index) {
                    None => &roots[index],
                    Some(position) => {
                        let right = (ordinal >> (selected.len() - position - 1)) & 1 != 0;
                        if right {
                            arena[roots[index]].right.as_ref().unwrap()
                        } else {
                            arena[roots[index]].left.as_ref().unwrap()
                        }
                    }
                };
                assert_eq!(&child[index], expected);
            }
        }
        assert!(children.next().is_none());
        assert!(children.next().is_none());
        if count > 0 {
            assert_eq!(
                covered,
                roots
                    .iter()
                    .map(|node| arena[*node].size)
                    .product::<usize>()
            );
        }
    }
}

#[test]
fn old_bound_policy_checkpoint_is_rejected() {
    let session = NativeSearchSession::new(small_problem()).unwrap();
    for version in 4..=22 {
        let mut checkpoint = session.checkpoint().unwrap();
        checkpoint.schema = format!("toram.crysta-native-search-checkpoint.v{version}");
        assert!(NativeSearchSession::from_checkpoint(checkpoint.clone()).is_err());
        checkpoint.schema = format!("toram.d4-native-search-checkpoint.v{version}");
        assert!(NativeSearchSession::from_checkpoint(checkpoint).is_err());
    }
}

#[test]
fn correlated_product_covers_clipped_rectangles_and_numeric_fallbacks() {
    for x in [0.0, 0.25, 1.0, 19.0, 1e6] {
        for y in [0.0, 0.125, 2.0, 27.0] {
            for weight in [0.25, 1.0, 4.0, 1e6] {
                for fraction in [0.0, 0.1, 0.5, 0.9, 1.0, 1.5] {
                    let support = (x + weight * y) * fraction;
                    let upper = correlated_product_upper(x, y, support, weight);
                    for i in 0..=20 {
                        for j in 0..=20 {
                            let a = x * i as f64 / 20.0;
                            let b = y * j as f64 / 20.0;
                            if a + weight * b <= support {
                                assert!(upper >= a * b);
                            }
                        }
                    }
                }
            }
        }
    }
    assert_eq!(correlated_product_upper(-1.0, 1.0, 1.0, 1.0), f64::INFINITY);
    assert_eq!(
        correlated_product_upper(1.0, 1.0, f64::NAN, 1.0),
        f64::INFINITY
    );
}

fn range_product_problem(case: usize) -> NativeProblem {
    let mut problem = small_problem();
    let mut base = serde_json::to_value(&problem.base_context).unwrap();
    base["strBase"] = json!(400);
    base["intBase"] = json!(350);
    base["dexBase"] = json!(200);
    base["skillMult"] = json!(2.1);
    base["skillConst"] = json!(200);
    base["critF"] = json!(1000);
    base["spellBurstLevel"] = json!(10);
    base["targetWeakened"] = json!(true);
    base["srw"] = json!(5);
    base["lrw"] = json!(15);
    base["damageMultiplierLayers"] = json!({"skill":2.1,"passive":1.1,"active":1.2,"combo":1.5});
    if case == 1 || case == 2 {
        base["atkType"] = json!("MAG");
        base["ignoreMdef"] = json!(true);
        base["mainType"] = json!(if case == 1 { "지팡이" } else { "마도구" });
    }
    if case == 3 {
        base["useHigherRangeDamage"] = json!(true);
    }
    if case == 5 {
        base["damageMultiplierLayers"]["active"] = json!(-1);
    }
    if case == 6 {
        base["srw"] = json!(-140);
    }
    if case == 7 {
        base["bossPhysResist"] = json!(150);
    }
    if case == 8 {
        base["dualBringerActive"] = json!(true);
        base["dualBringerLevel"] = json!(10);
    }
    if case == 9 {
        base["skillStats"] = json!([{"stat":"totalDEX","target":"mult","ratio":0.01}]);
    }
    if case == 10 {
        base["noCritical"] = json!(true);
    }
    problem.base_context = PreparedContext::from(base);
    problem.scenario_snapshot = json!({"requirements":{}});
    for (g, group) in problem.groups.iter_mut().enumerate() {
        group.packages = serde_json::from_value(json!([
            {"id":format!("{g}-a"),"statDelta":{"ATKP":20,"MATKP":20,"ATK":40,"MATK":50,"CDMG":16,"SRW":-10,"DEX":1.25}},
            {"id":format!("{g}-b"),"statDelta":{"ATKP":2,"MATKP":2,"CDMG":2,"SRW":20,"LRW":5}},
            {"id":format!("{g}-z"),"statDelta":{"ATKP":20,"MATKP":20,"ATK":40,"MATK":50,"CDMG":16,"SRW":-10,"DEX":1.25}}
        ])).unwrap();
    }
    if case == 4 {
        problem.groups[0].packages[0]
            .stat_delta
            .insert("DAMAGE_P".into(), 5.0);
    }
    problem
}

#[test]
fn range_product_bounds_cover_all_ancestors_and_skip_unsupported_graphs() {
    for case in 0..11 {
        let mut problem = range_product_problem(case);
        problem.prepare_evaluation_stats();
        let roots = problem.prepare_trees().unwrap();
        let supply = problem.trees.supply.as_ref().unwrap();
        assert_eq!(
            supply.product_start.is_some(),
            ![4, 5, 6, 7, 8].contains(&case),
            "case={case}"
        );
        let ancestors: [Vec<Vec<NodeId>>; 4] = std::array::from_fn(|g| {
            let end = roots
                .get(g + 1)
                .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
            (0..3)
                .map(|selected| {
                    (roots[g].0 as usize..end)
                        .map(|n| NodeId(n as u32))
                        .filter(|n| {
                            let mut indices = Vec::new();
                            cluster_indices(&problem.trees, *n, &mut indices);
                            indices.contains(&selected)
                        })
                        .collect()
                })
                .collect()
        });
        for a in 0..3 {
            for b in 0..3 {
                for c in 0..3 {
                    for d in 0..3 {
                        let stats = selection_evaluation_stats(&problem, &[a, b, c, d]);
                        let actual = evaluate_summary_from_map(&problem.base_context, &stats)
                            .unwrap()
                            .optimization_damage_factor;
                        for aa in &ancestors[0][a] {
                            for bb in &ancestors[1][b] {
                                for cc in &ancestors[2][c] {
                                    for dd in &ancestors[3][d] {
                                        assert!(
                                            supply.score(&[*aa, *bb, *cc, *dd]) >= actual - 1e-7,
                                            "case={case} selected={a},{b},{c},{d}"
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    let mut constrained = range_product_problem(1);
    constrained.scenario_snapshot = json!({"requirements":{"maxHp":15000}});
    for group in &mut constrained.groups {
        group.packages[0].stat_delta.insert("MAXHP".into(), 5500.0);
    }
    constrained.prepare_evaluation_stats();
    constrained.prepare_trees().unwrap();
    let supply = constrained.trees.supply.as_ref().unwrap();
    assert!(supply.direction_count > SUPPLY_BASE);
    assert!(
        supply.product_start.is_none(),
        "Keep existing useful utility bounds without extra objective work"
    );
}

#[test]
fn range_product_exact_ties_threads_and_checkpoint_match_raw_oracle() {
    let problem = range_product_problem(1);
    let mut oracle = SearchState {
        best_score: f64::NEG_INFINITY,
        best_id: String::new(),
        best_selected: None,
        evaluations: 0,
    };
    for a in 0..3 {
        for b in 0..3 {
            for c in 0..3 {
                for d in 0..3 {
                    let selected = [a, b, c, d];
                    let stats = selection_stats(&problem, &selected);
                    consider(
                        &problem,
                        &Requirements::new(&problem.scenario_snapshot["requirements"]),
                        &mut oracle,
                        &selected,
                        &stats,
                    )
                    .unwrap();
                }
            }
        }
    }
    for threads in [1, 2, 8, 16, 64] {
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        assert!(session
            .problem
            .trees
            .supply
            .as_ref()
            .unwrap()
            .product_start
            .is_some());
        session
            .advance_parallel_slice_with_control(1, threads, None, None)
            .unwrap();
        let checkpoint =
            serde_json::from_str(&serde_json::to_string(&session.checkpoint().unwrap()).unwrap())
                .unwrap();
        let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
        while !restored.is_complete() {
            restored
                .advance_parallel_slice_with_control(32, threads, None, None)
                .unwrap();
        }
        let result = restored.snapshot();
        assert_eq!(result.score, Some(oracle.best_score));
        assert_eq!(result.best_build.unwrap().id, oracle.best_id);
    }
}

#[test]
fn snapshot_upper_includes_incumbent_before_and_after_restore() {
    let mut session = NativeSearchSession::new(small_problem()).unwrap();
    let mut node = session.heap.pop().unwrap();
    node.upper = session.state.best_score - 1.0;
    session.heap.push(node);
    let result = session.snapshot();
    assert_eq!(result.status, "bounded");
    assert_eq!(result.upper_bound, result.score);
    let restored = NativeSearchSession::from_checkpoint(session.checkpoint().unwrap()).unwrap();
    assert_eq!(restored.snapshot().upper_bound, result.score);
}

#[test]
fn partial_utility_pruning_matches_full_enumeration_with_penalties() {
    let mut problem = small_problem();
    for group in &mut problem.groups {
        group.packages = (0..4)
            .map(|i| NativePackage {
                evaluation_delta: None,
                search_values: Vec::new(),
                id: format!("{}-{i}", group._id),
                stat_delta: Stats::from([
                    ("MAXHP".into(), -6000.0 * i as f64),
                    ("ATKP".into(), 20.0 * i as f64),
                ]),
            })
            .collect();
    }
    let session = NativeSearchSession::new(problem.clone()).unwrap();
    let problem = session.problem.clone();
    let root = session.heap.peek().unwrap();
    let candidates = box_candidate_indices(&problem.trees, &root.clusters);
    let suffix: [Stats; GROUP_COUNT] = std::array::from_fn(|start| {
        root.clusters[start..]
            .iter()
            .fold(Stats::new(), |sum, node| {
                add_stats(sum, &problem.trees[*node].envelope)
            })
    });
    let mut results = Vec::new();
    let mut counts = Vec::new();
    for pruning in [false, true] {
        let incumbent = SharedIncumbent {
            score_bits: AtomicU64::new(f64::NEG_INFINITY.to_bits()),
            record: Mutex::new(SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            }),
        };
        let mut counters = LocalSearchCounters::default();
        assert!(enumerate_box_parallel(
            0,
            &candidates.each_ref().map(|items| items.as_slice()),
            pruning.then_some(&suffix),
            &problem,
            &session.requirements,
            &incumbent,
            &mut counters,
            None,
            None,
            &mut [0; GROUP_COUNT],
            &Stats::new()
        )
        .unwrap());
        let result = incumbent.record.lock().unwrap();
        results.push((result.best_score, result.best_id.clone()));
        counts.push(counters.enumerated);
    }
    assert_eq!(results[0], results[1]);
    assert_eq!(counts[0], 256);
    assert!(counts[1] < counts[0]);
}

#[test]
fn resumable_session_preserves_frontier_and_exact_tie() {
    let uninterrupted = solve_exact(&small_problem()).unwrap();
    let mut session = NativeSearchSession::new(small_problem()).unwrap();
    let first = session.run_slice(1).unwrap();
    assert!(matches!(first.status.as_str(), "bounded" | "exact"));
    if !first.exact {
        assert!(session.ready_work_count() > 0);
        assert!(first.upper_bound.unwrap() >= first.score.unwrap());
    }
    while !session.is_complete() {
        session.run_slice(1).unwrap();
    }
    let resumed = session.run_slice(1).unwrap();
    assert!(resumed.exact);
    assert_eq!(resumed.score, uninterrupted.score);
    assert_eq!(
        resumed.best_build.unwrap().id,
        uninterrupted.best_build.unwrap().id
    );
}

#[test]
fn serialized_checkpoint_resumes_without_frontier_loss_or_duplication() {
    let uninterrupted = solve_exact(&small_problem()).unwrap();
    let mut session = NativeSearchSession::new(small_problem()).unwrap();
    let bounded = session.run_slice(1).unwrap();
    assert!(matches!(bounded.status.as_str(), "bounded" | "exact"));
    let checkpoint = session.checkpoint().unwrap();
    let json = serde_json::to_string(&checkpoint).unwrap();
    let restored = serde_json::from_str(&json).unwrap();
    let mut resumed = NativeSearchSession::from_checkpoint(restored).unwrap();
    while !resumed.is_complete() {
        resumed.run_slice(1).unwrap();
    }
    let result = resumed.run_slice(1).unwrap();
    assert!(result.exact);
    assert_eq!(result.score, uninterrupted.score);
    assert_eq!(
        result.best_build.unwrap().id,
        uninterrupted.best_build.unwrap().id
    );
}

#[test]
fn session_elapsed_excludes_time_parked_between_resumes() {
    let mut session = NativeSearchSession::new(wide_problem()).unwrap();
    let first = session.run_slice(1).unwrap();
    std::thread::sleep(Duration::from_millis(15));
    let parked = session.snapshot();
    assert_eq!(parked.elapsed_ms, first.elapsed_ms);
    let resumed = session.run_slice(1).unwrap();
    assert!(resumed.elapsed_ms >= parked.elapsed_ms);
    assert!(resumed.elapsed_ms < parked.elapsed_ms + 1_000);
}

#[test]
fn cancelled_parallel_search_never_claims_exact() {
    let cancelled = AtomicBool::new(true);
    let result = solve_exact_parallel_cancellable(&small_problem(), 2, &cancelled).unwrap();
    assert_eq!(result.result.status, "cancelled");
    assert!(!result.result.exact);
    assert!(result.result.upper_bound.is_none());
}

#[test]
fn parallel_scheduler_preserves_exact_result_at_supported_thread_counts() {
    for threads in [1, 2, 4, 8, 16, 64] {
        let result = solve_exact_parallel(&small_problem(), threads).unwrap();
        assert!(result.result.exact, "{threads} threads must remain exact");
        assert_eq!(result.result.best_build.unwrap().id, "a||b||c||d");
        assert!(result.threads_used <= threads);
    }
}

#[test]
fn shared_parallel_frontier_drains_descendants_without_losing_exact_tie() {
    let problem = wide_problem();
    let expected = solve_exact(&problem).unwrap();
    let result = solve_exact_parallel(&problem, 2).unwrap();
    assert!(result.result.exact);
    assert_eq!(result.result.score, expected.score);
    assert_eq!(
        result.result.best_build.unwrap().id,
        expected.best_build.unwrap().id
    );
    assert!(result.scheduled_shards > 0);
    assert!(result.result.visited_nodes > result.scheduled_shards as u64);
    assert!(result.scheduler.split_count > 0);
    assert_eq!(
        result.scheduler.worker_busy_micros.len(),
        result.threads_used
    );
}

#[test]
fn parallel_session_slices_resume_to_the_serial_exact_tie() {
    let problem = wide_problem();
    let expected = solve_exact(&problem).unwrap();
    for threads in [1, 2, 8, 64] {
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        while !session.is_complete() {
            session.run_parallel_slice(8, threads).unwrap();
        }
        let result = session.snapshot();
        assert!(result.exact, "{threads} threads must finish exactly");
        assert_eq!(result.score, expected.score);
        assert_eq!(
            result.best_build.unwrap().id,
            expected.best_build.clone().unwrap().id
        );
    }
}

#[test]
fn bounded_parallel_slices_keep_a_safe_upper_and_resume_after_input_reversal() {
    let original = wide_problem();
    let expected = solve_exact(&original).unwrap();
    let expected_score = expected.score.expect("wide oracle must be feasible");
    let expected_id = expected
        .best_build
        .expect("wide oracle must have a build")
        .id;
    let mut reversed = original.clone();
    for group in &mut reversed.groups {
        group.packages.reverse();
    }
    for threads in [1, 2, 4, 8, 16, 64] {
        let mut session = NativeSearchSession::new(reversed.clone()).unwrap();
        let bounded = session.run_parallel_slice(1, threads).unwrap();
        if !bounded.exact {
            assert!(
                bounded
                    .upper_bound
                    .expect("bounded slice must certify an upper")
                    >= expected_score,
                "{threads} threads must never understate an unexplored optimum"
            );
            assert!(session.ready_work_count() > 0);
        }
        while !session.is_complete() {
            session.run_parallel_slice(1, threads).unwrap();
        }
        let resumed = session.snapshot();
        assert!(
            resumed.exact,
            "{threads} threads must resume to exact completion"
        );
        assert_eq!(resumed.score, Some(expected_score));
        assert_eq!(resumed.best_build.expect("exact build").id, expected_id);
    }
}

#[test]
fn controlled_parallel_slice_requeues_cancelled_or_deadline_work() {
    for (cancelled, deadline) in [(true, None), (false, Some(Instant::now()))] {
        let mut session = NativeSearchSession::new(wide_problem()).unwrap();
        let ready_before = session.ready_work_count();
        let cancel = Arc::new(AtomicBool::new(cancelled));
        let result = session
            .run_parallel_slice_with_control(8, 8, Some(&cancel), deadline)
            .unwrap();
        assert!(!result.exact);
        assert_eq!(session.ready_work_count(), ready_before);
    }
}
#[test]
fn supply_budget_fallback_preserves_exhaustive_search_and_json_resume() {
    let mut problem = wide_problem();
    for group in &mut problem.groups {
        for package in &mut group.packages {
            package.stat_delta.insert("CSPD".into(), 1e13);
        }
    }
    let expected = solve_exact(&problem).unwrap();
    let mut session = NativeSearchSession::new(problem).unwrap();
    assert!(session
        .problem
        .trees
        .supply
        .as_ref()
        .unwrap()
        .plan
        .is_none());
    session.run_parallel_slice(1, 4).unwrap();
    let checkpoint =
        serde_json::from_str(&serde_json::to_string(&session.checkpoint().unwrap()).unwrap())
            .unwrap();
    let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
    while !restored.is_complete() {
        restored.run_parallel_slice(64, 4).unwrap();
    }
    assert_eq!(restored.snapshot().score, expected.score);
    assert_eq!(
        restored.snapshot().best_build.unwrap().id,
        expected.best_build.unwrap().id
    );
}

#[test]
fn all_supply_planes_cover_future_options_and_nonlinear_boundaries() {
    use crate::crysta_native_evaluator::joint_supply::SupplyPlan;
    use crate::crysta_native_evaluator::{candidate_cast_metrics, joint_supply::METRICS};
    for case in 0..37 {
        let mut problem = small_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        for (key, value) in [
            ("strBase", 327.0),
            ("dexBase", 400.0),
            ("agiBase", 300.0),
            ("intBase", 320.0),
            ("vitBase", 50.0),
            ("skillMult", 2.1),
            ("wpnAtk", 650.0),
            ("bossDef", 2200.0),
            ("bossMdef", 3000.0),
            ("critF", 15.0),
            ("aspdF", 100.0),
            ("maxMpF", 600.0),
            ("amprF", 12.0),
        ] {
            base[key] = json!(value);
        }
        base["mainType"] = json!(
            [
                "한손검",
                "양손검",
                "활",
                "자동활",
                "지팡이",
                "마도구",
                "권갑",
                "선풍창",
                "발도검",
                "맨손"
            ][case % 10]
        );
        base["atkType"] = json!(if case % 2 == 0 { "PHYS" } else { "MAG" });
        base["attackPowerMode"] =
            json!(["default", "sum", "higher", "atk", "wizardBlend"][case % 5]);
        base["subType"] = json!(["없음", "한손검(듀얼소드)", "화살", "마도구"][case % 4]);
        base["subAtk"] = json!(450);
        base["subStab"] = json!(80);
        base["subRefine"] = json!(12);
        base["dualBringerActive"] = json!(case < 24);
        base["dualBringerLevel"] = json!(10);
        base["targetWeakened"] = json!(true);
        base["spellBurstLevel"] = json!(10);
        base["chkIsUnsheathe"] = json!(case % 3 == 0);
        base["conversionLevel"] = json!(7);
        base["activeBuildConversions"] = if case % 4 == 0 {
            json!([{"conversion":"unsheatheToAtk","value":0.7}])
        } else {
            json!([])
        };
        base["useHigherRangeDamage"] = json!(case % 3 == 1);
        base["halfMdefIgnored"] = json!(case % 5 == 1);
        base["ignoreDefense"] = json!(case % 5 == 2);
        base["ignoreMdef"] = json!(case % 5 == 3);
        base["criticalChanceMultiplier"] = json!(if case % 7 == 0 { -0.5 } else { 1.2 });
        base["cdmgF"] = json!(if case % 6 == 0 { 220.0 } else { 15.0 });
        base["skillStats"] = json!([{"stat":"totalDEX","target":"const","ratio":0.3},{"stat":"totalAGI","target":"mult","ratio":if case%6==1 {-0.001}else{0.001}}]);
        base["normalAttackAmprProfile"] = json!({"passive":[{"percent":12,"flat":3}],"activeCandidates":[{"id":"a","multiplier":1.1},{"id":"b","multiplier":if case%6==2 {-0.5}else{0.9},"flat":40}]});
        if case == 22 {
            base["aspdF"] = json!(-9000.25);
            base["maxHpF"] = json!(-20.75);
        }
        if case == 23 {
            base["crtBase"] = json!(-102);
            base["bossPhysResist"] = json!(130);
        }
        if case == 36 {
            base["wpnAtk"] = json!(10000);
            base["cdmgF"] = json!(2000);
        }
        problem.base_context = PreparedContext::from(base);
        problem.scenario_snapshot = json!({"requirements":{"maxHp":1000,"maxMp":100,"amprBeforeDual":10,"normalAttackCrit":10,"aspd":100}});
        for (g, group) in problem.groups.iter_mut().enumerate() {
            group.packages = (0..3)
                .map(|p| {
                    let mut stats = Stats::new();
                    for (i, key) in crate::crysta_native_evaluator::NATIVE_STAT_KEYS
                        .iter()
                        .enumerate()
                    {
                        let n = ((i * 17 + p * 13 + g * 7 + case * 3) % 31) as f64 - 12.0;
                        let value = if case == 36 && *key == "STR" {
                            -600.0
                        } else if *key == "ELEM_AWAKENING" || *key == "MAGIC_ELEMENT" {
                            if case < 24 && p == (g + case) % 3 {
                                1.0
                            } else {
                                0.0
                            }
                        } else if key.starts_with("ATK_UP_") || key.starts_with("MATK_UP_") {
                            if case < 24 {
                                n / 10.0
                            } else {
                                0.0
                            }
                        } else if *key == "MAXHP"
                            || *key == "MAXMP"
                            || *key == "ASPD"
                            || *key == "CSPD"
                        {
                            n * 25.0 + 0.25
                        } else if case == 21 && key.ends_with('P') {
                            -40.0 + n
                        } else {
                            n + 0.125
                        };
                        stats.insert((*key).into(), value);
                    }
                    NativePackage {
                        id: format!("{g}-{p}"),
                        stat_delta: stats,
                        evaluation_delta: None,
                        search_values: Vec::new(),
                    }
                })
                .collect();
        }
        problem.prepare_evaluation_stats();
        let roots = problem.prepare_trees().unwrap();
        let supply = problem.trees.supply.as_ref().unwrap();
        assert!(supply.plan.is_some());
        let groups: Vec<Vec<_>> = problem
            .groups
            .iter()
            .map(|g| {
                g.packages
                    .iter()
                    .map(NativePackage::evaluation_stats)
                    .collect()
            })
            .collect();
        let plan = SupplyPlan::prepare(&problem.base_context, &groups).unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let ancestors: [Vec<Vec<NodeId>>; 4] = std::array::from_fn(|g| {
            let end = roots
                .get(g + 1)
                .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
            (0..3)
                .map(|selected| {
                    (roots[g].0 as usize..end)
                        .map(|n| NodeId(n as u32))
                        .filter(|n| {
                            let mut indices = Vec::new();
                            cluster_indices(&problem.trees, *n, &mut indices);
                            indices.contains(&selected)
                        })
                        .collect()
                })
                .collect()
        });
        for a in 0..3 {
            for b in 0..3 {
                for c in 0..3 {
                    for d in 0..3 {
                        let selected = [a, b, c, d];
                        let stats = selection_evaluation_stats(&problem, &selected);
                        let raw = evaluate_summary_from_map(&problem.base_context, &stats).unwrap();
                        let goals = utility_values(&problem.base_context, &stats).unwrap();
                        let cast = candidate_cast_metrics(&problem.base_context, &stats);
                        let actual = [
                            raw.optimization_damage_factor,
                            goals[0],
                            goals[1],
                            goals[2],
                            goals[3],
                            goals[4],
                            cast[0],
                            cast[1],
                        ];
                        for (i, actual_value) in actual.iter().enumerate().take(METRICS) {
                            let form = &plan.upper[i];
                            let upper = form.constant
                                + form.error
                                + (0..4)
                                    .map(|g| {
                                        form.package(
                                            problem.groups[g].packages[selected[g]]
                                                .evaluation_stats(),
                                        )
                                    })
                                    .sum::<f64>();
                            assert!(upper>=actual_value-1e-7,"case={case} selected={selected:?} metric={i}: plane={upper} actual={actual_value}");
                            if i < SUPPLY_METRICS {
                                assert!(
                                    supply.metric(&roots, i) >= actual[i] - 1e-7,
                                    "root case={case} metric={i}"
                                );
                            }
                        }
                        for aa in &ancestors[0][a] {
                            for bb in &ancestors[1][b] {
                                for cc in &ancestors[2][c] {
                                    for dd in &ancestors[3][d] {
                                        let box_ = [*aa, *bb, *cc, *dd];
                                        for (i, actual_value) in
                                            actual.iter().enumerate().take(SUPPLY_METRICS)
                                        {
                                            assert!(
                                                supply.metric(&box_, i) >= actual_value - 1e-7,
                                                "ancestor case={case} metric={i}"
                                            );
                                        }
                                        if (0..5).all(|i| requirements.accepts_value(i, goals[i])) {
                                            assert!(
                                                problem.trees.joint_utilities_possible(&box_),
                                                "joint pruned feasible case={case}"
                                            );
                                            let bound =
                                                evaluate_box(&problem, &box_, Some(&requirements))
                                                    .unwrap()
                                                    .expect("feasible ancestor");
                                            assert!(
                                                bound.optimization_damage_factor
                                                    >= actual[0] - 1e-7,
                                                "combined ancestor case={case}"
                                            );
                                        }
                                    }
                                }
                            }
                        }
                        if (0..5).all(|i| requirements.accepts_value(i, goals[i])) {
                            assert!(
                                supply.score(&roots) >= actual[0] - 1e-7,
                                "weighted root case={case}"
                            );
                        }
                    }
                }
            }
        }
        let mut oracle = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; 4],
            &Stats::new(),
            &mut oracle,
            &mut 0,
        )
        .unwrap();
        let expected = oracle.best_selected.map(|_| oracle.best_score);
        let serial = solve_exact(&problem).unwrap();
        assert_eq!(serial.score, expected, "serial oracle case={case}");
        assert_eq!(
            serial.best_build.map(|b| b.id),
            oracle.best_selected.map(|_| oracle.best_id.clone())
        );
        for threads in [1, 2, 4, 8, 16, 64] {
            let mut reversed = problem.clone();
            for g in &mut reversed.groups {
                g.packages.reverse();
            }
            let mut session = NativeSearchSession::new(reversed).unwrap();
            session.run_parallel_slice(1, threads).unwrap();
            let checkpoint = serde_json::from_str(
                &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
            )
            .unwrap();
            let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
            while !restored.is_complete() {
                let partial = restored.run_parallel_slice(1, threads).unwrap();
                if let Some(expected) = expected {
                    assert!(partial.upper_bound.unwrap() >= expected - 1e-7);
                }
            }
            let result = restored.snapshot();
            assert_eq!(
                result.score, expected,
                "parallel oracle case={case} threads={threads}"
            );
            assert_eq!(
                result.best_build.map(|b| b.id),
                oracle.best_selected.map(|_| oracle.best_id.clone())
            );
        }
    }
}
