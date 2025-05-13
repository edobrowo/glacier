#include "bezier_patch_geo.hpp"

#include <algorithm>

#include "indexed_mesh.hpp"
#include "math/interpolation.hpp"
#include "primitive/mesh_prim.hpp"

/// @brief Interpolate the point at parameters (u, v).
static Point3D cubic_bezier_patch(
    std::span<const Point3D> p, const f64 u, const f64 v
) {
    assertm(p.size() == 16, "p must have 16 control points");

    std::array<Point3D, 4> a;
    for (Index i = 0; i < 4; ++i)
        a[i] = math::cubic_bezier(p.subspan(i * 4, 4), u);
    return math::cubic_bezier(std::span<const Point3D>(a), v);
}

BezierPatchGeo::BezierPatchGeo(std::span<const Point3D> points)
    : mUDiv(4), mVDiv(4) {
    assertm(points.size() == 16, "points must have 16 control points");

    std::copy(points.begin(), points.end(), mPoints.begin());
}

PrimitivePtr BezierPatchGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

const std::array<Point3D, 16>& BezierPatchGeo::points() const {
    return mPoints;
}

Point3D BezierPatchGeo::eval(const f64 u, const f64 v) const {
    assertm(0.0 <= u && u <= 1.0, "u must be in [0, 1]");
    assertm(0.0 <= v && v <= 1.0, "v must be in [0, 1]");

    return cubic_bezier_patch(mPoints, u, v);
}

void BezierPatchGeo::setDivisions(const Size u_div, const Size v_div) {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    mUDiv = u_div;
    mVDiv = v_div;
}

// TODO: normals and texture coordinates
PrimitivePtr BezierPatchGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    const Index row = mUDiv + 1;
    for (Index vi = 0; vi <= mVDiv; ++vi) {
        const f64 v = static_cast<f64>(vi) / mVDiv;

        for (Index ui = 0; ui <= mUDiv; ++ui) {
            const f64 u = static_cast<f64>(ui) / mUDiv;

            const Point3D& p = eval(u, v);

            m.addVertex(VertexP{p});

            if (ui < mUDiv && vi < mVDiv) {
                const Index a = vi * row + ui;
                const Index b = vi * row + (ui + 1);
                const Index c = (vi + 1) * row + ui;
                const Index d = (vi + 1) * row + (ui + 1);

                m.addTriangle(a, b, d);
                m.addTriangle(a, d, c);
            }
        }
    }

    return std::make_unique<MeshPrim>(m);
}
