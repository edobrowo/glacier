#include "geometry/bezier_patch.hpp"

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

BezierPatch::BezierPatch(std::span<const Point3D> points) : mUDiv(4), mVDiv(4) {
    assertm(points.size() == 16, "points must have 16 control points");

    std::copy(points.begin(), points.end(), mPoints.begin());
}

TriangleMesh BezierPatch::mesh() const {
    TriangleMesh mesh;

    const Index row = mUDiv + 1;
    for (Index vi = 0; vi <= mVDiv; ++vi) {
        const f64 v = static_cast<f64>(vi) / mVDiv;

        for (Index ui = 0; ui <= mUDiv; ++ui) {
            const f64 u = static_cast<f64>(ui) / mUDiv;

            const Point3D& p = eval(u, v);

            mesh.addVertex(Vertex{p});

            if (ui < mUDiv && vi < mVDiv) {
                const Index a = vi * row + ui;
                const Index b = vi * row + (ui + 1);
                const Index c = (vi + 1) * row + ui;
                const Index d = (vi + 1) * row + (ui + 1);

                mesh.addTriangle(a, b, d);
                mesh.addTriangle(a, d, c);
            }
        }
    }

    return mesh;
}

const std::array<Point3D, 16>& BezierPatch::points() const {
    return mPoints;
}

Point3D BezierPatch::eval(const f64 u, const f64 v) const {
    assertm(0.0 <= u && u <= 1.0, "u must be in [0, 1]");
    assertm(0.0 <= v && v <= 1.0, "v must be in [0, 1]");

    return cubic_bezier_patch(mPoints, u, v);
}

void BezierPatch::setDivisions(const Size u_div, const Size v_div) {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    mUDiv = u_div;
    mVDiv = v_div;
}
