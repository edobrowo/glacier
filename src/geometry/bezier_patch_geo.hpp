#pragma once

#include <array>
#include <span>

#include "indexed_mesh.hpp"
#include "math/point.hpp"
#include "primitive/mesh.hpp"
#include "util/common.hpp"

class BezierPatchGeo {
public:
    BezierPatchGeo(std::span<const Point3D> points);
    ~BezierPatchGeo() = default;

    const std::array<Point3D, 16>& points() const;

    Point3D eval(const f64 u, const f64 v) const;

    PrimitivePtr toMeshPrimitive(const Size u_div, const Size v_div) const;

private:
    std::array<Point3D, 16> mPoints;
};
