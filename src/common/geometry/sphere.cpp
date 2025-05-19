#include "geometry/sphere.hpp"

#include "geometry/triangle_mesh.hpp"
#include "math/constants.hpp"

Sphere::Sphere() : mCenter(Point3D::zero()), mRadius(0.5) {
}

Sphere::Sphere(const Point3D& center, const f64 radius)
    : mCenter(center), mRadius(radius) {
}

// TODO: normals and texture coordinates
TriangleMesh Sphere::mesh() const {
    TriangleMesh mesh;

    const Index row = mUDiv + 1;

    for (Index vi = 1; vi < mVDiv; ++vi) {
        const f64 v = static_cast<f64>(vi) / mVDiv;
        const f64 polar = math::pi<f64>() * v;

        for (Index ui = 0; ui <= mUDiv; ++ui) {
            const f64 u = static_cast<f64>(ui) / mUDiv;
            const f64 azimuthal = 2.0 * math::pi<f64>() * u;

            const Vector3D uv(
                std::cos(azimuthal) * std::sin(polar),
                std::cos(polar),
                std::sin(azimuthal) * std::sin(polar)
            );
            const Point3D p = mCenter + mRadius * uv;

            mesh.addVertex(Vertex{p});

            if (ui < mUDiv && vi < mVDiv - 1) {
                const Index a = (vi - 1) * row + ui;
                const Index b = (vi - 1) * row + (ui + 1);
                const Index c = vi * row + ui;
                const Index d = vi * row + (ui + 1);

                mesh.addTriangle(a, b, d);
                mesh.addTriangle(a, d, c);
            }
        }
    }

    // Top cap.
    {
        const Vector3D top_apex(0.0, 0.5, 0.0);
        const Point3D point = mCenter + mRadius * top_apex;

        mesh.addVertex(Vertex{point});

        const Index apex = mesh.vertices().size() - 1;

        for (Index ui = 0; ui < mUDiv; ++ui) {
            const Index a = ui;
            const Index b = ui + 1;

            mesh.addTriangle(apex, b, a);
        }
    }

    // Bottom cap.
    {
        const Vector3D bottom_apex(0.0, -0.5, 0.0);
        const Point3D point = mCenter + mRadius * bottom_apex;

        mesh.addVertex(Vertex{point});

        const Index apex = mesh.vertices().size() - 1;

        for (Index ui = 0; ui < mUDiv; ++ui) {
            const Index b = (mVDiv - 2) * row + ui;
            const Index c = (mVDiv - 2) * row + (ui + 1);

            mesh.addTriangle(apex, b, c);
        }
    }

    return mesh;
}

const Point3D& Sphere::center() const {
    return mCenter;
}

f64 Sphere::radius() const {
    return mRadius;
}

void Sphere::setDivisions(const Size u_div, const Size v_div) {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    mUDiv = u_div;
    mVDiv = v_div;
}
