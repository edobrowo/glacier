#include "mirror_specular.hpp"

MirrorSpecular::MirrorSpecular(const Vector3D& color) : mColor(color) {
    mKind = Kind::MirrorSpecular;
}

ScatterRecord MirrorSpecular::scatter(const Ray& incident,
                                      const Intersect& intersect) const {
    const Point3D& p = intersect.position;
    const Vector3D& n = intersect.normal;
    const Vector3D& l = incident.direction;

    const Vector3D& r = l + -2.0 * dot(l, n) * n;

    const Ray scattered(p, r);

    return ScatterRecord(scattered, mColor);
}
