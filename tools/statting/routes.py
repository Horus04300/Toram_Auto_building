"""Bounded monotone route experiments, not an in-app recommender."""
from itertools import combinations, permutations, product
from native_model import require


def partitions(values):
    """Every ordered partition; each negative is assigned once at its target."""
    if not values:
        yield ()
        return
    for count in range(1, len(values)+1):
        for group in combinations(values, count):
            rest = tuple(x for x in values if x not in group)
            for tail in partitions(rest):
                yield (group,)+tail


def advance(model, profile, state, potential, update):
    update = {i: v for i, v in update.items() if state.get(i, 0) != v}
    if not update:
        return state, potential, None
    next_state, after, rate = model.transition(profile, state, potential, update)
    require(rate == 100 and after >= 1 and len(next_state) < 8, 'unsafe/noncontinuable prefix')
    return next_state, after, update


def prefixes(model, profile, positives, negative_count):
    candidates = {((), profile['startingPotential']): ({}, profile['startingPotential'], [])}
    identities = tuple(positives)
    for size in range(1, min(len(identities), 7-negative_count)+1):
        for subset in combinations(identities, size):
            try:
                seed, potential, action = advance(model, profile, {}, profile['startingPotential'], {i: 1 for i in subset})
            except ValueError:
                continue
            first = [action]
            candidates[(tuple(seed.items()), potential)] = (seed, potential, first)
            for identity in identities:
                state, current, path = seed, potential, first
                if identity not in state and len(state)+negative_count >= 7:
                    continue
                for value in range(state.get(identity, 0)+1, positives[identity]+1):
                    try:
                        state, current, action = advance(model, profile, state, current, {identity: value})
                    except ValueError:
                        break
                    path = path+[action]
                    candidates[(tuple(state.items()), current)] = (state, current, path)
    # shortcut: bounded prefix representatives; exhaustive small-domain oracle
    # measures the loss before expanding to more expensive route families.
    groups = {}
    for state, potential, path in candidates.values():
        key = tuple(sorted(state))
        rank = (potential, len(path), tuple(state.items()))
        if key not in groups or rank < groups[key][0]:
            groups[key] = (rank, (state, potential, path))
    chosen = [entry[1] for entry in groups.values()]
    chosen += sorted(candidates.values(), key=lambda s: (s[1], len(s[2]), tuple(s[0].items())))[:8]
    unique = {}
    for item in chosen:
        unique[(tuple(item[0].items()), item[1])] = item
    return list(unique.values()), len(candidates)


def finish_variants(model, profile, state, potential, path, target):
    helpers = [i for i, v in target.items() if v > state.get(i, 0)
               and model.rows[i]['fields']['UsePotential'] == 1
               and model.rows[i]['fields']['DoubleUse'] == 0]
    plans = [((), False)]
    for size in range(1, len(helpers)+1):
        for order in permutations(helpers, size):
            plans.extend([(order, False), (order, True)])
    for helpers_order, through_cap in plans:
        current, remaining, steps = state, potential, path
        try:
            for identity in helpers_order:
                upper = target[identity] if through_cap else min(target[identity], model.rows[identity]['fields']['BaseMax'])
                for value in range(current.get(identity, 0)+1, upper+1):
                    current, remaining, action = advance(model, profile, current, remaining, {identity: value})
                    steps = steps+[action]
            last = {i: v for i, v in target.items() if current.get(i, 0) != v}
            if last:
                final, after, rate = model.transition(profile, current, remaining, last)
                require(rate > 0, 'client disables zero-percent execution')
                steps = steps+[last]
            else:
                final, after, rate = current, remaining, 100
            require(final == target, 'target mismatch')
            yield {'warningPercent': rate, 'afterPotential': after, 'steps': steps,
                   'helperOrder': helpers_order, 'splitThroughCap': through_cap}
        except ValueError:
            continue


def route_rank(result):
    return (result['warningPercent'], -len(result['steps']), result['afterPotential'])


def mixed_prefixes(model, profile, positives, negatives):
    # The first oracle miss needs a small refund in the SAME action as a
    # category-activating positive. Splitting all negatives first misses it.
    seeds = ({}, *({identity: 1} for identity in positives))
    for seed in seeds:
        try:
            state, current, action = advance(model, profile, {}, profile['startingPotential'], seed)
        except ValueError:
            continue
        path = [action] if action else []
        for positive in positives:
            value = state.get(positive, 0)+1
            if value > positives[positive]:
                continue
            for negative, target in negatives.items():
                for amount in range(1, min(4, abs(target))+1):
                    try:
                        mixed, after, action = advance(model, profile, state, current,
                                                       {positive: value, negative: -amount})
                        rest = {i: v for i, v in negatives.items() if mixed.get(i) != v}
                        tail, remaining, refund = advance(model, profile, mixed, after, rest)
                        yield tail, remaining, path+[action]+([refund] if refund else [])
                    except ValueError:
                        continue


