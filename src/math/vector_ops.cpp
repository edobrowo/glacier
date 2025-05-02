#include "vector_ops.hpp"

namespace math {

Vector3D project(const Vector3D& v, const Vector3D& w) {
    return (v.dot(w) / w.dot()) * w;
}

f64 angle(const Vector3D& v, const Vector3D& w) {
    return std::acos(v.dot(w) / (v.length() * w.length()));
}

Vector3D reflect(const Vector3D& l, const Vector3D& n) {
    return l - 2.0 * l.dot(n) * n;
}

Vector3D perturb(const Vector3D& v, const f64 alpha, const f64 beta) {
    // Construct local orthonormal basis with vector, tangent, and bitangent
    // vectors.
    const Vector3D t = (v.x < 1.0) ? v.cross(Vector3D(1.0, 0.0, 0.0))
                                   : v.cross(Vector3D(0.0, 1.0, 0.0));
    const Vector3D b = v.cross(t);

    // Compute the new direction from the spherical coordinates.
    const Vector3D v_p =
        std::cos(alpha) * v +
        std::sin(alpha) * (std::cos(beta) * t + std::sin(beta) * b);

    return v_p;
}

Vector3D refract(const Vector3D& l, const Vector3D& n, const f64 eta) {
    const f64 cos_theta = std::min(-l.dot(n), 1.0);
    const Vector3D R_perp = eta * (l + cos_theta * n);
    const Vector3D R_para = -std::sqrt(math::abs(1.0 - R_perp.dot())) * n;
    return R_perp + R_para;
}

}
