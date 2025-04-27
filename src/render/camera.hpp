#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "util/common.hpp"

/// @brief Virtual camera class. Defines a camera frame using a
/// lookfrom-lookat-fov parameterization. Provides pixel-to-worldspace
/// conversion and pixel sampling.
class Camera {
public:
    Camera(const Point3D& look_from,
           const Point3D& look_at,
           const Vector3D& up,
           const f64 fov,
           const Size nx,
           const Size ny);
    ~Camera() = default;

    /// @brief Camera origin (equal to LookFrom).
    const Point3D& origin() const;

    /// @brief Determines the worldspace position of pixel (px, py). The
    /// position corresponds to the center of the pixel.
    Point3D p(const Index px, const Index py) const;

    /// @brief Samples the pixel (px, py). The position corresponds to the
    /// center of the pixel.
    Point3D sample(const Index px, const Index py) const;

    /// @brief Retrieves the raster width of the camera view.
    Size nx() const;

    /// @brief Retrieves the raster height of the camera view.
    Size ny() const;

private:
    u32 mNx, mNy;
    f64 mViewWidth, mViewHeight;

    Point3D mOrigin;
    Vector3D mU;
    Vector3D mV;
    Vector3D mW;

    Point3D mPixelOrigin;
    Vector3D mPixelU;
    Vector3D mPixelV;
};
