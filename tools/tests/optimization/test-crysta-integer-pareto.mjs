import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
const optimizer = require('../../../web/src/optimization/candidate-preparation.js');

// Reference uses the unchanged public floating-point dominance predicate.
function reference(packages, keys, maxComparisons) {
  const ordered = packages.slice().sort((a,b) => a.id < b.id ? -1 : a.id > b.id ? 1 : 0);
  const seen = new Set(), unique = [];
  for (const item of ordered) {
    const key = keys.map(k => k + ':' + (Number(item.statDelta?.[k]) || 0)).join('|');
    if (!seen.has(key)) { seen.add(key); unique.push(item); }
  }
  const frontier = [];
  let comparisons = 0, complete = true;
  for (let i=0; i<unique.length; i++) {
    let rejected = false;
    for (const prior of frontier) {
      if (++comparisons > maxComparisons) { complete = false; break; }
      if (optimizer.dominates(prior.statDelta, unique[i].statDelta, keys)) { rejected = true; break; }
    }
    if (!complete) { frontier.push(...unique.slice(i)); break; }
    if (!rejected) frontier.push(unique[i]);
  }
  return { ids:frontier.map(p => p.id), comparisons, complete, duplicates:ordered.length-unique.length };
}
let checked = 0;
function check(packages, keys) {
  for (const maxComparisons of [1,2,7,1000000]) {
    const actual = optimizer.strictParetoFrontier(packages, keys, { maxComparisons });
    const expected = reference(packages, keys, maxComparisons);
    assert.deepEqual({ ids:actual.packages.map(p => p.id), comparisons:actual.comparisons,
      complete:actual.complete, duplicates:actual.duplicateCount }, expected);
    assert.ok(actual.packages.every(p => packages.includes(p)), 'Return the original packages and all raw options');
    checked++;
  }
}
const values = [-2147483648,-2147483647,-1,-0,0,1,2147483646,2147483647];
const integerGrid = values.flatMap((x,i) => values.map((y,j) => ({ id:`p-${i}-${j}`, statDelta:{ X:x,Y:y,UNUSED:0.125 } })));
check(integerGrid, ['X','Y']);
check([...integerGrid].reverse(), ['X','Y']);
for (const special of [0.5,1e-10,1+5e-10,-1-5e-10,2147483648,-2147483649,Infinity,-Infinity,NaN,'17',undefined,null]) {
  check([{ id:'a',statDelta:{ X:special,Y:2 } }, ...integerGrid], ['X','Y']);
}
check(integerGrid, []);
check([], ['X']);
check([{ id:'one' }], ['X']);
let seed = 1831;
const random = () => { seed = (Math.imul(seed,1664525)+1013904223) >>> 0; return seed; };
for (let trial=0; trial<300; trial++) {
  const keys = ['A','B','C','D'].slice(0,1+random()%4);
  const packages = Array.from({ length:2+random()%50 }, (_,i) => ({ id:`id-${i}`, statDelta:Object.fromEntries(
    keys.filter(() => random()%5 !== 0).map(k => [k,(random()%41-20)/(trial%3 === 0 ? 10 : 1)])
  ) }));
  packages.push({ ...packages[0], id:'duplicate-z' });
  check(packages, keys);
}
console.log(`CrystaOptimization integer Pareto: PASS (${checked} frontier/budget comparisons, i32 limits, fractional/epsilon fallback, raw package identity)`);
