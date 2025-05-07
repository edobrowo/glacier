#pragma once

#include "primitive.hpp"
#include "util/common.hpp"

/// @brief Tube primitive.
class Tube : public Primitive {
public:
    Tube();
    Tube(const Point3D& center, const f64 radius, const f64 height);
    ~Tube() override = default;

    /// @brief Computes the surface intersection with the tube.
    virtual Option<Intersect> intersect(const Ray& ray, const Interval& bounds)
        const override;

    bool top;
    bool bot;

private:
    Point3D mCenter;
    f64 mRadius;
    f64 mHeight;
};
