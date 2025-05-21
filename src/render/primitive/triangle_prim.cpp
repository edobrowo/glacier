#include "triangle_prim.hpp"

#include "common/math/almost.hpp"

TrianglePrim::TrianglePrim(
    const Point3D& Q, const Vector3D& u, const Vector3D& v
)
    : mQ(Q), mU(u), mV(v) {
    mKind = Kind::Implicit;

    mNormal = Normal3D(mU.cross(mV)).normalize();
    mD = mNormal.dot(mQ.pos());
    mW = Vector3D(mNormal) / mNormal.dot();
}

Option<SurfaceInteraction> TrianglePrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    const f64 denom = mNormal.dot(ray.direction);

    // No hit if the ray is parallel to the plane.
    if (almost::le_zero(math::abs(denom)))
        return std::nullopt;

    // No hit if the ray parameter is outside the parameter bounds.
    const f64 t = (mD - mNormal.dot(ray.origin.pos())) / denom;
    if (!bounds.contains(t))
        return std::nullopt;

    const Point3D P = ray.at(t);
    const Vector3D p = P - mQ;

    // Local frame canonical barycentric coordinate test.
    const f64 uu = mU.dot(mU);
    const f64 uv = mU.dot(mV);
    const f64 vv = mV.dot(mV);
    const f64 pu = p.dot(mU);
    const f64 pv = p.dot(mV);

    const f64 denom_bary = uv * uv - uu * vv;
    const f64 alpha = (uv * pv - vv * pu) / denom_bary;
    const f64 beta = (uv * pu - uu * pv) / denom_bary;

    // No hit if the ray is outside the plane boundaries.
    if (almost::l_zero(alpha) || almost::l_zero(beta) ||
        almost::g(alpha + beta, 1.0))
        return std::nullopt;

    if (ray.direction.dot(mNormal) > 0.0)
        return SurfaceInteraction(
            P, -mNormal, SurfaceInteraction::Face::Inside, t
        );
    else
        return SurfaceInteraction(
            P, mNormal, SurfaceInteraction::Face::Outside, t
        );
}
