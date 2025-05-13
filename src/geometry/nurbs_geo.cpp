#include "nurbs_geo.hpp"

#include <algorithm>

#include "indexed_mesh.hpp"
#include "primitive/mesh_prim.hpp"

// TODO: blossom-based?

namespace {

/// @brief B-spline basis component function f_{i,n}(u) that rises from zero
/// to one.
f64 f(const Index i, const Index n, const f64 u, std::span<const f64> k) {
    const f64 denom = k[i + n] - k[i];
    return denom == 0.0 ? 0.0 : (u - k[i]) / denom;
}

/// @brief B-spline basis component function g_{i,n}(u) that falls from one
/// to zero.
f64 g(const Index i, const Index n, const f64 u, std::span<const f64> k) {
    const f64 denom = k[i + n] - k[i];
    return denom == 0.0 ? 0.0 : (k[i + n] - u) / denom;
}

/// @brief B-spline basis function N_{i,n}(u). NURBS basis functions are
/// triangular functions that are nonzero over two knot spans. They rise
/// from zero to one in the first span and fall to zero in the second span.
f64 N(const Index i, const Index n, const f64 u, std::span<const f64> k) {
    if (n == 0) {
        if (i < k.size() - 1 && (k[i] <= u && u < k[i + 1])) {
            return 1.0;
        }
        return 0.0;
    }

    return f(i, n, u, k) * N(i, n - 1, u, k) +
           g(i + 1, n, u, k) * N(i + 1, n - 1, u, k);
}

}

NURBSGeo::NURBSGeo(
    std::span<const Point3D> points,
    std::span<const f64> weights,
    std::span<const f64> u_knot_vector,
    std::span<const f64> v_knot_vector
)
    : mUDiv(4), mVDiv(4) {
    assertm(
        points.size() == numPoints, "points must have numPoints control points"
    );
    assertm(
        weights.size() == numPoints,
        "weights must have numPoints control weights"
    );
    assertm(
        u_knot_vector.size() == numUKnots,
        "u knot vector must have numUKnots values"
    );
    assertm(
        v_knot_vector.size() == numVKnots,
        "v knot vector must have numVKnots values"
    );

    for (Index i = 0; i < numPoints; ++i)
        mPoints[i] = NURBSControlPoint{points[i], weights[i]};

    std::copy(u_knot_vector.begin(), u_knot_vector.end(), mUKnots.begin());
    std::copy(v_knot_vector.begin(), v_knot_vector.end(), mVKnots.begin());
}

PrimitivePtr NURBSGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

const std::array<NURBSControlPoint, NURBSGeo::numPoints>&
NURBSGeo::points() const {
    return mPoints;
}

Point3D NURBSGeo::eval(const f64 u, const f64 v) const {
    assertm(0.0 <= u && u <= 1.0, "u must be in [0, 1]");
    assertm(0.0 <= v && v <= 1.0, "v must be in [0, 1]");

    const Size n = degree;
    const Size m = degree;
    const Size k = numUPoints;
    const Size l = numVPoints;

    f64 denom = 0;
    for (Index q = 0; q < l; ++q) {
        for (Index p = 0; p < k; ++p) {
            const Index idx = q * numUPoints + p;

            const f64 wpq = mPoints[idx].weight;

            denom += N(p, n, u, mUKnots) * N(q, m, v, mVKnots) * wpq;
        }
    }

    if (denom == 0.0)
        return Point3D::zero();

    Point3D result = Point3D::zero();

    for (Index j = 0; j < l; ++j) {
        for (Index i = 0; i < k; ++i) {
            const Index idx = j * numUPoints + i;

            const Point3D& Pij = mPoints[idx].point;
            const f64 wij = mPoints[idx].weight;

            const f64 num = N(i, n, u, mUKnots) * N(j, m, v, mVKnots) * wij;

            result += (num / denom) * Pij.pos();
        }
    }

    return result;
}

void NURBSGeo::setDivisions(const Size u_div, const Size v_div) {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    mUDiv = u_div;
    mVDiv = v_div;
}

// TODO: normals and texture coordinates
PrimitivePtr NURBSGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    const Index row = mUDiv + 1;
    for (Index vi = 0; vi <= mVDiv; ++vi) {
        const f64 v = static_cast<f64>(vi) / mVDiv;

        for (Index ui = 0; ui <= mUDiv; ++ui) {
            const f64 u = static_cast<f64>(ui) / mUDiv;

            const Point3D& p = eval(u, v);

            m.addVertex(VertexP{p});

            if (ui < mUDiv - 1 && vi < mVDiv - 1) {
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
