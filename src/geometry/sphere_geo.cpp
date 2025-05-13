#include "sphere_geo.hpp"

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "primitive/mesh_prim.hpp"
#include "primitive/sphere_prim.hpp"

SphereGeo::SphereGeo() : mCenter(Point3D::zero()), mRadius(0.5) {
}

SphereGeo::SphereGeo(const Point3D& center, const f64 radius)
    : mCenter(center), mRadius(radius) {
}

PrimitivePtr SphereGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

const Point3D& SphereGeo::center() const {
    return mCenter;
}

f64 SphereGeo::radius() const {
    return mRadius;
}

void SphereGeo::setDivisions(const Size u_div, const Size v_div) {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    mUDiv = u_div;
    mVDiv = v_div;
}

PrimitivePtr SphereGeo::buildImplicitPrimitive() const {
    return std::make_unique<SpherePrim>(mCenter, mRadius);
}

// TODO: mCenter and mRadius
// TODO: normals and texture coordinates
PrimitivePtr SphereGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

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

            m.addVertex(VertexP{p});

            if (ui < mUDiv && vi < mVDiv - 1) {
                const Index a = (vi - 1) * row + ui;
                const Index b = (vi - 1) * row + (ui + 1);
                const Index c = vi * row + ui;
                const Index d = vi * row + (ui + 1);

                m.addTriangle(a, b, d);
                m.addTriangle(a, d, c);
            }
        }
    }

    // Top cap.
    {
        const Vector3D top_apex(0.0, 0.5, 0.0);
        const Point3D point = mCenter + mRadius * top_apex;

        m.addVertex(VertexP{point});

        const Index apex = m.vertices().size() - 1;

        for (Index ui = 0; ui < mUDiv; ++ui) {
            const Index a = ui;
            const Index b = ui + 1;

            m.addTriangle(apex, b, a);
        }
    }

    // Bottom cap.
    {
        const Vector3D bottom_apex(0.0, -0.5, 0.0);
        const Point3D point = mCenter + mRadius * bottom_apex;

        m.addVertex(VertexP{point});

        const Index apex = m.vertices().size() - 1;

        for (Index ui = 0; ui < mUDiv; ++ui) {
            const Index b = (mVDiv - 2) * row + ui;
            const Index c = (mVDiv - 2) * row + (ui + 1);

            m.addTriangle(apex, b, c);
        }
    }

    return std::make_unique<MeshPrim>(m);
}
