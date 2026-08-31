(function (root) {
    var STATUS_MIN = 1;
    var STATUS_CAP = 510;
    var LEVEL_POINT_PER_LEVEL = 2;
    var FIXED_STATUS_BONUS = 25;
    var OFFICIAL_LEVEL_CAP = Object.freeze({
        level: 325,
        sourceUrl: 'https://toram.jp/information/detail/?information_id=11036',
        verifiedAt: '2026-08-24'
    });

    // Later official-cap refreshers may replace this provider without changing the
    // status-point calculation contract.
    if (!root.ToramOfficialLevelCap) {
        root.ToramOfficialLevelCap = Object.freeze({
            getCurrent: function () { return OFFICIAL_LEVEL_CAP; }
        });
    }

    function integer(val, fallback) {
        var n = parseInt(val, 10);
        return isNaN(n) ? (fallback !== undefined ? fallback : 0) : n;
    }

    function officialLevelCap() {
        var provider = root.ToramOfficialLevelCap;
        var record = provider && typeof provider.getCurrent === 'function' ? provider.getCurrent() : OFFICIAL_LEVEL_CAP;
        return Math.max(1, integer(record && record.level, OFFICIAL_LEVEL_CAP.level));
    }

    // Player-level emblems are granted at Lv.5, 15, 25, ... and are shared by
    // every parameter after the account's highest parameter reaches that level.
    function playerLevelEmblemPoints(highestParameterLevel) {
        return Math.round(Math.max(1, integer(highestParameterLevel, 1)) / 10) * 5;
    }

    function pointBreakdown(characterLevel, highestParameterLevel) {
        var level = Math.max(1, integer(characterLevel, 1));
        var highest = Math.max(1, integer(highestParameterLevel, officialLevelCap()));
        return {
            characterLevel: level,
            highestParameterLevel: highest,
            levelPoints: level * LEVEL_POINT_PER_LEVEL,
            emblemPoints: playerLevelEmblemPoints(highest),
            fixedPoints: FIXED_STATUS_BONUS,
            total: level * LEVEL_POINT_PER_LEVEL + playerLevelEmblemPoints(highest) + FIXED_STATUS_BONUS
        };
    }

    function pointLimitForLevel(characterLevel) {
        return pointBreakdown(characterLevel, officialLevelCap()).total;
    }

    root.ToramStatusPoints = Object.freeze({
        officialLevelCap: officialLevelCap,
        playerLevelEmblemPoints: playerLevelEmblemPoints,
        pointBreakdown: pointBreakdown,
        pointLimitForLevel: pointLimitForLevel
    });

    if (typeof document === 'undefined') return;

    function pointLimit() {
        var levelInput = document.getElementById('charLevel');
        var cap = officialLevelCap();
        var level = Math.max(1, Math.min(cap, integer(levelInput.value, 1)));
        levelInput.value = level;
        levelInput.max = cap;
        return pointLimitForLevel(level);
    }

    function inputs() {
        return [
            document.getElementById('strBase'),
            document.getElementById('intBase'),
            document.getElementById('vitBase'),
            document.getElementById('agiBase'),
            document.getElementById('dexBase')
        ];
    }

    function update(changedInput) {
        var cap = officialLevelCap();
        var breakdown = pointBreakdown(document.getElementById('charLevel').value, cap);
        var limit = pointLimit();
        var statusInputs = inputs();

        statusInputs.forEach(function (input) {
            var v = integer(input.value, STATUS_MIN);
            if (v < STATUS_MIN) v = STATUS_MIN;
            if (v > STATUS_CAP) v = STATUS_CAP;
            input.value = v;
            input.min = STATUS_MIN;
            input.max = STATUS_CAP;
            input.step = '1';
        });

        var total = statusInputs.reduce(function (sum, input) { return sum + Number(input.value); }, 0);

        if (total > limit) {
            var excess = total - limit;
            if (changedInput) {
                var currentChanged = Number(changedInput.value);
                var allowedChanged = Math.max(STATUS_MIN, currentChanged - excess);
                changedInput.value = allowedChanged;
            } else {
                var reduction = excess;
                for (var i = statusInputs.length - 1; i >= 0 && reduction > 0; i--) {
                    var inp = statusInputs[i];
                    var curr = Number(inp.value);
                    var reducible = curr - STATUS_MIN;
                    var take = Math.min(reducible, reduction);
                    inp.value = curr - take;
                    reduction -= take;
                }
            }
        }

        total = statusInputs.reduce(function (sum, input) { return sum + Number(input.value); }, 0);
        var summary = document.getElementById('statusPointSummary');
        summary.textContent = total + ' / ' + limit;
        summary.title = '투자 스테이터스 포인트: ' + total + ' / ' + limit + '\n훈장: 공식 최대 레벨 Lv.' + cap + ' 기준 +' + breakdown.emblemPoints + 'pt';
        summary.setAttribute('aria-label', summary.title.replace('\n', ', '));
    }

    function investToMaximum(inputId) {
        var selected = document.getElementById(inputId);
        var otherTotal = inputs().reduce(function (total, input) {
            return total + (input === selected ? 0 : Number(input.value));
        }, 0);
        selected.value = Math.max(STATUS_MIN, Math.min(STATUS_CAP, pointLimit() - otherTotal));
        update(selected);
        selected.focus();
    }

    function resetToMinimum() {
        inputs().forEach(function (input) { input.value = STATUS_MIN; });
        update();
    }

    if (typeof root.addEventListener === 'function') {
        root.addEventListener('toram:official-level-cap-updated', function () { update(); });
    }

    document.getElementById('charLevel').addEventListener('input', function () { update(); });
    inputs().forEach(function (input) {
        input.addEventListener('input', function () { update(input); });
        input.addEventListener('change', function () { update(input); });
    });
    document.querySelectorAll('.stat-easy-btn').forEach(function (button) {
        button.addEventListener('click', function () { investToMaximum(button.dataset.statInput); });
    });
    document.getElementById('statusResetBtn').addEventListener('click', resetToMinimum);
    update();
}(window));