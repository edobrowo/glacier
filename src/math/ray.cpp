#include "ray.hpp"

Ray::Ray(const Point3D& origin, const Vector3D& direction)
    : origin(origin), direction(direction) {
}

Point3D Ray::at(const f64 t) const {
    return origin + t * direction;
}