def plan(model, profile, positives, negatives):
    require(set(positives).isdisjoint(negatives), 'positive and negative type conflict')
    target = dict(positives)
    target.update(negatives)
    require(len(target) <= 8, 'target exceeds usable slots')
    for i, v in target.items():
        model.validate_value(i, v)
    prefix_states, prefix_count = prefixes(model, profile, positives, len(negatives))
    empty = ({}, profile['startingPotential'], [])
    if not any(not state for state, _, _ in prefix_states):
        prefix_states.insert(0, empty)
    orders = list(partitions(tuple(negatives)))
    best = {}
    attempted, completed, unique_paths = 0, 0, set()
    for start, potential, prefix in prefix_states:
        for groups in orders:
            attempted += 1
            state, current, path = start, potential, prefix
            try:
                for group in groups:
                    updates = {i: negatives[i] for i in group}
                    state, current, action = advance(model, profile, state, current, updates)
                    path = path+[action]
            except ValueError:
                continue
            for result in finish_variants(model, profile, state, current, path, target):
                completed += 1
                unique_paths.add(tuple(tuple(action.items()) for action in result['steps']))
                split = bool(result['helperOrder'])
                family = ('drain' if prefix else 'negative-first')+('-split' if split else '')
                result = dict(result, family=family, prefixActions=len(prefix), negativeGroups=len(groups))
                for key in (family, 'combined'):
                    if key not in best or route_rank(result) > route_rank(best[key]):
                        best[key] = result
                if not prefix and len(groups) == 1 and not split:
                    best['baseline'] = result
    for state, current, prefix in mixed_prefixes(model, profile, positives, negatives):
        attempted += 1
        for result in finish_variants(model, profile, state, current, prefix, target):
            completed += 1
            unique_paths.add(tuple(tuple(action.items()) for action in result['steps']))
            family = 'mixed-split' if result['helperOrder'] else 'mixed'
            result = dict(result, family=family, prefixActions=len(prefix), negativeGroups='mixed-then-remainder')
            for key in (family, 'combined'):
                if key not in best or route_rank(result) > route_rank(best[key]):
                    best[key] = result
    return {'best': best, 'prefixStatesGenerated': prefix_count,
            'negativeSchedulesAttempted': attempted, 'completedRoutes': completed,
            'uniqueCompletedRoutes': len(unique_paths)}


def exhaustive(model, profile, target):
    """Exact best warning% for a small monotone domain, <=one repeated category.

    At identical option values more remaining potential cannot worsen a positive
    cost's bounded warning%; negative costs already give100. Thus max potential
    is sufficient for this oracle's score (not minimum steps or reversal odds).
    """
    ids = tuple(target)
    require(len(ids) <= 3, 'oracle is intentionally a small independent domain')
    maxima = tuple(abs(target[i]) for i in ids)
    signs = tuple(1 if target[i] > 0 else -1 for i in ids)
    states = {(0,)*len(ids): (profile['startingPotential'], [])}
    best, edges = None, 0
    for vector in product(*(range(m+1) for m in maxima)):
        if vector not in states:
            continue
        potential, path = states[vector]
        state = {i: signs[k]*v for k, (i, v) in enumerate(zip(ids, vector)) if v}
        for next_vector in product(*(range(v, m+1) for v, m in zip(vector, maxima))):
            if next_vector == vector:
                continue
            updates = {i: signs[k]*next_vector[k] for k, i in enumerate(ids) if next_vector[k] != vector[k]}
            final, after, rate = model.transition(profile, state, potential, updates)
            edges += 1
            if next_vector == maxima:
                result = {'warningPercent': rate, 'afterPotential': after, 'steps': path+[updates]}
                if best is None or route_rank(result) > route_rank(best):
                    best = result
            elif rate == 100 and after >= 1:
                if next_vector not in states or after > states[next_vector][0]:
                    states[next_vector] = (after, path+[updates])
    return {'best': best, 'states': len(states), 'edges': edges,
            'scope': 'exact bounded warning percent, monotone values; no reversal or minimum-action proof'}
