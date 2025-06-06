#include "tube_prim.hpp"

#include "common/math/rootfinding.hpp"

TubePrim::TubePrim(
    const Point3D& center,
    const f64 radius,
    const f64 height,
    const bool top,
    const bool bottom
)
    : mCenter(center),
      mRadius(radius),
      mHeight(height),
      mTopCap(top),
      mBottomCap(bottom) {
    mKind = Kind::Implicit;

    const Vector3D extent(mRadius, mRadius, mHeight / 2.0);
    mBbox = AABB(mCenter - extent, mCenter + extent);
}

Option<SurfaceInteraction> TubePrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    Option<SurfaceInteraction> closest = std::nullopt;

    // Tube side.
    {
        // Convenience component variables.
        const f64 ox = ray.origin.x - mCenter.x;
        const f64 oy = ray.origin.y - mCenter.y;

        const f64 dx = ray.direction.x;
        const f64 dy = ray.direction.y;

        // Set up quadratic.
        const f64 a = dx * dx + dy * dy;
        const f64 b = 2.0 * (dx * ox + dy * oy);
        const f64 c = ox * ox + oy * oy - mRadius * mRadius;

        // Solve quadratic.
        std::pair<Option<f64>, Option<f64>> roots =
            math::quadratic_roots(a, b, c);

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

        if (bounds.contains(t)) {
            const Point3D p = ray.at(t);

            // Compare hit point to z bounds.
            if (Interval(-mHeight / 2.0, mHeight / 2.0).contains(p.z)) {
                Normal3D normal =
                    Normal3D(p.x - mCenter.x, p.y - mCenter.y, 0.0) / mRadius;
                if (ray.direction.dot(normal) > 0.0)
                    closest = SurfaceInteraction(
                        p, -normal, SurfaceInteraction::Face::Inside, t
                    );
                else
                    closest = SurfaceInteraction(
                        p, normal, SurfaceInteraction::Face::Outside, t
                    );
            }
        }
    }

    // Top disk.
    if (mTopCap && ray.direction.z != 0.0) {
        const f64 z = mCenter.z + mHeight / 2.0;
        const f64 t = (z - ray.origin.z) / ray.direction.z;

        if (bounds.contains(t) && (!closest || t < closest->t)) {
            const Point3D p = ray.at(t);
            const f64 dist2 = (p.x - mCenter.x) * (p.x - mCenter.x) +
                              (p.y - mCenter.y) * (p.y - mCenter.y);
            const Normal3D normal = Normal3D(0, 0, 1);
            if (dist2 <= mRadius * mRadius) {
                if (ray.direction.dot(normal) > 0.0)
                    closest = SurfaceInteraction(
                        p, -normal, SurfaceInteraction::Face::Inside, t
                    );
                else
                    closest = SurfaceInteraction(
                        p, normal, SurfaceInteraction::Face::Outside, t
                    );
            }
        }
    }

    // Bottom disk.
    if (mBottomCap && ray.direction.z != 0.0) {
        const f64 z = mCenter.z - mHeight / 2.0;
        const f64 t = (z - ray.origin.z) / ray.direction.z;

        if (bounds.contains(t) && (!closest || t < closest->t)) {
            const Point3D p = ray.at(t);
            const f64 dist2 = (p.x - mCenter.x) * (p.x - mCenter.x) +
                              (p.y - mCenter.y) * (p.y - mCenter.y);
            const Normal3D normal = Normal3D(0, 0, -1);
            if (dist2 <= mRadius * mRadius) {
                if (ray.direction.dot(normal) > 0.0)
                    closest = SurfaceInteraction(
                        p, -normal, SurfaceInteraction::Face::Inside, t
                    );
                else
                    closest = SurfaceInteraction(
                        p, normal, SurfaceInteraction::Face::Outside, t
                    );
            }
        }
    }

    return closest;
}
