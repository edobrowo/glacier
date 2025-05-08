#include "intersect.hpp"

Intersect::Intersect(
    const f64 t,
    const Point3D& position,
    const Vector3D& normal,
    const Intersect::Face face
)
    : t(t), position(position), normal(normal), face(face) {
}

Intersect::Intersect(const Intersect& other)
    : t(other.t),
      position(other.position),
      normal(other.normal),
      face(other.face) {
}

Intersect& Intersect::operator=(const Intersect& other) {
    t = other.t;
    position = other.position;
    normal = other.normal;
    face = other.face;

    return *this;
}

Intersect::Intersect(Intersect&& other)
    : t(std::move(other.t)),
      position(std::move(other.position)),
      normal(std::move(other.normal)),
      face(std::move(other.face)) {
}

Intersect& Intersect::operator=(Intersect&& other) {
    t = std::move(other.t);
    position = std::move(other.position);
    normal = std::move(other.normal);
    face = std::move(other.face);

    return *this;
}
