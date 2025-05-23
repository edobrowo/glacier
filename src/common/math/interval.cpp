#include "math/interval.hpp"

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

f64 Interval::size() const {
    return max - min;
}

bool Interval::contains(const f64 a) const {
    return min <= a && a <= max;
}

bool Interval::surrounds(const f64 a) const {
    return min < a && a < max;
}

Interval Interval::expand(const f64 epsilon) const {
    const f64 padding = epsilon / 2.0;
    return Interval(min - padding, max + padding);
}

Interval Interval::enclosure(const Interval& other) const {
    return Interval(std::min(min, other.min), std::max(max, other.max));
}

Interval Interval::intersection(const Interval& other) const {
    return Interval(std::max(min, other.min), std::min(max, other.max));
}
