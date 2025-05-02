#include "specular.hpp"

#include "math/vector_ops.hpp"
#include "util/thread_random.hpp"

Specular::Specular(const Vector3D& color, const f64 phong)
    : mColor(color), mPhong(phong) {
    mKind = Kind::Specular;
}

Specular::~Specular() {
}

Option<ScatterRecord> Specular::scatter(const Ray& incident,
                                        const Intersect& intersect) const {
    const f64 x1 = thread_rng::uniform<f64>();
    const f64 x2 = thread_rng::uniform<f64>();

    const f64 exp = 1.0 / (mPhong + 1.0);

    // Sample polar and azimuthal spherical coordinates.
    const f64 alpha = std::acos(std::pow(1.0 - x1, exp));
    const f64 beta = 2.0 * math::pi<f64>() * x2;

    const Point3D& p = intersect.position;
    const Vector3D& n = intersect.normal;
    const Vector3D& l = incident.direction;

    const Vector3D r = math::reflect(l, n);

    const Vector3D direction = math::perturb(r, alpha, beta);

    const Ray scattered(p, direction);

    return ScatterRecord(scattered, mColor);
}
