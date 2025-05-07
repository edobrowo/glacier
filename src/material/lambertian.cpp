#include "lambertian.hpp"

#include "math/vector_ops.hpp"
#include "util/thread_random.hpp"

Lambertian::Lambertian(const Vector3D& color) : Material(), mColor(color) {
    mKind = Kind::Lambertian;
}

Lambertian::~Lambertian() {
}

Option<ScatterRecord> Lambertian::scatter(
    const Ray& incident, const Intersect& intersect
) const {
    const f64 x1 = thread_rng::uniform<f64>();
    const f64 x2 = thread_rng::uniform<f64>();

    // Sample polar and azimuthal spherical coordinates.
    const f64 alpha = std::sqrt(std::acos(1.0 - x1));
    const f64 beta = 2.0 * math::pi<f64>() * x2;

    const Point3D& p = intersect.position;
    const Vector3D& n = intersect.normal;

    const Vector3D direction = math::perturb(n, alpha, beta);

    const Ray scattered(p, direction);

    return ScatterRecord(scattered, mColor);
}
