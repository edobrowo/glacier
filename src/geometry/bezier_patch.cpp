#include "bezier_patch.hpp"

#include <algorithm>

#include "math/interpolation.hpp"

static Point3D cubic_bezier_patch(
    std::span<const Point3D> p, const f64 u, const f64 v
) {
    assertm(p.size() == 16, "p must have 16 control points");

    std::array<Point3D, 4> a;
    for (Index i = 0; i < 4; ++i)
        a[i] = math::cubic_bezier(p.subspan(i * 4, 4), u);
    return math::cubic_bezier(std::span<const Point3D>(a), v);
}

BezierPatch::BezierPatch(std::span<const Point3D> points) {
    assertm(points.size() == 16, "points must have 16 control points");

    std::copy(points.begin(), points.end(), mPoints.begin());
}

const std::array<Point3D, 16>& BezierPatch::points() const {
    return mPoints;
}

Point3D BezierPatch::eval(const f64 u, const f64 v) const {
    assertm(0.0 <= u && u <= 1.0, "u must be in [0, 1]");
    assertm(0.0 <= v && v <= 1.0, "v must be in [0, 1]");

    return cubic_bezier_patch(mPoints, u, v);
}
