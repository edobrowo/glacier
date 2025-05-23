#include "math/transform.hpp"

Transform::Transform()
    : mMatrix(Matrix4D::ident()), mInverse(Matrix4D::ident()) {
}

Transform::Transform(const Matrix4D& matrix)
    : mMatrix(matrix), mInverse(invert(matrix).value()) {
}

Transform::Transform(const Matrix4D& matrix, const Matrix4D& inverse)
    : mMatrix(matrix), mInverse(inverse) {
}

Transform::Transform(const Transform& other)
    : mMatrix(other.mMatrix), mInverse(other.mInverse) {
}

Transform::Transform(Transform&& other)
    : mMatrix(std::move(other.mMatrix)), mInverse(std::move(other.mInverse)) {
}

Transform& Transform::operator=(const Transform& other) {
    mMatrix = other.mMatrix;
    mInverse = other.mInverse;

    return *this;
}

Transform& Transform::operator=(Transform&& other) {
    mMatrix = std::move(other.mMatrix);
    mInverse = std::move(other.mInverse);

    return *this;
}

Transform Transform::scale(const Vector3D& factor) {
    // clang-format off
    return Transform(
        Matrix4D(
            {
                factor[0], 0.0,       0.0,       0.0,
                0.0,       factor[1], 0.0,       0.0,
                0.0,       0.0,       factor[2], 0.0,
                0.0,       0.0,       0.0,       1.0
            }
        ),
        Matrix4D(
            {
                1.0 / factor[0], 0.0,             0.0,             0.0,
                0.0,             1.0 / factor[1], 0.0,             0.0,
                0.0,             0.0,             1.0 / factor[2], 0.0,
                0.0,             0.0,             0.0,             1.0
            }
        )
    );
    // clang-format on
}

Transform Transform::scale(const f64 factor) {
    return scale(Vector3D::uniform(factor));
}

Transform Transform::rotate(const f64 angle, const Vector3D& k) {
    // https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formulaa

    Vector3D kn = k.normalize();

    // clang-format off
    const Matrix3D K(
        {
            0.0,  -kn[2], kn[1],
            kn[2], 0.0,  -kn[0],
           -kn[1], kn[0], 0.0,
        }
    );
    // clang-format on

    const Matrix3D I = Matrix3D::ident();
    const Matrix3D K2 = K * K;
    const Matrix3D R = I + (std::sin(angle)) * K + (1.0 - std::cos(angle)) * K2;

    return Transform(embed_ident<f64, 3, 4>(R, 0, 0));
}

Transform Transform::rotateX(const f64 angle) {
    // clang-format off
    return Transform(
        Matrix4D(
            {
                1.0, 0.0,            0.0,          0.0,
                0.0, ::cos(angle),  -::sin(angle), 0.0,
                0.0, ::sin(angle),   ::cos(angle), 0.0,
                0.0, 0.0,            0.0,          1.0
            }
        )
    );
    // clang-format on
}

Transform Transform::rotateY(const f64 angle) {
    // clang-format off
    return Transform(
        Matrix4D(
            {
                ::cos(angle), 0.0, ::sin(angle), 0.0,
                0.0,          1.0, 0.0,          0.0,
               -::sin(angle), 0.0, ::cos(angle), 0.0,
                0.0,          0.0, 0.0,          1.0
            }
        )
    );
    // clang-format on
}

Transform Transform::rotateZ(const f64 angle) {
    // clang-format off
    return Transform(
        Matrix4D(
            {
                ::cos(angle), -::sin(angle), 0.0, 0.0,
                ::sin(angle),  ::cos(angle), 0.0, 0.0,
                0.0,           0.0,          1.0, 0.0,
                0.0,           0.0,          0.0, 1.0
            }
        )
    );
    // clang-format on
}

Transform Transform::translate(const Vector3D& delta) {
    // clang-format off
    return Transform(
        Matrix4D(
            {
                1.0, 0.0, 0.0, delta[0],
                0.0, 1.0, 0.0, delta[1],
                0.0, 0.0, 1.0, delta[2],
                0.0, 0.0, 0.0, 1.0
            }
        ),
        Matrix4D(
            {
                1.0, 0.0, 0.0, -delta[0],
                0.0, 1.0, 0.0, -delta[1],
                0.0, 0.0, 1.0, -delta[2],
                0.0, 0.0, 0.0,  1.0
            }
        )
    );
    // clang-format on
}

Transform Transform::translate(const f64 delta) {
    return Transform::translate(Vector3D::uniform(delta));
}

const Matrix4D& Transform::matrix() const {
    return mMatrix;
}

const Matrix4D& Transform::inverse() const {
    return mInverse;
}

Vector3D Transform::operator()(const Vector3D& v) const {
    Vector3D result;
    for (Index row = 0; row < 3; ++row)
        for (Index col = 0; col < 3; ++col)
            result[row] += mMatrix(row, col) * v[col];
    return result;
}

Normal3D Transform::operator()(const Normal3D& n) const {
    const Matrix4D inv_transpose = transpose(mInverse);

    Normal3D result;
    for (Index row = 0; row < 3; ++row)
        for (Index col = 0; col < 3; ++col)
            result[row] += inv_transpose(row, col) * n[col];
    return result;
}

Point3D Transform::operator()(const Point3D& p) const {
    Point3D result;
    for (Index row = 0; row < 3; ++row)
        for (Index col = 0; col < 3; ++col)
            result[row] += mMatrix(row, col) * p[col];
    result[0] += mMatrix(0, 3);
    result[1] += mMatrix(1, 3);
    result[2] += mMatrix(2, 3);
    return result;
}

Ray Transform::operator()(const Ray& ray) const {
    return Ray((*this)(ray.origin), (*this)(ray.direction));
}

AABB Transform::operator()(const AABB& aabb) const {
    Point3D min = aabb.min();
    Point3D max = aabb.max();

    const std::array<Point3D, 8> corners = {
        (*this)(min),
        (*this)(Point3D(min.x, min.y, max.z)),
        (*this)(Point3D(min.x, max.y, min.z)),
        (*this)(Point3D(min.x, max.y, max.z)),
        (*this)(Point3D(max.x, min.y, min.z)),
        (*this)(Point3D(max.x, min.y, max.z)),
        (*this)(Point3D(max.x, max.y, min.z)),
        (*this)(max)
    };

    min = corners.front();
    max = corners.front();

    for (Index i = 1; i < corners.size(); ++i) {
        min = min.min(corners[i]);
        max = max.max(corners[i]);
    }

    return AABB(min, max);
}

void Transform::operator*=(const Transform& other) {
    mMatrix *= other.matrix();
    mInverse = other.inverse() * mInverse;
}

Transform operator*(const Transform& lhs, const Transform& rhs) {
    return Transform(
        lhs.matrix() * rhs.matrix(), rhs.inverse() * lhs.inverse()
    );
}

Transform invert(const Transform& t) {
    return Transform(t.inverse(), t.matrix());
}

Transform transpose(const Transform& t) {
    return Transform(transpose(t.matrix()), transpose(t.inverse()));
}
