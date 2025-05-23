#pragma once

#include "math/aabb.hpp"
#include "math/matrix.hpp"
#include "math/normal.hpp"
#include "math/point.hpp"
#include "math/ray.hpp"
#include "math/vector.hpp"
#include "prelude.hpp"
#include "util/format.hpp"

/// @brief Affine transformation.
class Transform {
public:
    Transform();
    explicit Transform(const Matrix4D& matrix);
    Transform(const Matrix4D& matrix, const Matrix4D& inverse);
    ~Transform() = default;

    Transform(const Transform& other);
    Transform(Transform&& other);

    Transform& operator=(const Transform& other);
    Transform& operator=(Transform&& other);

    /// @brief Non-uniform scale transform.
    static Transform scale(const Vector3D& factor);

    /// @brief Uniform scale transform.
    static Transform scale(const f64 factor);

    /// @brief Rotation about an arbitrary axis transform.
    static Transform rotate(const f64 angle, const Vector3D& k);

    /// @brief Rotation about the x axis.
    static Transform rotateX(const f64 angle);

    /// @brief Rotation about the y axis.
    static Transform rotateY(const f64 angle);

    /// @brief Rotation about the z axis.
    static Transform rotateZ(const f64 angle);

    /// @brief Non-uniform translation transform.
    static Transform translate(const Vector3D& delta);

    /// @brief Uniform translation transform.
    static Transform translate(const f64 delta);

    /// @brief Retrieves a constant reference to the transformation matrix.
    const Matrix4D& matrix() const;

    /// @brief Retrieves a constant reference to the inverse transformation
    /// matrix.
    const Matrix4D& inverse() const;

    Vector3D operator()(const Vector3D& v) const;
    Normal3D operator()(const Normal3D& n) const;
    Point3D operator()(const Point3D& p) const;
    Ray operator()(const Ray& ray) const;
    AABB operator()(const AABB& aabb) const;

    void operator*=(const Transform& other);

private:
    Matrix4D mMatrix;
    Matrix4D mInverse;
};

Transform operator*(const Transform& lhs, const Transform& rhs);

Transform invert(const Transform& t);
Transform transpose(const Transform& t);

template <>
struct FormatWriter<Transform> {
    static void write(const Transform& value, StringBuffer& sb) {
        sb.appendFormat("T() = {}\nT-() = {}", value.matrix(), value.inverse());
    }
};
