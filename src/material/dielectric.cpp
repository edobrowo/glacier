#include "dielectric.hpp"

#include "math/vector_ops.hpp"
#include "util/thread_random.hpp"

Dielectric::Dielectric(const f64 eta) : mEta(eta) {
    mKind = Kind::Dielectric;
}

Dielectric::~Dielectric() {
}

/// @brief Reflectance calculated using Schlick's approximation
static f64 reflectance(const f64 cosine, const f64 ri) {
    const f64 r0 = math::sqr((1.0 - ri) / (1.0 + ri));
    return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
}

Option<ScatterRecord> Dielectric::scatter(
    const Ray& incident, const Intersect& intersect
) const {
    // TODO: handle entering upon intersection (or just more gracefully).
    const bool entering = incident.direction.dot(intersect.normal) > 0.0;
    const Vector3D n = entering ? -intersect.normal : intersect.normal;
    const f64 ri = entering ? mEta : (1.0 / mEta);

    const Vector3D l = incident.direction.normalize();
    const f64 cos_theta = std::min(-l.dot(n), 1.0);
    const f64 sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    const bool cannot_refract = ri * sin_theta > 1.0;
    const bool schlick_test =
        reflectance(cos_theta, ri) > thread_rng::uniform<f64>();

    const Vector3D direction = (cannot_refract || schlick_test)
                                   ? math::reflect(l, n)
                                   : math::refract(l, n, ri);

    const Ray scattered(intersect.position, direction);

    return ScatterRecord(scattered, Vector3D::uniform(1.0f));
}
