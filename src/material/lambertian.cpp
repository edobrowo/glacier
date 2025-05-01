#include "lambertian.hpp"

#include "util/thread_random.hpp"

Lambertian::Lambertian(const Vector3D& color) : Material(), mColor(color) {
    mKind = Kind::Lambertian;
}

Lambertian::~Lambertian() {
}

ScatterRecord Lambertian::scatter(const Ray& incident,
                                  const Intersect& intersect) const {
    const f64 x1 = thread_rng::uniform<f64>();
    const f64 x2 = thread_rng::uniform<f64>();

    // Sample polar and azimuthal spherical coordinates.
    const f64 alpha = std::sqrt(std::acos(1.0 - x1));
    const f64 beta = 2.0 * math::pi<f64>() * x2;

    const Point3D& p = intersect.position;
    const Vector3D& n = intersect.normal;

    // Construct local orthonormal basis with the surface normal, tangent, and
    // bitangent vectors.
    const Vector3D t = (n.x < 1.0) ? n.cross(Vector3D(1.0, 0.0, 0.0))
                                   : n.cross(Vector3D(0.0, 1.0, 0.0));
    const Vector3D b = n.cross(t);

    // Compute the new direction from the spherical coordinates.
    const Vector3D direction =
        std::cos(alpha) * n +
        std::sin(alpha) * (std::cos(beta) * t + std::sin(beta) * b);

    const Ray scattered(p, direction);

    return ScatterRecord(scattered, mColor);
}
