# Coryn Club skill icons

- Source: https://coryn.club/skill_simulator.php
- Skills listed: 480
- Download failures: 15

## Skill tree simulator data

`skill_tree_data.js` is the simulator's source of truth. It contains each tree's category, grid size, and skills (`id`, `name`, `prereq`, `x`, `y`, `icon`). The UI reads this file without hard-coded per-tree layouts.

To add a new skill, add its icon to the matching tree folder, then add its record to that tree's `skills` array. `prereq` is the parent skill ID, or `-1` for a root skill; `x` and `y` are zero-based grid coordinates. A new tree also needs a folder, `title.png`, and one new tree object in this file.