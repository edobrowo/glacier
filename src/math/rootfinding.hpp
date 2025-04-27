#pragma once

#include "numeric.hpp"
#include "util/common.hpp"

namespace math {

/// @brief Solves the quadratic ax^2 + bx + c.
const std::pair<Option<f64>, Option<f64>> quadratic_roots(const f64 a,
                                                          const f64 b,
                                                          const f64 c);

}
