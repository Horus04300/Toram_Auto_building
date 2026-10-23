// Small test problems only: enumerate every combination without pruning or seeds.
export function exhaustiveSearch(problem, { evaluateStats }) {
  let bestBuild = null, outcomes = null, score = null, evaluations = 0;
  function visit(index, packages, stats) {
    if (index < problem.groups.length) {
      for (const candidate of problem.groups[index].packages) {
        const sum = { ...stats };
        for (const [key, value] of Object.entries(candidate.statDelta || {})) sum[key] = (sum[key] || 0) + value;
        visit(index + 1, [...packages, candidate], sum);
      }
      return;
    }
    evaluations++;
    const evaluated = evaluateStats(stats);
    if (!evaluated.constraints.feasible) return;
    const next = evaluated.damage.expected, id = packages.map(candidate => candidate.id).join('||');
    if (!bestBuild || next > score + 1e-9 || (Math.abs(next - score) <= 1e-9 && id < bestBuild.id)) {
      score = next; outcomes = evaluated; bestBuild = { id, packages, statDelta:stats };
    }
  }
  visit(0, [], {});
  return { status:bestBuild ? 'exact' : 'invalid', score, bestBuild, outcomes, evaluations };
}
