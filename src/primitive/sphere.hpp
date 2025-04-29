#pragma once

#include "primitive.hpp"
#include "util/common.hpp"

/// @brief Implicit sphere primitive.
class Sphere : public Primitive {
public:
    Sphere();
    virtual ~Sphere();

    /// @brief Computes the surface intersection with a sphere centered at the
    /// origin with unit radius.
    virtual Option<Intersect> intersect(const Ray& ray,
                                        const Interval& bounds) const override;
};
