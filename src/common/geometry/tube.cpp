#include "geometry/tube.hpp"

#include "math/constants.hpp"

Tube::Tube()
    : mCenter(), mRadius(0.5), mHeight(1.0), mTopCap(true), mBottomCap(true) {
}

Tube::Tube(const Point3D& center, const f64 radius, const f64 height)
    : mCenter(center),
      mRadius(radius),
      mHeight(height),
      mTopCap(true),
      mBottomCap(true) {
}

Point3D Tube::center() const {
    return mCenter;
}

f64 Tube::radius() const {
    return mRadius;
}

f64 Tube::height() const {
    return mHeight;
}

bool Tube::topCapVisible() const {
    return mTopCap;
}

bool Tube::bottomCapVisible() const {
    return mBottomCap;
}

// TODO: normals and texture coordinates
TriangleMesh Tube::mesh() const {
    TriangleMesh mesh;

    const Vector3D top_offset(0.0, 0.0, mHeight / 2.0);
    const Vector3D bottom_offset(0.0, 0.0, -mHeight / 2.0);

    if (mTopCap)
        mesh.addVertex(Vertex{mCenter + top_offset});

    if (mBottomCap)
        mesh.addVertex(Vertex{mCenter + bottom_offset});

    const Index start = mTopCap + mBottomCap;

    for (Index ui = 0; ui <= mDiv; ++ui) {
        const f64 u = static_cast<f64>(ui) / mDiv;
        const f64 theta = 2.0 * math::pi<f64>() * u;

        const Point3D p_top =
            mCenter + top_offset +
            mRadius * (std::cos(theta) * Vector3D(1.0, 0.0, 0.0) +
                       std::sin(theta) * Vector3D(0.0, 1.0, 0.0));
        mesh.addVertex(Vertex{p_top});

        const Point3D p_bottom =
            mCenter + bottom_offset +
            mRadius * (std::cos(theta) * Vector3D(1.0, 0.0, 0.0) +
                       std::sin(theta) * Vector3D(0.0, 1.0, 0.0));
        mesh.addVertex(Vertex{p_bottom});

        if (ui < mDiv) {
            const Index a = start + 2 * ui;
            const Index b = start + 2 * ui + 1;
            const Index c = start + 2 * ui + 2;
            const Index d = start + 2 * ui + 3;

            mesh.addTriangle(a, b, c);
            mesh.addTriangle(b, d, c);

            if (mTopCap) {
                const Index top = 0;
                mesh.addTriangle(top, a, c);
            }

            if (mBottomCap) {
                const Index bottom = mBottomCap == mTopCap;
                mesh.addTriangle(bottom, d, b);
            }
        }
    }

    return mesh;
}

void Tube::setCapVisibility(const bool top, const bool bottom) {
    mTopCap = top;
    mBottomCap = bottom;
}

void Tube::setDivisions(const Size div) {
    assertm(div > 0, "div must be greater than 0");

    mDiv = div;
}
