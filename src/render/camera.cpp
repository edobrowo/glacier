#include "render/camera.hpp"

#include "common/math/numeric.hpp"
#include "common/util/log.hpp"
#include "common/util/thread_random.hpp"

Camera::Camera(
    const Point3D& look_from,
    const Point3D& look_at,
    const Vector3D& up,
    const f64 fov,
    const Size nx,
    const Size ny
) {
    // Raster image dimensions.
    mNx = nx;
    mNy = ny;

    // Camera frame.
    mOrigin = look_from;
    mW = (look_from - look_at).normalize();
    mU = (up.cross(mW)).normalize();
    mV = mW.cross(mU);

    // View dimensions.
    const f64 aspect = static_cast<f64>(nx) / static_cast<f64>(ny);
    mViewHeight = 2.0 * std::tan(math::rad(fov) / 2.0);
    mViewWidth = mViewHeight * aspect;

    // Viewport vectors in the camera frame.
    const Vector3D viewport_u = mU * mViewWidth;
    const Vector3D viewport_v = -mV * mViewHeight;

    // Pixel delta vectors in the camera frame.
    mPixelU = viewport_u / static_cast<f64>(mNx);
    mPixelV = viewport_v / static_cast<f64>(mNy);

    // Locate the origin pixel at the top-left corner of the viewport.
    mPixelOrigin = mOrigin - mW - viewport_u / 2.0 - viewport_v / 2.0 +
                   0.5 * (mPixelU + mPixelV);
}

const Point3D& Camera::origin() const {
    return mOrigin;
}

static inline Vector2D sample_unit_square() {
    return Vector2D(
        thread_rng::uniform(-0.5, 0.5), thread_rng::uniform(-0.5, 0.5)
    );
}

Point3D Camera::p(const Index px, const Index py) const {
    assertm(px < mNx, "px must be less than raster width");
    assertm(py < mNy, "py must be less than raster height");

    const f64 x = static_cast<f64>(px);
    const f64 y = static_cast<f64>(py);

    return mPixelOrigin + x * mPixelU + y * mPixelV;
}

Point3D Camera::sample(const Index px, const Index py) const {
    assertm(px < mNx, "px must be less than raster width");
    assertm(py < mNy, "py must be less than raster height");

    const Vector2D sample_pos = sample_unit_square();

    const f64 x = static_cast<f64>(px) + sample_pos.x;
    const f64 y = static_cast<f64>(py) + sample_pos.y;

    return mPixelOrigin + x * mPixelU + y * mPixelV;
}

Size Camera::nx() const {
    return mNx;
}

Size Camera::ny() const {
    return mNy;
}
