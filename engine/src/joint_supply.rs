//! Candidate-correlated affine outer bounds for the complete calculation graph.
//! Each form is supported over actual packages, not coordinate-wise maxima.
//! McCormick planes preserve variable bases times variable percentages. Floors,
//! caps and conditional branches are outer relaxations, never game formula edits.
use super::native_stats::{KEYS, STAT_COUNT};
use super::{
    array, floor_ratio, number, text, ContextLookup, Invariant, NativeStats, PreparedContext,
};
use std::ops::{Add, Div, Mul, Neg, Sub};
use std::sync::Arc;
fn flag(base: &PreparedContext, key: &str) -> bool {
    base.context_flag(key)
}

pub const METRICS: usize = 8; // damage, five goals, CSPD, cast reduction

#[derive(Clone, Debug)]
pub struct Form {
    pub constant: f64,
    pub coefficients: [f64; STAT_COUNT],
    pub error: f64,
}
impl Form {
    fn constant(value: f64) -> Self {
        Self {
            constant: value,
            coefficients: [0.0; STAT_COUNT],
            error: 0.0,
        }
    }
    fn magnitude(&self, domain: &Domain) -> f64 {
        self.constant.abs()
            + self
                .coefficients
                .iter()
                .zip(domain.abs)
                .map(|(a, b)| a.abs() * b)
                .sum::<f64>()
    }
    fn combine(&self, other: &Self, a: f64, b: f64, domain: &Domain) -> Self {
        let mut value = Self {
            constant: self.constant * a + other.constant * b,
            coefficients: std::array::from_fn(|i| {
                self.coefficients[i] * a + other.coefficients[i] * b
            }),
            error: self.error * a.abs() + other.error * b.abs(),
        };
        // Covers coefficient arithmetic, package aggregation and dot products.
        // Large/nonfinite arithmetic disables this optional plan at preparation.
        value.error += 128.0
            * f64::EPSILON
            * (1.0
                + value.magnitude(domain)
                + self.magnitude(domain) * a.abs()
                + other.magnitude(domain) * b.abs());
        value
    }
    pub fn package(&self, stats: &NativeStats) -> f64 {
        let mut value = 0.0;
        for (key, coefficient) in KEYS.iter().zip(self.coefficients) {
            if coefficient != 0.0 {
                value += coefficient * stats.get(key).copied().unwrap_or(0.0);
            }
        }
        value
    }
}

struct Domain {
    groups: Vec<Vec<[f64; STAT_COUNT]>>,
    abs: [f64; STAT_COUNT],
}
impl Domain {
    fn support(&self, form: &Form, high: bool) -> f64 {
        let terms: Vec<_> = form
            .coefficients
            .iter()
            .copied()
            .enumerate()
            .filter(|(_, c)| *c != 0.0)
            .collect();
        if terms.is_empty() {
            if form.error == 0.0 {
                return form.constant;
            }
            let error = form.error + 128.0 * f64::EPSILON * (1.0 + form.constant.abs());
            return if high {
                form.constant + error
            } else {
                form.constant - error
            };
        }
        let mut result = form.constant;
        for group in &self.groups {
            let value = group
                .iter()
                .map(|point| terms.iter().map(|(i, c)| point[*i] * c).sum::<f64>())
                .reduce(|a, b| if high { a.max(b) } else { a.min(b) })
                .unwrap();
            result += value;
        }
        let error = form.error + 128.0 * f64::EPSILON * (1.0 + form.magnitude(self));
        if high {
            result + error
        } else {
            result - error
        }
    }
}

