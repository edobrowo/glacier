#pragma once

#include "common/prelude.hpp"
#include "primitive/primitive.hpp"

/// @brief Tube primitive.
class TubePrim : public Primitive {
public:
    TubePrim(
        const Point3D& center,
        const f64 radius,
        const f64 height,
        const bool top,
        const bool bottom
    );
    ~TubePrim() override = default;

    /// @brief Computes the surface intersection with the implicit tube quadric.
    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

private:
    Point3D mCenter;
    f64 mRadius, mHeight;
    bool mTopCap, mBottomCap;
};
