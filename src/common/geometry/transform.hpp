#pragma once

#include "math/matrix.hpp"
#include "math/vector.hpp"

/// @brief Transform class.
class Transform {
public:
    enum class Order {
        SRT = 0,
        STR,
        RST,
        RTS,
        TSR,
        TRS
    };

    enum class RotationOrder {
        XYZ = 0,
        XZY,
        YXZ,
        YZX,
        ZXY,
        ZYX
    };

    Transform();
    ~Transform() = default;

    /// @brief Retrieves the model transform.
    const Matrix4D& matrix() const;

    /// @brief Retrieves the inverse of the model transform.
    const Matrix4D& inverse() const;

    /// @brief Retrieves a constant reference to the scale parameters.
    const Vector3D& s() const;

    /// @brief Sets the scale parameters. Updates the transform matrices.
    void s(const f64 x, const f64 y, const f64 z);

    /// @brief Retrieves a constant reference to the rotation parameters.
    const Vector3D& r() const;

    /// @brief Sets the rotation parameters. Updates the transform matrices.
    void r(const f64 x, const f64 y, const f64 z);

    /// @brief Retrieves a constant reference to the translation parameters.
    const Vector3D& t() const;

    /// @brief Sets the translation parameters. Updates the transform matrices.
    void t(const f64 x, const f64 y, const f64 z);

    /// @brief Retrieves the transform order.
    Order order() const;

    /// @brief Sets the transform order. Updates the transform matrices.
    void setOrder(const Order order);

    /// @brief Retrieves the rotation order.
    RotationOrder rotationOrder() const;

    /// @brief Sets the rotation order. Updates the transform matrices.
    void setRotationOrder(const RotationOrder order);

private:
    /// @brief Updates the model and inverse model transforms.
    void updateTransforms();

    Vector3D mTranslation;
    Vector3D mRotation;
    Vector3D mScale;

    Order mOrder;
    RotationOrder mRotationOrder;

    Matrix4D mMatrix;
    Matrix4D mInverse;
};