#[derive(Clone)]
struct Expr {
    domain: Arc<Domain>,
    lower: Form,
    upper: Form,
    low: f64,
    high: f64,
}
impl Expr {
    fn new(domain: Arc<Domain>, lower: Form, upper: Form) -> Self {
        let low = domain.support(&lower, false);
        let high = domain.support(&upper, true);
        Self {
            domain,
            lower,
            upper,
            low,
            high,
        }
    }
    fn c(&self, value: f64) -> Self {
        Self::new(
            self.domain.clone(),
            Form::constant(value),
            Form::constant(value),
        )
    }
    fn interval(&self, low: f64, high: f64) -> Self {
        Self::new(
            self.domain.clone(),
            Form::constant(low),
            Form::constant(high),
        )
    }
    fn scale(self, amount: f64) -> Self {
        if amount == 0.0 || (self.low == 0.0 && self.high == 0.0) {
            return self.c(0.0);
        }
        let zero = Form::constant(0.0);
        let (lower, upper) = if amount >= 0.0 {
            (&self.lower, &self.upper)
        } else {
            (&self.upper, &self.lower)
        };
        Self::new(
            self.domain.clone(),
            lower.combine(&zero, amount, 0.0, &self.domain),
            upper.combine(&zero, amount, 0.0, &self.domain),
        )
    }
    fn floor(self) -> Self {
        let mut lower = self.lower.clone();
        lower.constant -= 1.0;
        lower.error += 64.0 * f64::EPSILON * (1.0 + lower.magnitude(&self.domain));
        let upper = self.upper.clone();
        if self.low.floor() == self.high.floor() {
            return self.c(self.high.floor());
        }
        let mut result = Self::new(self.domain.clone(), lower, upper);
        result.low = self.low.floor();
        result.high = self.high.floor();
        result
    }
    fn max(self, other: Self) -> Self {
        let difference = self.clone() - other.clone();
        if difference.high <= 0.0 {
            return other;
        }
        if difference.low >= 0.0 {
            return self;
        }
        let slope = difference.high / (difference.high - difference.low);
        let upper = (difference.clone() * slope + (-slope * difference.low)).upper;
        let lower = if difference.high + difference.low >= 0.0 {
            difference.lower.clone()
        } else {
            Form::constant(0.0)
        };
        let positive = Self::new(self.domain.clone(), lower, upper);
        other + positive
    }
    fn min(self, other: Self) -> Self {
        -((-self).max(-other))
    }
    fn clamp(self, low: f64, high: f64) -> Self {
        let a = self.c(low);
        let b = self.c(high);
        self.max(a).min(b)
    }
    fn select_ge(left: &Self, right: &Self, yes: Self, no: Self) -> Self {
        let diff = left.clone() - right.clone();
        if diff.low >= 0.0 {
            return yes;
        }
        if diff.high < 0.0 {
            return no;
        }
        // Discontinuous stat/boolean branches retain both possibilities.
        yes.clone()
            .interval(yes.low.min(no.low), yes.high.max(no.high))
    }
    fn positive_flag(self) -> Self {
        if self.low > 0.0 {
            self.c(1.0)
        } else if self.high <= 0.0 {
            self.c(0.0)
        } else {
            self.interval(0.0, 1.0)
        }
    }
    fn trunc(self) -> Self {
        Self::select_ge(
            &self,
            &self.c(0.0),
            self.clone().floor(),
            -(-self.clone()).floor(),
        )
    }
    fn float_trunc(self, error: f64) -> Self {
        let mut lower = self.lower.clone();
        let mut upper = self.upper.clone();
        lower.error += error;
        upper.error += error;
        let rounded = Self::new(self.domain.clone(), lower, upper);
        if rounded.low.trunc() == rounded.high.trunc() {
            return rounded.c(rounded.low.trunc());
        }
        if rounded.low >= 0.0 {
            return rounded.floor();
        }
        if rounded.high <= 0.0 {
            return -(-rounded).floor();
        }
        // trunc(x) lies between x-1 and x+1 across zero. Keeping those
        // affine forms retains package correlation through cancellation.
        let mut lower = rounded.lower.clone();
        let mut upper = rounded.upper.clone();
        lower.constant -= 1.0;
        upper.constant += 1.0;
        Self::new(rounded.domain.clone(), lower, upper)
    }
    fn soften_cdmg(self) -> Self {
        // Dropping the upper branch's floor gives this concave upper graph.
        // One unit below it bounds the original floored branch from below.
        let upper = self.clone().min((self + 300.0) / 2.0);
        let lower = upper.clone() - 1.0;
        Self::new(upper.domain.clone(), lower.lower, upper.upper)
    }
}
impl Add for Expr {
    type Output = Self;
    fn add(self, other: Self) -> Self {
        if self.low == 0.0 && self.high == 0.0 {
            return other;
        }
        if other.low == 0.0 && other.high == 0.0 {
            return self;
        }
        Self::new(
            self.domain.clone(),
            self.lower.combine(&other.lower, 1.0, 1.0, &self.domain),
            self.upper.combine(&other.upper, 1.0, 1.0, &self.domain),
        )
    }
}
impl Sub for Expr {
    type Output = Self;
    fn sub(self, other: Self) -> Self {
        self + (-other)
    }
}
impl Neg for Expr {
    type Output = Self;
    fn neg(self) -> Self {
        self.scale(-1.0)
    }
}
impl Add<f64> for Expr {
    type Output = Self;
    fn add(self, other: f64) -> Self {
        let c = self.c(other);
        self + c
    }
}
impl Sub<f64> for Expr {
    type Output = Self;
    fn sub(self, other: f64) -> Self {
        self + (-other)
    }
}
impl Mul<f64> for Expr {
    type Output = Self;
    fn mul(self, other: f64) -> Self {
        self.scale(other)
    }
}
impl Div<f64> for Expr {
    type Output = Self;
    fn div(self, other: f64) -> Self {
        self.scale(1.0 / other)
    }
}
impl Mul for Expr {
    type Output = Self;
    fn mul(self, other: Self) -> Self {
        if self.low == self.high {
            return other.scale(self.low);
        }
        if other.low == other.high {
            return self.scale(other.low);
        }
        // Two upper and two lower McCormick planes; choose the strongest supported
        // plane. Signs select the appropriate already-certified operand form.
        let u1 = self.clone() * other.low + other.clone() * self.high - self.high * other.low;
        let u2 = self.clone() * other.high + other.clone() * self.low - self.low * other.high;
        let l1 = self.clone() * other.low + other.clone() * self.low - self.low * other.low;
        let l2 = self.clone() * other.high + other.clone() * self.high - self.high * other.high;
        let upper = if u1.high <= u2.high {
            u1.upper
        } else {
            u2.upper
        };
        let lower = if l1.low >= l2.low { l1.lower } else { l2.lower };
        Self::new(self.domain.clone(), lower, upper)
    }
}

/// Globally valid root-domain planes are retained in every child subtree.
/// They never replace candidates or their exact evaluation options.
#[derive(Clone)]
pub struct RangeProductPlan {
    pub factors: [Form; 2],
    pub upper: [f64; 2],
    pub tail: f64,
}

