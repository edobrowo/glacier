#include "material/mirror_specular.hpp"

#include "common/math/vector_ops.hpp"

MirrorSpecular::MirrorSpecular(const Vector3D& color) : mColor(color) {
    mKind = Kind::MirrorSpecular;
}

MirrorSpecular::~MirrorSpecular() {
}

Option<ScatterRecord> MirrorSpecular::scatter(
    const Ray& incident, const SurfaceInteraction& interaction
) const {
    const Point3D& p = interaction.p;
    const Vector3D& n = interaction.n;
    const Vector3D& l = incident.direction;

    const Vector3D& r = math::reflect(l, n);

    const Ray scattered(p, r);

    return ScatterRecord(scattered, mColor);
}
