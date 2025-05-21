#pragma once

#include "math/matrix.hpp"
#include "math/normal.hpp"
#include "math/point.hpp"
#include "math/ray.hpp"
#include "math/vector.hpp"
#include "prelude.hpp"

/// @brief Affine transformation.
class Transform {
public:
    Transform();
    explicit Transform(const Matrix4D& matrix);
    Transform(const Matrix4D& matrix, const Matrix4D& inverse);
    ~Transform() = default;

    static Transform scale(const Vector3D& factor);
    static Transform scale(const f64 factor);

    static Transform rotate(const f64 angle, const Vector3D& k);
    static Transform rotateX(const f64 angle);
    static Transform rotateY(const f64 angle);
    static Transform rotateZ(const f64 angle);

    static Transform translate(const Vector3D& delta);
    static Transform translate(const f64 delta);

    Transform(const Transform& other);
    Transform(Transform&& other);

    Transform& operator=(const Transform& other);
    Transform& operator=(Transform&& other);

    const Matrix4D& matrix() const;
    const Matrix4D& inverse() const;

    Vector3D operator()(const Vector3D& v) const;
    Normal3D operator()(const Normal3D& n) const;
    Point3D operator()(const Point3D& p) const;
    Ray operator()(const Ray& ray) const;

    void operator*=(const Transform& other);

private:
    Matrix4D mMatrix;
    Matrix4D mInverse;
};

Transform operator*(const Transform& lhs, const Transform& rhs);

Transform invert(const Transform& t);
Transform transpose(const Transform& t);
