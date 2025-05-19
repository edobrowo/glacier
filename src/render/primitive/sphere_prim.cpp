#include "sphere_prim.hpp"

#include "common/math/rootfinding.hpp"

SpherePrim::SpherePrim(const Point3D& center, const f64 radius)
    : Primitive(), mCenter(center), mRadius(radius) {
    mKind = Kind::Implicit;
}

Option<SurfaceInteraction> SpherePrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    // Set up quadratic.
    const Vector3D oc = ray.origin - mCenter;
    const f64 a = ray.direction.dot();
    const f64 b = 2.0 * ray.direction.dot(oc);
    const f64 c = oc.dot() - math::sqr(mRadius);

    // Solve quadratic.
    std::pair<Option<f64>, Option<f64>> roots = math::quadratic_roots(a, b, c);

    // No roots implies no intersection.
    if (!roots.first.has_value() && !roots.second.has_value())
        return std::nullopt;

    const f64 t1 = roots.first.value_or(-1.0);
    const f64 t2 = roots.second.value_or(-1.0);

    // Take the minimum nonnegative root.
    f64 t = 0;
    if (t1 < 0.0 && t2 < 0.0)
        return std::nullopt;
    else if (t1 < 0.0)
        t = t2;
    else if (t2 < 0.0)
        t = t1;
    else
        t = std::min(t1, t2);

    if (!bounds.contains(t))
        return std::nullopt;

    const Point3D p = ray.at(t);

    const Vector3D normal = (p - mCenter) / mRadius;

    if (ray.direction.dot(normal) > 0.0)
        return SurfaceInteraction(
            p, -normal, SurfaceInteraction::Face::Inside, t
        );
    else
        return SurfaceInteraction(
            p, normal, SurfaceInteraction::Face::Outside, t
        );
}