#[derive(Clone)]
pub struct SupplyPlan {
    pub upper: [Form; METRICS],
    // Unsaturated MP retains the supply cost hidden by the goal's cap.
    pub resource_upper: [Form; 2],
    pub lower: [f64; METRICS],
    pub stages: [Form; 6], // raw power, CDMG, stability, element, skill, range
    pub legacy_safe: bool,
    pub range_product: Option<RangeProductPlan>,
    abs: [f64; STAT_COUNT],
}
impl SupplyPlan {
    pub fn prepare(base: &PreparedContext, groups: &[Vec<&NativeStats>]) -> Option<Self> {
        let points: Vec<Vec<_>> = groups
            .iter()
            .map(|g| {
                g.iter()
                    .map(|p| std::array::from_fn(|i| p.get(KEYS[i]).copied().unwrap_or(0.0)))
                    .collect()
            })
            .collect();
        let mut abs = [0.0_f64; STAT_COUNT];
        for group in &points {
            for point in group {
                for value in point {
                    if !value.is_finite() || value.abs() > 1e12 {
                        return None;
                    }
                }
            }
        }
        for i in 0..STAT_COUNT {
            abs[i] = points
                .iter()
                .map(|g| g.iter().map(|p| p[i].abs()).fold(0.0_f64, f64::max))
                .sum();
        }
        let domain = Arc::new(Domain {
            groups: points,
            abs,
        });
        let zero = Expr::new(domain.clone(), Form::constant(0.0), Form::constant(0.0));
        let stat = |key: &str| {
            let i = KEYS.iter().position(|k| *k == key).unwrap();
            if domain.abs[i] == 0.0 {
                return zero.c(0.0);
            }
            let mut f = Form::constant(0.0);
            f.coefficients[i] = 1.0;
            f.error = 64.0 * f64::EPSILON * (1.0 + domain.abs[i]);
            Expr::new(domain.clone(), f.clone(), f)
        };
        let c = |key: &str| zero.c(number(base, key));
        let pair = |prefix: &str, percent: &str, flat: &str| {
            ((c(&format!("{prefix}Base")) * (c(&format!("{prefix}P")) + stat(percent) + 100.0)
                / 100.0)
                + c(&format!("{prefix}F"))
                + stat(flat))
            .floor()
        };
        let str_ = pair("str", "STRP", "STR");
        let dex = pair("dex", "DEXP", "DEX");
        let agi = pair("agi", "AGIP", "AGI");
        let int_ = pair("int", "INTP", "INT");
        let vit = pair("vit", "VITP", "VIT");
        let level = number(base, "level");
        let hpbase = ((vit.clone() * 100.0 + 2241.0) * level / 300.0 + 93.0).floor();
        let legacy_hp = hpbase.low >= 0.0;
        let hp =
            (hpbase * (c("maxHpP") + stat("MAXHPP") + 100.0) / 100.0 + c("maxHpF") + stat("MAXHP"))
                .floor();
        let hp = hp.clamp(0.0, 99999.0);
        let mp = (int_.clone() / 10.0 + base.invariant(Invariant::MpFlat) + stat("MAXMP"))
            .floor()
            .max(zero.c(0.0));
        let mp_goal = mp
            .clone()
            .min(zero.c(if number(base, "godspeedWieldLevel") > 0.0 {
                2300.0
            } else {
                2000.0
            }));
        let mut ampr =
            (mp.clone().min(zero.c(2000.0)) / 100.0 + 10.0).floor() + c("amprF") + stat("AMPR");
        let profile = base
            .context_get("normalAttackAmprProfile")
            .unwrap_or(&serde_json::Value::Null);
        let modifier = |value: Expr, m: &serde_json::Value| {
            let mut v = value.floor();
            if number(m, "percent") != 0.0 {
                v = (v * (100.0 + number(m, "percent")) / 100.0).floor();
            }
            let rate = m
                .get("multiplier")
                .and_then(serde_json::Value::as_f64)
                .filter(|v| v.is_finite())
                .unwrap_or(1.0);
            if rate != 1.0 {
                v = (v * rate).floor();
            }
            (v + number(m, "flat")).floor()
        };
        for m in array(profile, "passive") {
            ampr = modifier(ampr, m);
        }
        if !array(profile, "activeCandidates").is_empty() {
            ampr = array(profile, "activeCandidates")
                .iter()
                .map(|m| modifier(ampr.clone(), m))
                .reduce(Expr::max)
                .unwrap();
        }
        let normal = ((c("critP") + stat("CRITP") + 100.0) * base.invariant(Invariant::BaseCrit)
            / 100.0)
            .floor()
            + c("critF")
            + stat("CRIT");
        let crit_goal = (normal.clone() - c("bossCritResist"))
            .trunc()
            .clamp(0.0, 100.0);
        let main = text(base, "mainType");
        let sub = text(base, "subType");
        let dual = main == "한손검" && sub == "한손검(듀얼소드)";
        let (stat_atk, stat_matk, aspd_stat, stab_stat, matk_ratio) = match main {
            "한손검" if dual => (
                str_.clone() + agi.clone() + dex.clone() * 2.0,
                int_.clone() * 3.0 + dex.clone(),
                agi.clone() * 4.2 + str_.clone() * 0.2,
                (str_.clone() + dex.clone() * 3.0) / 40.0,
                0.0,
            ),
            "한손검" => (
                str_.clone() * 2.0 + dex.clone() * 2.0,
                int_.clone() * 3.0 + dex.clone(),
                agi.clone() * 4.2 + str_.clone() * 0.2,
                (str_.clone() + dex.clone() * 3.0) / 40.0,
                0.0,
            ),
            "양손검" => (
                str_.clone() * 3.0 + dex.clone(),
                int_.clone() * 3.0 + dex.clone(),
                agi.clone() * 2.1 + str_.clone() * 0.2,
                dex.clone() / 10.0,
                0.0,
            ),
            "활" => (
                str_.clone() + dex.clone() * 3.0,
                int_.clone() * 3.0 + dex.clone(),
                agi.clone() * 3.1 + dex.clone() * 0.2,
                (str_.clone() + dex.clone() * 3.0) / 40.0,
                0.0,
            ),
            "자동활" => (
                dex.clone() * 4.0,
                int_.clone() * 3.0 + dex.clone(),
                agi.clone() * 2.2 + dex.clone() * 0.2,
                str_.clone() / 20.0,
                0.0,
            ),
            "지팡이" => (
                str_.clone() * 3.0 + int_.clone(),
                int_.clone() * 4.0 + dex.clone(),
                agi.clone() * 1.8 + int_.clone() * 0.2,
                str_.clone() / 20.0,
                1.0,
            ),
            "마도구" => (
                int_.clone() * 2.0 + agi.clone() * 2.0,
                int_.clone() * 4.0 + dex.clone(),
                agi.clone() * 4.0 + int_.clone() * 0.2,
                dex.clone() / 10.0,
                1.0,
            ),
            "권갑" => (
                agi.clone() * 2.0 + dex.clone() * 0.5,
                int_.clone() * 4.0 + dex.clone(),
                agi.clone() * 4.6 + (dex.clone() + str_.clone()) / 10.0,
                dex.clone() / 40.0,
                0.5,
            ),
            "선풍창" => (
                (str_.clone() * 2.5).floor() + (agi.clone() * 1.5).floor(),
                int_.clone() * 2.0 + agi.clone() + dex.clone(),
                agi.clone() * 3.5 + str_.clone() * 0.2,
                (str_.clone() + dex.clone()) / 40.0,
                0.0,
            ),
            "발도검" => (
                (dex.clone() * 2.5).floor() + (str_.clone() * 1.5).floor(),
                int_.clone() * 1.5 + dex.clone(),
                agi.clone() * 3.9 + dex.clone() * 0.3,
                (str_.clone() * 3.0 + dex.clone()) / 40.0,
                0.0,
            ),
            _ => (
                str_.clone(),
                int_.clone() * 3.0 + dex.clone(),
                agi.clone() * 9.6,
                zero.c(0.0),
                0.0,
            ),
        };
        let aspd_stat = if sub == "한손검(듀얼소드)" {
            agi.clone() * 4.2 + str_.clone() * 0.2
        } else {
            aspd_stat
        };
        let armor = match text(base, "armorType") {
            "경량옷" => 50.0,
            "중량옷" => -50.0,
            _ => 0.0,
        };
        let aspd_base = aspd_stat.floor() + super::base_aspd(main) + level;
        let legacy_aspd = aspd_base.low >= 0.0;
        let aspd = ((aspd_base * (c("aspdP") + stat("ASPD_P") + armor + 100.0) / 100.0).floor()
            + c("aspdF")
            + stat("ASPD"))
        .trunc();
        let motion = ((aspd.clone() - 1000.0) / 180.0).floor().min(zero.c(50.0))
            + c("motionSpeed")
            + stat("MOTIONSPEED");
        let motion = motion.clamp(0.0, 50.0) * 180.0 + 1000.0;
        let aspd_goal = Expr::select_ge(&aspd, &zero.c(1000.0), motion, aspd.clone());
        let cspd = ((zero.c(level) + (agi.clone() * 1.16).floor() + (dex.clone() * 2.94).floor())
            * (c("cspdP") + stat("CSPD_P") + 100.0)
            / 100.0)
            .floor()
            + c("cspdF")
            + stat("CSPD");
        let cast = (cspd.clone() / 20.0)
            .min((cspd.clone() - 1000.0) / 180.0 + 50.0)
            .min(zero.c(100.0))
            .floor()
            + c("castRed")
            + stat("CAST_RED");
        let cast = cast.min(zero.c(100.0));
        let mut atk_p = c("atkP") + stat("ATKP");
        let mut atk_f = c("atkF") + stat("ATK");
        let mut effective_weapon = c("wpnAtk") + c("baseWpnAtkF");
        let mut uns_p = c("unsheatheP") + stat("UNSHEATHEP");
        let mut uns_f = c("unsheatheF") + stat("UNSHEATHE");
        for conversion in array(base, "activeBuildConversions")
            .iter()
            .filter(|m| text(*m, "conversion") == "unsheatheToAtk")
        {
            let p = (uns_p.clone() * number(conversion, "value")).floor();
            let f = (uns_f.clone() * number(conversion, "value")).floor();
            atk_p = atk_p + p.clone();
            effective_weapon = effective_weapon + p;
            atk_f = atk_f + f;
            uns_p = zero.c(0.0);
            uns_f = zero.c(0.0);
        }
        let watkp = c("watkP") + stat("WATKP");
        let watk = c("watkF") + stat("WATK");
        let legacy_weapon = effective_weapon.low >= 0.0;
        let main_weapon = effective_weapon.clone()
            + (effective_weapon.clone() * watkp.clone() / 100.0).floor()
            + watk.clone();
        let mut weapon = main_weapon
            + (effective_weapon * base.invariant(Invariant::MainRefineSquared) / 100.0).floor()
            + c("wpnRefine");
        if sub == "화살" && (main == "활" || main == "자동활") {
            weapon = weapon + number(base, "subAtk").floor();
        }
        let mut fixed_reflection = NativeStats::new();
        for group in groups {
            if let Some(values) = group.first() {
                for key in KEYS
                    .iter()
                    .filter(|key| key.starts_with("ATK_UP_") || key.starts_with("MATK_UP_"))
                {
                    let total = fixed_reflection.get(key).copied().unwrap_or(0.0)
                        + values.get(key).copied().unwrap_or(0.0);
                    fixed_reflection.insert((*key).into(), total);
                }
            }
        }
        let up = |magic: bool| -> Option<Expr> {
            let prefix = if magic { "MATK" } else { "ATK" };
            let fields = ["STR", "INT", "VIT", "AGI", "DEX"];
            let fixed = fields.iter().all(|name| {
                let attribute = number(base, &format!("{}Base", name.to_lowercase()));
                let index = KEYS
                    .iter()
                    .position(|key| *key == format!("{prefix}_UP_{name}"))
                    .unwrap();
                attribute == 0.0
                    || domain
                        .groups
                        .iter()
                        .all(|group| group.iter().all(|point| point[index] == group[0][index]))
            });
            if fixed {
                return Some(zero.c(super::candidate_stat_up(base, &fixed_reflection, magic)));
            }
            let mut sum = zero.c(0.0);
            let mut magnitude = 0.0;
            let limit = f32::MAX as f64 / 16.0;
            for name in fields {
                let attribute = number(base, &format!("{}Base", name.to_lowercase()));
                let key = format!("{prefix}_UP_{name}");
                let rate = number(base, &format!("{}Up{name}", prefix.to_lowercase()));
                let index = KEYS.iter().position(|candidate| *candidate == key).unwrap();
                let rate_abs = rate.abs() + domain.abs[index];
                let term_bound = attribute.abs() * (rate_abs + 0.1) / 100.0;
                if !term_bound.is_finite()
                    || attribute.abs() > limit
                    || rate_abs * 10.0 > limit
                    || term_bound > limit
                {
                    return None;
                }
                sum = sum + (stat(&key) + rate) * (attribute / 100.0);
                magnitude += term_bound;
            }
            // NormalizeValue snaps raw tenths within 2*EPS32*max(1,|raw|).
            // Cast/divide/attribute-cast/product each cost at most EPS32/2;
            // five ordered additions cost at most gamma(5) times the sum of
            // absolute terms. 128*EPS32 is an outward bound for all these
            // errors, including cancellation and subnormals. The +.1 above
            // covers the snapping rule's absolute tolerance near raw zero.
            // The /16 guards keep all f32 intermediates below overflow.
            let error = 128.0 * f32::EPSILON as f64 * magnitude + f32::MIN_POSITIVE as f64;
            Some(sum.float_trunc(error))
        };
        let atk_up = up(false)?;
        let matk_up = up(true)?;
        let constant_reflection = atk_up.low == atk_up.high && matk_up.low == matk_up.high;
        if sub == "마도구" {
            atk_p = atk_p - 15.0;
        }
        let atk_base = weapon.clone() + stat_atk + level + atk_up;
        let matk_base = (weapon.clone() * matk_ratio).floor() + stat_matk + level + matk_up;
        let legacy_power = atk_base.low >= 0.0 && matk_base.low >= 0.0 && atk_p.low >= -100.0;
        let mut atk = (atk_base * (atk_p.clone() + 100.0) / 100.0).floor() + atk_f.clone();
        let mut matk = (matk_base * (c("matkP") + stat("MATKP") + 100.0) / 100.0).floor()
            + c("matkF")
            + stat("MATK");
        let conv = number(base, "conversionLevel");
        if conv > 0.0 && ["한손검", "양손검", "자동활", "권갑"].contains(&main) {
            let add = (weapon * conv * conv / 100.0).floor();
            matk = matk
                + if main == "권갑" {
                    (add / 2.0).floor()
                } else {
                    add + (int_.clone() * conv / 10.0).floor()
                };
        }
        let mut legacy_dual = true;
        if dual {
            let sub_weapon = c("subAtk")
                + (watkp * number(base, "subAtk") / 100.0).floor()
                + floor_ratio(
                    number(base, "subAtk"),
                    base.invariant(Invariant::SubRefineSquared),
                    200.0,
                    0.0,
                )
                + c("subRefine")
                + watk;
            let sub_atk = ((sub_weapon + (str_.clone() + agi.clone() * 3.0).floor() + level)
                * (atk_p + 100.0)
                / 100.0)
                .floor()
                + atk_f;
            let sub_stab = (zero.c((number(base, "subStab") * 0.5).floor())
                + (str_.clone() * 0.06).floor()
                + (agi.clone() * 0.04).floor()
                + c("stability")
                + stat("STABILITY"))
            .min(zero.c(100.0));
            legacy_dual = sub_atk.low >= 0.0 && sub_stab.low >= 0.0;
            atk = atk + (sub_atk * sub_stab / 100.0).floor();
        }
        let base_cdmg = (str_.clone() / 5.0)
            .floor()
            .max(((str_.clone() + agi.clone()) / 10.0).floor())
            + 150.0;
        let legacy_cdmg_base = base_cdmg.low >= 0.0;
        let cdmg = (base_cdmg * (c("cdmgP") + stat("CDMGP") + 100.0) / 100.0).floor()
            + c("cdmgF")
            + stat("CDMG");
        let mut cdmg = cdmg.soften_cdmg();
        if number(base, "minimumCriticalDamage") != 0.0 {
            cdmg = cdmg.max(c("minimumCriticalDamage"));
        }
        let mut crit = ((normal + number(base, "criticalChanceBonus"))
            * base
                .context_get("criticalChanceMultiplier")
                .and_then(serde_json::Value::as_f64)
                .unwrap_or(1.0))
        .floor();
        if let Some(fixed) = base
            .context_get("fixedCriticalChance")
            .and_then(serde_json::Value::as_f64)
            .filter(|f| f.is_finite())
        {
            crit = zero.c(fixed);
        }
        let mut stab = (c("wpnStab")
            + c("stability")
            + stat("STABILITY")
            + c("stabilityBonus")
            + stab_stat.floor())
        .min(zero.c(100.0));
        if sub == "화살" && (main == "활" || main == "자동활") {
            stab = (stab + c("subStab")).min(zero.c(100.0));
        }
        let awakening = if flag(base, "elementAwakening") {
            zero.c(1.0)
        } else {
            stat("ELEM_AWAKENING").positive_flag()
        };
        let mut weapon_element = number(base, "weaponElement") as i32;
        if ["활", "자동활"].contains(&main)
            && sub == "화살"
            && number(base, "subWeaponElement") != 0.0
        {
            weapon_element = number(base, "subWeaponElement") as i32;
        }
        let attack_element = text(base, "attackElement");
        let inherits = ["", "none", "weapon"].contains(&attack_element);
        let effective_element = if inherits {
            weapon_element
        } else {
            match attack_element {
                "fire" => 1,
                "water" => 2,
                "wind" => 3,
                "earth" => 4,
                "light" => 5,
                "dark" => 6,
                "neutral" | "normal" => 7,
                "mana" => 8,
                "targetAdvantage" => match number(base, "targetElement") {
                    1.0 => 2,
                    2.0 => 3,
                    3.0 => 4,
                    4.0 => 1,
                    5.0 => 6,
                    6.0 => 5,
                    _ => 0,
                },
                _ => 0,
            }
        };
        let weapon_weak = match effective_element {
            1 => number(base, "targetElement") == 4.0,
            2 => number(base, "targetElement") == 1.0,
            3 => number(base, "targetElement") == 2.0,
            4 => number(base, "targetElement") == 3.0,
            5 => number(base, "targetElement") == 6.0,
            6 => number(base, "targetElement") == 5.0,
            _ => false,
        };
        let weapon_magic = text(base, "atkType") == "MAG"
            && ((["지팡이", "마도구"].contains(&main)
                && effective_element != 0
                && effective_element != 7)
                || weapon_weak
                || attack_element == "weakness");
        let magic_element = if flag(base, "magicElement") || weapon_magic {
            zero.c(1.0)
        } else {
            stat("MAGIC_ELEMENT").positive_flag()
        };
        let weak = if text(base, "attackElement") == "weakness" || weapon_weak {
            zero.c(1.0)
        } else {
            awakening.clone()
        };
        let element_keys = [
            "FIRE_DMG",
            "WATER_DMG",
            "WIND_DMG",
            "EARTH_DMG",
            "LIGHT_DMG",
            "DARK_DMG",
            "NEUTRAL_DMG",
        ];
        let element_fields = [
            "fireDmg",
            "waterDmg",
            "windDmg",
            "earthDmg",
            "lightDmg",
            "darkDmg",
            "neutralDmg",
        ];
        let target_element = number(base, "targetElement") as usize;
        let target_bonus = if (1..=7).contains(&target_element) {
            c(element_fields[target_element - 1]) + stat(element_keys[target_element - 1])
        } else {
            zero.c(0.0)
        };
        let elem = c("elemP")
            + stat("ELEM_P")
            + target_bonus
            + weak.clone() * 25.0
            + awakening.max(magic_element) * (number(base, "intBase") / 10.0).floor();
        let magic = text(base, "atkType") == "MAG";
        if magic {
            let spell = 2.5 * number(base, "spellBurstLevel");
            let weaken = if flag(base, "targetWeakened") {
                if main == "지팡이" || main == "마도구" {
                    zero.c(50.0)
                } else {
                    weak * 50.0
                }
            } else {
                zero.c(0.0)
            };
            let mut reflect = weaken + spell;
            let mut cd_reflect = zero.c(50.0 + spell);
            if flag(base, "dualBringerActive") {
                let bonus = 2.5 * number(base, "dualBringerLevel");
                if flag(base, "targetWeakened") && sub == "마도구" {
                    reflect = reflect + Expr::select_ge(&str_, &int_, zero.c(bonus), zero.c(0.0));
                }
                cd_reflect = cd_reflect + Expr::select_ge(&str_, &int_, zero.c(0.0), zero.c(bonus));
            }
            crit = (crit * reflect / 100.0).floor();
            cdmg = ((cdmg - 100.0) * cd_reflect / 100.0).floor() + 100.0;
            stab = (stab / 2.0 + 50.0).floor().min(zero.c(100.0));
        }
        if flag(base, "chkGuaranteedCrit") {
            crit = zero.c(1000.0);
        }
        if flag(base, "noCritical") {
            crit = zero.c(0.0);
        }
        let legacy_cdmg = cdmg.low >= 100.0 && stab.low >= -100.0;
        let defense = number(base, if magic { "bossMdef" } else { "bossDef" });
        let pierce = if magic {
            c("magPierce") + stat("MAG_PIERCE") + c("magicPierceSkillBonus")
        } else {
            c("physPierce") + stat("PHYS_PIERCE") + c("physicalPierceSkillBonus")
        };
        let mut def = ((-pierce + 100.0) * defense / 100.0).floor();
        if flag(base, if magic { "ignoreMdef" } else { "ignoreDefense" }) {
            def = zero.c(0.0);
        } else if magic && flag(base, "halfMdefIgnored") {
            def = (def / 2.0).floor();
        }
        def = def.max(zero.c(0.0));
        let layers = base
            .context_get("damageMultiplierLayers")
            .unwrap_or(&serde_json::Value::Null);
        let layer = |key: &str, default: f64| {
            layers
                .get(key)
                .and_then(serde_json::Value::as_f64)
                .filter(|v| v.is_finite())
                .unwrap_or(default)
        };
        let mut mult = zero.c(layer("skill", number(base, "skillMult")));
        let mut constant = c("skillConst");
        for term in array(base, "skillStats") {
            let value = match text(term, "stat") {
                "totalSTR" => str_.clone(),
                "totalDEX" => dex.clone(),
                "totalAGI" => agi.clone(),
                "totalINT" => int_.clone(),
                "totalVIT" => vit.clone(),
                "STR" => c("strBase"),
                "DEX" => c("dexBase"),
                "AGI" => c("agiBase"),
                "INT" => c("intBase"),
                "VIT" => c("vitBase"),
                _ => zero.c(0.0),
            } * number(term, "ratio");
            match text(term, "target") {
                "mult" => mult = mult + value,
                "const" => constant = constant + value,
                _ => {}
            }
        }
        let power = match text(base, "attackPowerMode") {
            "sum" => atk + matk,
            "higher" => atk.max(matk),
            "atk" => atk,
            "wizardBlend" => atk * 0.25 + matk * 0.75,
            _ if magic => matk,
            _ => atk,
        };
        let mut raw = ((power + level - number(base, "bossLevel"))
            * base.invariant(if magic {
                Invariant::MagicResistance
            } else {
                Invariant::PhysResistance
            }))
        .floor();
        if flag(base, "chkIsUnsheathe") {
            raw = raw + uns_f;
        }
        raw = (raw + constant - def).max(zero.c(1.0));
        let srw = c("srw") + stat("SRW");
        let lrw = c("lrw") + stat("LRW");
        let range = if flag(base, "useHigherRangeDamage") {
            srw.max(lrw)
        } else if text(base, "rangeType") == "SHORT" {
            srw
        } else {
            lrw
        };
        let chance = (crit - c("bossCritResist")).clamp(0.0, 100.0);
        let legacy_mult = mult.low >= 0.0;
        let stages = [
            raw.upper.clone(),
            cdmg.upper.clone(),
            stab.upper.clone(),
            elem.upper.clone(),
            mult.upper.clone(),
            range.upper.clone(),
        ];
        let mut damage = (raw * (chance * (cdmg - 100.0) + 10000.0) / 10000.0).floor();
        damage = (damage * (elem + 100.0) / 100.0).floor();
        damage = (damage * mult).floor();
        if flag(base, "chkIsUnsheathe") {
            damage = (damage * (uns_p + 100.0) / 100.0).floor();
        }
        damage = (damage * (stab + 100.0) / 200.0).floor();
        damage = (damage * layer("passive", 1.0)).floor();
        let range_factor = (range.clone() + 100.0) / 100.0;
        let tail = layer("active", 1.0) * (number(base, "damageP") + 100.0) / 100.0
            * layer("combo", 1.0)
            * base.invariant(Invariant::Proc);
        // Dropping the remaining floors is safe only for nonnegative factors;
        // a varying damage% tail needs a separate three-factor bound.
        let range_product = if damage.low >= 0.0
            && range_factor.low >= 0.0
            && tail >= 0.0
            && tail.is_finite()
            && domain.abs[KEYS.iter().position(|k| *k == "DAMAGE_P").unwrap()] == 0.0
        {
            Some(RangeProductPlan {
                factors: [damage.upper.clone(), range_factor.upper.clone()],
                upper: [damage.high, range_factor.high],
                tail,
            })
        } else {
            None
        };
        damage = (damage * (range + 100.0) / 100.0).floor();
        damage = (damage * layer("active", 1.0)).floor();
        damage = (damage * (c("damageP") + stat("DAMAGE_P") + 100.0) / 100.0).floor();
        damage = (damage * layer("combo", 1.0)).floor();
        damage = damage * base.invariant(Invariant::Proc);
        let resource_upper = [mp.upper.clone(), ampr.upper.clone()];
        let values = [damage, hp, mp_goal, ampr, crit_goal, aspd_goal, cspd, cast];
        let lower = std::array::from_fn(|i| values[i].low);
        let upper = values.map(|v| v.upper);
        if upper
            .iter()
            .chain(stages.iter())
            .chain(resource_upper.iter())
            .any(|f| {
                !f.constant.is_finite()
                    || !f.error.is_finite()
                    || f.coefficients.iter().any(|c| !c.is_finite())
            })
        {
            return None;
        }
        // Signed percentages, variable reflection and new boolean options
        // can break monotonicity of the old coordinate envelope.
        let percentages = [
            ("STRP", "strP"),
            ("DEXP", "dexP"),
            ("AGIP", "agiP"),
            ("INTP", "intP"),
            ("VITP", "vitP"),
            ("ATKP", "atkP"),
            ("MATKP", "matkP"),
            ("WATKP", "watkP"),
            ("CDMGP", "cdmgP"),
            ("CRITP", "critP"),
            ("ASPD_P", "aspdP"),
            ("MAXHPP", "maxHpP"),
            ("UNSHEATHEP", "unsheatheP"),
            ("DAMAGE_P", "damageP"),
            ("SRW", "srw"),
            ("LRW", "lrw"),
            ("ELEM_P", "elemP"),
        ];
        let legacy_safe = legacy_cdmg
            && legacy_cdmg_base
            && legacy_weapon
            && legacy_power
            && legacy_dual
            && legacy_hp
            && legacy_aspd
            && legacy_mult
            && !flag(base, "dualBringerActive")
            && domain.abs[50] == 0.0
            && domain.abs[51] == 0.0
            && constant_reflection
            && percentages.iter().all(|(key, base_key)| {
                let i = KEYS.iter().position(|k| k == key).unwrap();
                let minimum: f64 = domain
                    .groups
                    .iter()
                    .map(|g| {
                        // With a nonnegative HP base, negative HP rates yield
                        // nonpositive HP; the positive maximum still bounds them.
                        if *key == "MAXHPP" {
                            g.iter().map(|p| p[i]).fold(f64::NEG_INFINITY, f64::max)
                        } else {
                            g.iter().map(|p| p[i]).fold(f64::INFINITY, f64::min)
                        }
                    })
                    .sum();
                let correction = if *key == "ASPD_P" {
                    armor
                } else if *key == "ATKP" && sub == "마도구" {
                    -15.0
                } else {
                    0.0
                };
                number(base, base_key) + minimum + correction > -99.0
            })
            && [
                "strBase",
                "dexBase",
                "agiBase",
                "intBase",
                "vitBase",
                "wpnAtk",
                "subAtk",
                "level",
                "bossDef",
                "bossMdef",
                "spellBurstLevel",
            ]
            .iter()
            .all(|key| number(base, key) >= 0.0)
            && base.invariant(Invariant::PhysResistance) >= 0.0
            && base.invariant(Invariant::MagicResistance) >= 0.0
            && base.invariant(Invariant::Proc) >= 0.0
            && base.invariant(Invariant::BaseCrit) >= 0.0
            && base
                .context_get("criticalChanceMultiplier")
                .and_then(serde_json::Value::as_f64)
                .unwrap_or(1.0)
                >= 0.0
            && ["skill", "passive", "active", "combo"].iter().all(|key| {
                layer(
                    key,
                    if *key == "skill" {
                        number(base, "skillMult")
                    } else {
                        1.0
                    },
                ) >= 0.0
            })
            && array(base, "activeBuildConversions")
                .iter()
                .all(|m| number(m, "value") >= 0.0)
            && array(base, "skillStats")
                .iter()
                .all(|term| number(term, "ratio") >= 0.0)
            && array(profile, "passive")
                .iter()
                .chain(array(profile, "activeCandidates").iter())
                .all(|m| {
                    number(m, "percent") >= -100.0
                        && m.get("multiplier")
                            .and_then(serde_json::Value::as_f64)
                            .unwrap_or(1.0)
                            >= 0.0
                });
        Some(Self {
            range_product,
            resource_upper,
            upper,
            lower,
            stages,
            legacy_safe,
            abs: domain.abs,
        })
    }
    pub fn weighted(&self, metric: usize, weight: f64) -> Form {
        let domain = Domain {
            groups: Vec::new(),
            abs: self.abs,
        };
        self.upper[0].combine(&self.upper[metric], 1.0, weight, &domain)
    }
    pub fn product_direction(&self, weight: f64) -> Option<Form> {
        let product = self.range_product.as_ref()?;
        let form = product.factors[0].combine(
            &product.factors[1],
            1.0,
            weight,
            &Domain {
                groups: Vec::new(),
                abs: self.abs,
            },
        );
        (form.constant.is_finite()
            && form.error.is_finite()
            && form.coefficients.iter().all(|v| v.is_finite()))
        .then_some(form)
    }
}

