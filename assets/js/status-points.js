         (function () {
            var STATUS_MIN = 1;
            var STATUS_CAP = 510;

            function integer(val, fallback) {
                var n = parseInt(val, 10);
                return isNaN(n) ? (fallback !== undefined ? fallback : 0) : n;
            }

            function pointLimit() {
                var levelInput = document.getElementById('charLevel');
                var level = Math.max(1, integer(levelInput.value, 1));
                levelInput.value = level;
                return level * 2 + (Math.round(level / 10) * 10) / 2 + 20 + 5;
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
                var limit = pointLimit();
                var statusInputs = inputs();

                statusInputs.forEach(function (input) {
                    var v = integer(input.value, STATUS_MIN);
                    if (v < STATUS_MIN) v = STATUS_MIN;
                    if (v > STATUS_CAP) v = STATUS_CAP;
                    input.value = v;
                    input.min = STATUS_MIN;
                    input.max = STATUS_CAP;
                    input.step = "1";
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

                var total = statusInputs.reduce(function (sum, input) { return sum + Number(input.value); }, 0);
                var summary = document.getElementById('statusPointSummary');
                summary.textContent = total + ' / ' + limit;
                summary.title = 'Invested status points: ' + total + ' / ' + limit;
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
        }());


    // Extensible skill-tree simulator. Definitions are embedded above for standalone HTML use.
