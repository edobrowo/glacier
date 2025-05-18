#include "geometry/transform.hpp"

#include "math/transformation.hpp"

Transform::Transform()
    : mTranslation(Vector3D::zero()),
      mRotation(Vector3D::zero()),
      mScale(Vector3D::one()),
      mOrder(Transform::Order::SRT),
      mRotationOrder(Transform::RotationOrder::XYZ),
      mMatrix(Matrix4D::ident()),
      mInverse(Matrix4D::ident()) {
}

const Matrix4D& Transform::matrix() const {
    return mMatrix;
}

const Matrix4D& Transform::inverse() const {
    return mInverse;
}

const Vector3D& Transform::s() const {
    return mScale;
}

void Transform::s(const f64 x, const f64 y, const f64 z) {
    const Vector3D value(x, y, z);

    if (value == mScale)
        return;

    mScale = value;
    updateTransforms();
}

const Vector3D& Transform::r() const {
    return mRotation;
}

void Transform::r(const f64 x, const f64 y, const f64 z) {
    const Vector3D value(x, y, z);

    if (value == mRotation)
        return;

    mRotation = value;
    updateTransforms();
}

const Vector3D& Transform::t() const {
    return mTranslation;
}

void Transform::t(const f64 x, const f64 y, const f64 z) {
    const Vector3D value(x, y, z);

    if (value == mTranslation)
        return;

    mTranslation = value;
    updateTransforms();
}

Transform::Order Transform::order() const {
    return mOrder;
}

void Transform::setOrder(const Order order) {
    if (order == mOrder)
        return;

    mOrder = order;
    updateTransforms();
}

Transform::RotationOrder Transform::rotationOrder() const {
    return mRotationOrder;
}

void Transform::setRotationOrder(const RotationOrder order) {
    if (order == mRotationOrder)
        return;

    mRotationOrder = order;
    updateTransforms();
}

void Transform::updateTransforms() {
    const Matrix4D T = translate(mTranslation);

    const Matrix4D Rx = rotateX(mRotation.x);
    const Matrix4D Ry = rotateY(mRotation.y);
    const Matrix4D Rz = rotateZ(mRotation.z);
    Matrix4D R;

    switch (mRotationOrder) {
    case RotationOrder::XYZ:
        R = Rz * Ry * Rx;
        break;
    case RotationOrder::XZY:
        R = Ry * Rz * Rx;
        break;
    case RotationOrder::YXZ:
        R = Rz * Rx * Ry;
        break;
    case RotationOrder::YZX:
        R = Rx * Rz * Ry;
        break;
    case RotationOrder::ZXY:
        R = Ry * Rx * Rz;
        break;
    case RotationOrder::ZYX:
        R = Rx * Ry * Rz;
        break;
    default:
        unreachable;
    }

    const Matrix4D S = scale(mScale);

    switch (mOrder) {
    case Order::SRT:
        mMatrix = T * R * S;
        break;
    case Order::RST:
        mMatrix = T * S * R;
        break;
    case Order::STR:
        mMatrix = R * T * S;
        break;
    case Order::TSR:
        mMatrix = R * S * T;
        break;
    case Order::RTS:
        mMatrix = S * T * R;
        break;
    case Order::TRS:
        mMatrix = S * R * T;
        break;
    default:
        unreachable;
    }

    mInverse = invert(mMatrix).value_or(Matrix4D::ident());
}
