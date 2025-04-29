#include "intersect.hpp"

Intersect::Intersect(const f64 t,
                     const Point3D& position,
                     const Vector3D& normal)
    : t(t), position(position), normal(normal) {
}

Intersect::Intersect(const Intersect& other)
    : t(other.t), position(other.position), normal(other.normal) {
}

Intersect& Intersect::operator=(const Intersect& other) {
    t = other.t;
    position = other.position;
    normal = other.normal;

    return *this;
}

Intersect::Intersect(Intersect&& other)
    : t(std::move(other.t)),
      position(std::move(other.position)),
      normal(std::move(other.normal)) {
}

Intersect& Intersect::operator=(Intersect&& other) {
    t = std::move(other.t);
    position = std::move(other.position);
    normal = std::move(other.normal);

    return *this;
}
