(function (root) {
    var FALLBACK = Object.freeze({
        level: 325,
        sourceUrl: 'https://toram.jp/information/detail/?information_id=11036',
        verifiedAt: '2026-08-24',
        source: 'bundled-official-record'
    });
    var CACHE_KEY = 'toram-official-level-cap-v1';
    var CACHE_MAX_AGE_MS = 24 * 60 * 60 * 1000;
    var current = loadCachedRecord() || FALLBACK;
    var refreshPromise = null;

    function integer(value, fallback) {
        var parsed = parseInt(value, 10);
        return isNaN(parsed) ? fallback : parsed;
    }

    function validRecord(record) {
        return record && integer(record.level, 0) >= FALLBACK.level;
    }

    function readStorage() {
        try { return root.localStorage; } catch (_) { return null; }
    }

    function loadCachedRecord() {
        var storage = readStorage();
        if (!storage) return null;
        try {
            var record = JSON.parse(storage.getItem(CACHE_KEY));
            return validRecord(record) ? record : null;
        } catch (_) {
            return null;
        }
    }

    function saveCachedRecord(record) {
        var storage = readStorage();
        if (!storage) return;
        try { storage.setItem(CACHE_KEY, JSON.stringify(record)); } catch (_) { /* cache is optional */ }
    }

    function isFresh(record) {
        return record && Date.now() - integer(record.checkedAt, 0) < CACHE_MAX_AGE_MS;
    }

    function extractConfirmedLevelCap(html) {
        var match;
        var maximum = 0;
        var expression = /Lv上限[「"]\s*(\d+)\s*[」"][^。<\n]{0,80}開放(?!予定)/g;
        while ((match = expression.exec(html))) {
            maximum = Math.max(maximum, integer(match[1], 0));
        }
        return maximum;
    }

    function detailPaths(indexHtml) {
        var paths = [];
        var seen = Object.create(null);
        var expression = /href=["'](\/information\/detail\/\?information_id=\d+)/g;
        var match;
        while ((match = expression.exec(indexHtml))) {
            if (!seen[match[1]]) {
                seen[match[1]] = true;
                paths.push(match[1]);
            }
        }
        return paths.slice(0, 20);
    }

    function notify(record) {
        if (typeof root.dispatchEvent !== 'function') return;
        try {
            root.dispatchEvent(new CustomEvent('toram:official-level-cap-updated', { detail: record }));
        } catch (_) {
            // Older WebViews may not expose CustomEvent constructors in this context.
        }
    }

    function fetchLatest() {
        if (typeof root.fetch !== 'function') return Promise.resolve(current);
        if (refreshPromise) return refreshPromise;
        if (isFresh(current)) return Promise.resolve(current);

        refreshPromise = root.fetch('https://toram.jp/information/?type_code=all', { cache: 'no-store' })
            .then(function (response) {
                if (!response.ok) throw new Error('Official notice index unavailable');
                return response.text();
            })
            .then(function (indexHtml) {
                var paths = detailPaths(indexHtml);
                return Promise.all(paths.map(function (path) {
                    return root.fetch('https://toram.jp' + path, { cache: 'no-store' })
                        .then(function (response) { return response.ok ? response.text() : ''; })
                        .then(function (html) {
                            return { level: extractConfirmedLevelCap(html), sourceUrl: 'https://toram.jp' + path };
                        })
                        .catch(function () { return { level: 0 }; });
                }));
            })
            .then(function (records) {
                var best = records.reduce(function (selected, record) {
                    return record.level > selected.level ? record : selected;
                }, { level: current.level });
                var next = {
                    level: Math.max(current.level, best.level),
                    sourceUrl: best.level > current.level ? best.sourceUrl : current.sourceUrl,
                    verifiedAt: new Date().toISOString().slice(0, 10),
                    checkedAt: Date.now(),
                    source: best.level > current.level ? 'official-live-notice' : current.source
                };
                current = next;
                saveCachedRecord(next);
                notify(next);
                return current;
            })
            .catch(function () {
                // A failed online check must never reduce or invalidate a known official cap.
                return current;
            })
            .finally(function () { refreshPromise = null; });
        return refreshPromise;
    }

    root.ToramOfficialLevelCap = Object.freeze({
        getCurrent: function () { return current; },
        refresh: fetchLatest,
        extractConfirmedLevelCap: extractConfirmedLevelCap
    });

    // The known official record is available immediately; the online confirmation is non-blocking.
    fetchLatest();
}(window));