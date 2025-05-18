#include "math/rootfinding.hpp"

namespace math {

const std::pair<Option<f64>, Option<f64>> quadratic_roots(
    const f64 a, const f64 b, const f64 c
) {
    if (a == 0.0) {
        if (b == 0.0)
            // No roots case (I).
            return std::make_pair(std::nullopt, std::nullopt);
        else
            // One root case (I).
            return std::make_pair(-c / b, std::nullopt);
    }

    // Discriminant.
    const f64 d = b * b - 4.0 * a * c;

    if (d < 0.0) {
        // No roots case (II).
        return std::make_pair(std::nullopt, std::nullopt);
    } else {
        const f64 q = -(b + math::signum_ztp(b) * std::sqrt(d)) / 2.0;
        if (q != 0.0)
            // Two roots case.
            return std::make_pair(q / a, c / q);
        else
            // One root case (II)
            return std::make_pair(q / a, std::nullopt);
    }
}

}
