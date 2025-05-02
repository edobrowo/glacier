#include "mirror_specular.hpp"

#include "math/vector_ops.hpp"

MirrorSpecular::MirrorSpecular(const Vector3D& color) : mColor(color) {
    mKind = Kind::MirrorSpecular;
}

MirrorSpecular::~MirrorSpecular() {
}

ScatterRecord MirrorSpecular::scatter(const Ray& incident,
                                      const Intersect& intersect) const {
    const Point3D& p = intersect.position;
    const Vector3D& n = intersect.normal;
    const Vector3D& l = incident.direction;

    const Vector3D& r = math::reflect(l, n);

    const Ray scattered(p, r);

    return ScatterRecord(scattered, mColor);
}
