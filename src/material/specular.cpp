#include "specular.hpp"

#include "util/thread_random.hpp"

Specular::Specular(const Vector3D& color, const f64 phong)
    : mColor(color), mPhong(phong) {
    mKind = Kind::Specular;
}

ScatterRecord Specular::scatter(const Ray& incident,
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

    const Vector3D& r = l + -2.0 * dot(l, n) * n;

    // Construct local orthonormal basis with the reflected, tangent, and
    // bitangent vectors.
    const Vector3D t = (r.x < 1.0) ? cross(r, Vector3D(1.0, 0.0, 0.0))
                                   : cross(r, Vector3D(0.0, 1.0, 0.0));
    const Vector3D b = cross(r, t);

    // Compute the new direction from the spherical coordinates.
    const Vector3D direction =
        std::cos(alpha) * r +
        std::sin(alpha) * (std::cos(beta) * t + std::sin(beta) * b);

    const Ray scattered(p, direction);

    return ScatterRecord(scattered, mColor);
}
