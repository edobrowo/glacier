#pragma once

#include "common/prelude.hpp"
#include "primitive.hpp"

/// @brief Implicit sphere primitive.
class SpherePrim : public Primitive {
public:
    SpherePrim(const Point3D& center, const f64 radius);
    ~SpherePrim() override = default;

    /// @brief Computes the surface intersection with an implicit sphere
    /// centered at the origin with unit radius.
    Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

private:
    Point3D mCenter;
    f64 mRadius;
};
