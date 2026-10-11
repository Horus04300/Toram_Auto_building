// Fixed headless timing boundary. No DOM, rendering callbacks or engine-local clocks.
export async function measureComputation({ compile, client, now = () => performance.now(), maxDurationMs = 120000, sliceMs = 30000 }) {
  if (!(maxDurationMs > 0) || !(sliceMs > 0 && sliceMs <= 30000)) throw new Error('Invalid measurement budget');
  const started = now();
  let compiledAt = null, slices = 0, progressEvents = 0, cached = false;
  const callbacks = {
    onProgress() { progressEvents++; },
    onComplete(result, metadata) { cached ||= Boolean(metadata?.cached); }
  };
  try {
    const problem = compile();
    compiledAt = now();
    const options = { timeLimitMs:sliceMs, progressIntervalMs:100, maxParetoComparisons:1000000 };
    let result = await client.optimize(problem, callbacks, options);
    slices++;
    while (result?.continuationId && client.hasContinuation()
      && ['bounded', 'no-incumbent-yet'].includes(result.status) && now() - started < maxDurationMs) {
      result = await client.resume(callbacks, options);
      slices++;
    }
    // The product client has now restored packages and performed final JS evaluation.
    const finished = now();
    return { result, timing:{ totalMs:finished-started, compileMs:compiledAt-started,
      executionAndResultMs:finished-compiledAt, slices, progressEvents, cached } };
  } catch (cause) {
    const error = new Error(String(cause?.message || cause), { cause });
    error.measurement = { totalMs:now()-started, compileMs:compiledAt === null ? null : compiledAt-started,
      slices, progressEvents, cached, status:'error' };
    throw error;
  }
}
