#pragma once

#include "primitive.hpp"
#include "util/common.hpp"

/// @brief Tube primitive.
class Tube : public Primitive {
public:
    Tube();
    Tube(
        const Point3D& center,
        const f64 radius,
        const f64 height,
        const bool top,
        const bool bottom
    );
    ~Tube() override = default;

    /// @brief Computes the surface intersection with the implicit tube quadric.
    virtual Option<Intersect> intersect(const Ray& ray, const Interval& bounds)
        const override;

private:
    Point3D mCenter;
    f64 mRadius, mHeight;
    bool mTopCap, mBottomCap;
};
