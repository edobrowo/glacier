#pragma once

#include "primitive.hpp"
#include "util/common.hpp"

/// @brief Implicit sphere primitive.
class Sphere : public Primitive {
public:
    Sphere();
    Sphere(const Point3D& center, const f64 radius);
    ~Sphere() override = default;

    /// @brief Computes the surface intersection with a sphere centered at the
    /// origin with unit radius.
    virtual Option<Intersect> intersect(const Ray& ray,
                                        const Interval& bounds) const override;

private:
    Point3D mCenter;
    f64 mRadius;
};
