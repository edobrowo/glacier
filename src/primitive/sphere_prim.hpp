#pragma once

#include "primitive.hpp"
#include "util/common.hpp"

/// @brief Implicit sphere primitive.
class SpherePrim : public Primitive {
public:
    SpherePrim(const Point3D& center, const f64 radius);
    ~SpherePrim() override = default;

    /// @brief Computes the surface intersection with an implicit sphere
    /// centered at the origin with unit radius.
    virtual Option<Intersect> intersect(const Ray& ray, const Interval& bounds)
        const override;

private:
    Point3D mCenter;
    f64 mRadius;
};
