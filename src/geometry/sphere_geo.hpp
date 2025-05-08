#pragma once

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "math/point.hpp"
#include "primitive/mesh.hpp"
#include "primitive/sphere.hpp"

class SphereGeo {
public:
    SphereGeo();
    SphereGeo(const Point3D& center, const f64 radius);
    ~SphereGeo() = default;

    PrimitivePtr toImplicitPrimitive() const;
    PrimitivePtr toMeshPrimitive(const Size u_div, const Size v_div) const;

private:
    Point3D mCenter;
    f64 mRadius;
};
