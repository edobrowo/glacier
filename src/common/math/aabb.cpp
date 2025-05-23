#include "aabb.hpp"

AABB::AABB() : x(Interval::empty), y(Interval::empty), z(Interval::empty) {
}

AABB::AABB(const Interval& x, const Interval& y, const Interval& z)
    : x(x), y(y), z(z) {
    padWithMinimum();
}

AABB::AABB(const Point3D& p1, const Point3D& p2) : AABB() {
    x = (p1.x <= p2.x) ? Interval(p1.x, p2.x) : Interval(p2.x, p1.x);
    y = (p1.y <= p2.y) ? Interval(p1.y, p2.y) : Interval(p2.y, p1.y);
    z = (p1.z <= p2.z) ? Interval(p1.z, p2.z) : Interval(p2.z, p1.z);
    padWithMinimum();
}

AABB::AABB(const AABB& other) : x(other.x), y(other.y), z(other.z) {
}

AABB::AABB(AABB&& other)
    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {
}

AABB& AABB::operator=(const AABB& other) {
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

AABB& AABB::operator=(AABB&& other) {
    x = std::move(other.x);
    y = std::move(other.y);
    z = std::move(other.z);

    return *this;
}

Point3D AABB::min() const {
    return Point3D(x.min, y.min, z.min);
}

Point3D AABB::max() const {
    return Point3D(x.max, y.max, z.max);
}

const Interval& AABB::axis(const Index i) const {
    assertm(i < 3, "i must be 0, 1, or 2");
    return axes[i];
}

bool AABB::checkIntersect(const Ray& ray, const Interval& bounds) const {
    Interval slab_bounds = bounds;

    for (Index i = 0; i < 3; ++i) {
        const Interval& ax = axis(i);
        const f64 dir_inv = 1.0 / ray.direction[i];

        const f64 t0 = (ax.min - ray.origin[i]) * dir_inv;
        const f64 t1 = (ax.max - ray.origin[i]) * dir_inv;

        if (t0 < t1) {
            if (t0 > slab_bounds.min)
                slab_bounds.min = t0;
            if (t1 < slab_bounds.max)
                slab_bounds.max = t1;
        } else {
            if (t1 > slab_bounds.min)
                slab_bounds.min = t1;
            if (t0 < slab_bounds.max)
                slab_bounds.max = t0;
        }

        if (slab_bounds.max <= slab_bounds.min)
            return false;
    }

    return true;
}

AABB AABB::enclosure(const AABB& other) const {
    return AABB(
        x.enclosure(other.x), y.enclosure(other.y), z.enclosure(other.z)
    );
}

AABB AABB::intersection(const AABB& other) const {
    return AABB(
        x.intersection(other.x),
        y.intersection(other.y),
        z.intersection(other.z)
    );
}

void AABB::padWithMinimum() {
    if (x.size() < MINIMUM_AXIS_SIZE)
        x = x.expand(MINIMUM_AXIS_SIZE);
    if (y.size() < MINIMUM_AXIS_SIZE)
        y = y.expand(MINIMUM_AXIS_SIZE);
    if (z.size() < MINIMUM_AXIS_SIZE)
        z = z.expand(MINIMUM_AXIS_SIZE);
}
