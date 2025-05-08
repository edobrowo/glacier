#include "bezier_patch_geo.hpp"

#include <algorithm>

#include "math/interpolation.hpp"

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

BezierPatchGeo::BezierPatchGeo(std::span<const Point3D> points) {
    assertm(points.size() == 16, "points must have 16 control points");

    std::copy(points.begin(), points.end(), mPoints.begin());
}

const std::array<Point3D, 16>& BezierPatchGeo::points() const {
    return mPoints;
}

Point3D BezierPatchGeo::eval(const f64 u, const f64 v) const {
    assertm(0.0 <= u && u <= 1.0, "u must be in [0, 1]");
    assertm(0.0 <= v && v <= 1.0, "v must be in [0, 1]");

    return cubic_bezier_patch(mPoints, u, v);
}

// TODO: normals and texture coordinates
PrimitivePtr BezierPatchGeo::toMeshPrimitive(const Size u_div, const Size v_div)
    const {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    const Index row = u_div + 1;

    IndexedMesh<VertexP> m;
    for (Index vi = 0; vi <= v_div; ++vi) {
        const f64 v = static_cast<f64>(vi) / v_div;

        for (Index ui = 0; ui <= u_div; ++ui) {
            const f64 u = static_cast<f64>(ui) / u_div;

            const Point3D& p = eval(u, v);

            m.addVertex(VertexP{p});

            if (ui < u_div && vi < v_div) {
                const Index a = vi * row + ui;
                const Index b = (vi + 1) * row + ui;
                const Index c = vi * row + (ui + 1);
                const Index d = (vi + 1) * row + (ui + 1);

                m.addTriangle(a, c, d);
                m.addTriangle(a, d, b);
            }
        }
    }

    return std::make_unique<Mesh>(m);
}