#[cfg(test)]
mod float_reflection_tests {
    use super::*;
    use serde_json::json;

    #[test]
    fn signed_float_reflection_planes_cover_native_rounding_and_cancellation() {
        for attribute in [
            -16777217.0,
            -2999.0,
            -1.0,
            0.0,
            1.0,
            3.0,
            999.0,
            2999.0,
            10000.0,
            16777217.0,
        ] {
            for raw in [-32768_i32, -13, -7, -1, 1, 7, 13, 32767] {
                for magic in [false, true] {
                    let base = PreparedContext::from(json!({
                        "mainType":"맨손","atkType":if magic {"MAG"}else{"PHYS"},
                        "rangeType":"SHORT","strBase":attribute,"intBase":attribute+3.0,
                        "level":0,"wpnStab":100,"skillMult":1
                    }));
                    let prefix = if magic { "MATK" } else { "ATK" };
                    let groups: Vec<Vec<NativeStats>> = (0..3)
                        .map(|group| {
                            (0..2)
                                .map(|choice| {
                                    ["STR", "INT", "VIT", "AGI", "DEX"]
                                        .into_iter()
                                        .enumerate()
                                        .map(|(index, name)| {
                                            let sign = if (group + choice + index) % 2 == 0 {
                                                1.0
                                            } else {
                                                -1.0
                                            };
                                            let rate = if group == 0 {
                                                (raw as f32 * 0.1_f32) as f64 * sign
                                            } else if group == 1 {
                                                -(raw as f64 / 10.0) * sign
                                            } else {
                                                sign * if choice == 0 {
                                                    1.23456789
                                                } else {
                                                    0.10000000001
                                                }
                                            };
                                            (format!("{prefix}_UP_{name}"), rate)
                                        })
                                        .collect()
                                })
                                .collect()
                        })
                        .collect();
                    let borrowed: Vec<Vec<_>> =
                        groups.iter().map(|group| group.iter().collect()).collect();
                    let plan = SupplyPlan::prepare(&base, &borrowed)
                        .expect("Finite variable rates retain an affine bound");
                    for selection in 0..8 {
                        let mut stats = NativeStats::new();
                        let mut upper = plan.stages[0].constant + plan.stages[0].error;
                        for (group, packages) in groups.iter().enumerate() {
                            let candidate = &packages[(selection >> group) & 1];
                            stats.add_assign(candidate);
                            upper += plan.stages[0].package(candidate);
                        }
                        let reflection = super::super::candidate_stat_up(&base, &stats, magic);
                        let raw_power = ((if magic {
                            3.0 * (attribute + 3.0)
                        } else {
                            attribute
                        }) + reflection)
                            .floor()
                            .max(1.0);
                        assert!(upper>=raw_power-1e-6,"attribute={attribute} raw={raw} magic={magic} choice={selection}: {upper} < {raw_power}");
                    }
                }
            }
        }
    }
}
