#pragma once

#include <array>

#include "common/math/interval.hpp"
#include "common/prelude.hpp"
#include "primitive.hpp"
#include "quad_prim.hpp"

/// @brief Cuboid primitive.
class CuboidPrim : public Primitive {
public:
    CuboidPrim(
        const Point3D& o,
        const Vector3D& x,
        const Vector3D& y,
        const Vector3D& z
    );
    ~CuboidPrim() override = default;

    /// @brief Computes the surface intersection with the cuboid by computing
    /// the intersection with each of the 6 component quads.
    Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

private:
    std::array<QuadPrim, 6> mQuads;
};
