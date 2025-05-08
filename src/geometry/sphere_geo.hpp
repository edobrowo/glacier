#pragma once

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "math/point.hpp"
#include "primitive/mesh.hpp"
#include "primitive/sphere.hpp"

/// @brief Sphere geometry.
class SphereGeo {
public:
    SphereGeo();
    SphereGeo(const Point3D& center, const f64 radius);
    ~SphereGeo() = default;

    /// @brief Convert the sphere to an implicit primitive representation.
    PrimitivePtr toImplicitPrimitive() const;

    /// @brief Convert the sphere to a mesh via UV construction.
    PrimitivePtr toMeshPrimitive(const Size u_div, const Size v_div) const;

private:
    Point3D mCenter;
    f64 mRadius;
};
