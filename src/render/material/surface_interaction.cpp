#include "surface_interaction.hpp"

SurfaceInteraction::SurfaceInteraction(
    const Point3D& p, const Normal3D& n, const Face face, const f64 t
)
    : p(p), n(n), face(face), mat(nullptr), t(t) {
}

SurfaceInteraction::SurfaceInteraction(const SurfaceInteraction& other)
    : p(other.p), n(other.n), face(other.face), mat(other.mat), t(other.t) {
}

SurfaceInteraction SurfaceInteraction::operator=(
    const SurfaceInteraction& other
) {
    p = other.p;
    n = other.n;
    face = other.face;
    mat = other.mat;
    t = other.t;

    return *this;
}

SurfaceInteraction::SurfaceInteraction(SurfaceInteraction&& other)
    : p(std::move(other.p)),
      n(std::move(other.n)),
      face(std::move(other.face)),
      mat(std::move(other.mat)),
      t(std::move(other.t)) {
}

SurfaceInteraction SurfaceInteraction::operator=(SurfaceInteraction&& other) {
    p = std::move(other.p);
    n = std::move(other.n);
    face = std::move(other.face);
    mat = std::move(other.mat);
    t = std::move(other.t);

    return *this;
}
