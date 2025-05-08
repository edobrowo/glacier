#pragma once

#include <span>

#include "point.hpp"
#include "util/common.hpp"

namespace math {

/// @brief Linear interpolation.
template <std::floating_point T, typename P>
constexpr inline P lerp(T t, P a, P b) {
    return t * a + (T(1) - t) * b;
}

/// @brief Linear interpolation Point specialization using blend.
template <std::floating_point T, u32 dim>
constexpr inline Point<T, dim> lerp(T t, Point<T, dim> a, Point<T, dim> b) {
    return blend(t, a, b);
}

/// @brief Cubic interpolation.
template <std::floating_point T, typename P>
constexpr inline P cerp(T t, P a, P b, P c, P d) {
    const T t2 = t * t;
    const T t3 = t2 * t;

    // clang-format off
    return (       - T(0.5) * t +          t2 - T(0.5) * t3) * a +
           (T(1.0)              - T(2.5) * t2 + T(1.5) * t3) * b +
           (         T(0.5) * t + T(2.0) * t2 - T(1.5) * t3) * c +
           (                    - T(0.5) * t2 + T(0.5) * t3) * d;
    // clang-format on
}

/// @brief Blossom of the cubic Bezier.
template <std::floating_point T, typename P>
P blossom_cubic_bezier(const std::span<P> p, T t1, T t2, T t3) {
    assertm(p.size() == 4, "p must have 4 control points");

    const P a1 = lerp(t1, p[0], p[1]);
    const P a2 = lerp(t1, p[1], p[2]);
    const P a3 = lerp(t1, p[2], p[3]);

    const P b1 = lerp(t2, a1, a2);
    const P b2 = lerp(t2, a2, a3);

    const P c1 = lerp(t3, b1, b2);

    return c1;
}

/// @brief Evaluates a cubic Bezier.
template <std::floating_point T, typename P>
P cubic_bezier(std::span<const P> p, T t) {
    assertm(p.size() == 4, "p must have 4 control points");

    return blossom_cubic_bezier(p, t, t, t);
}

}
