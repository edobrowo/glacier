#include "interval.hpp"

const Interval Interval::empty =
    Interval(math::infinity<f64>(), -math::infinity<f64>());
const Interval Interval::universe =
    Interval(-math::infinity<f64>(), math::infinity<f64>());
const Interval Interval::unit = Interval(0.0, 1.0);

Interval::Interval(const f64 min, const f64 max) : min(min), max(max) {
}

Interval::Interval(const Interval& other) : min(other.min), max(other.max) {
}

Interval& Interval::operator=(const Interval& other) {
    min = other.min;
    max = other.max;

    return *this;
}

bool Interval::contains(const f64 a) const {
    return min <= a && a <= max;
}

bool Interval::surrounds(const f64 a) const {
    return min < a && a < max;
}
