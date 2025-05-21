#include "scene_transform.hpp"

#include "common/math/transform.hpp"

SceneTransform::SceneTransform()
    : mTranslation(Vector3D::zero()),
      mRotation(Vector3D::zero()),
      mScale(Vector3D::one()),
      mOrder(SceneTransform::Order::SRT),
      mRotationOrder(SceneTransform::RotationOrder::XYZ),
      mTransform() {
}

SceneTransform::SceneTransform(const SceneTransform& other)
    : mTranslation(other.mTranslation),
      mRotation(other.mRotation),
      mScale(other.mScale),
      mOrder(other.mOrder),
      mRotationOrder(other.mRotationOrder),
      mTransform(other.mTransform) {
}

SceneTransform::SceneTransform(SceneTransform&& other)
    : mTranslation(std::move(other.mTranslation)),
      mRotation(std::move(other.mRotation)),
      mScale(std::move(other.mScale)),
      mOrder(std::move(other.mOrder)),
      mRotationOrder(std::move(other.mRotationOrder)),
      mTransform(std::move(other.mTransform)) {
}

SceneTransform& SceneTransform::operator=(const SceneTransform& other) {
    mTranslation = other.mTranslation;
    mRotation = other.mRotation;
    mScale = other.mScale;
    mOrder = other.mOrder;
    mRotationOrder = other.mRotationOrder;
    mTransform = other.mTransform;

    return *this;
}

SceneTransform& SceneTransform::operator=(SceneTransform&& other) {
    mTranslation = std::move(other.mTranslation);
    mRotation = std::move(other.mRotation);
    mScale = std::move(other.mScale);
    mOrder = std::move(other.mOrder);
    mRotationOrder = std::move(other.mRotationOrder);
    mTransform = std::move(other.mTransform);

    return *this;
}

const Transform& SceneTransform::transform() const {
    return mTransform;
}

const Vector3D& SceneTransform::s() const {
    return mScale;
}

void SceneTransform::s(const f64 x, const f64 y, const f64 z) {
    const Vector3D value(x, y, z);

    if (value == mScale)
        return;

    mScale = value;
    updateTransforms();
}

const Vector3D& SceneTransform::r() const {
    return mRotation;
}

void SceneTransform::r(const f64 x, const f64 y, const f64 z) {
    const Vector3D value(x, y, z);

    if (value == mRotation)
        return;

    mRotation = value;
    updateTransforms();
}

const Vector3D& SceneTransform::t() const {
    return mTranslation;
}

void SceneTransform::t(const f64 x, const f64 y, const f64 z) {
    const Vector3D value(x, y, z);

    if (value == mTranslation)
        return;

    mTranslation = value;
    updateTransforms();
}

SceneTransform::Order SceneTransform::order() const {
    return mOrder;
}

void SceneTransform::setOrder(const Order order) {
    if (order == mOrder)
        return;

    mOrder = order;
    updateTransforms();
}

SceneTransform::RotationOrder SceneTransform::rotationOrder() const {
    return mRotationOrder;
}

void SceneTransform::setRotationOrder(const RotationOrder order) {
    if (order == mRotationOrder)
        return;

    mRotationOrder = order;
    updateTransforms();
}

void SceneTransform::updateTransforms() {
    const Transform T = Transform::translate(mTranslation);

    const Transform Rx = Transform::rotateX(mRotation.x);
    const Transform Ry = Transform::rotateY(mRotation.y);
    const Transform Rz = Transform::rotateZ(mRotation.z);
    Transform R;

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

    const Transform S = Transform::scale(mScale);

    switch (mOrder) {
    case Order::SRT:
        mTransform = T * R * S;
        break;
    case Order::RST:
        mTransform = T * S * R;
        break;
    case Order::STR:
        mTransform = R * T * S;
        break;
    case Order::TSR:
        mTransform = R * S * T;
        break;
    case Order::RTS:
        mTransform = S * T * R;
        break;
    case Order::TRS:
        mTransform = S * R * T;
        break;
    default:
        unreachable;
    }
}
