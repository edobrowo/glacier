#pragma once

#include <array>

#include "math/interval.hpp"
#include "primitive.hpp"
#include "quad.hpp"
#include "util/common.hpp"

/// @brief Cuboid primitive.
class Cuboid : public Primitive {
public:
    Cuboid(const Point3D& o,
           const Vector3D& x,
           const Vector3D& y,
           const Vector3D& z);
    ~Cuboid() override = default;

    /// @brief Computes the surface intersection with the cuboid by computing
    /// the intersection with each of the 6 component quads.
    virtual Option<Intersect> intersect(const Ray& ray,
                                        const Interval& bounds) const override;

private:
    std::array<Quad, 6> mQuads;
};
