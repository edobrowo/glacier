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

PrimitivePtr SphereGeo::primitive(const Primitive::Kind kind) const {
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

// TODO: normals and texture coordinates
PrimitivePtr SphereGeo::buildMeshPrimitive() const {
    const Index row = mUDiv + 1;

    IndexedMesh<VertexP> m;
    for (Index vi = 0; vi <= mVDiv; ++vi) {
        const f64 v = static_cast<f64>(vi) / mVDiv;
        const f64 polar = math::pi<f64>() * v;

        for (Index ui = 0; ui <= mUDiv; ++ui) {
            const f64 u = static_cast<f64>(ui) / mUDiv;
            const f64 azimuthal = 2.0 * math::pi<f64>() * u;

            const Point3D p(
                std::cos(azimuthal) * std::sin(polar) / 2.0,
                std::cos(polar) / 2.0,
                std::sin(azimuthal) * std::sin(polar) / 2.0
            );

            m.addVertex(VertexP{p});

            if (ui < mUDiv && vi < mVDiv) {
                const Index a = vi * row + ui;
                const Index b = (vi + 1) * row + ui;
                const Index c = vi * row + (ui + 1);
                const Index d = (vi + 1) * row + (ui + 1);

                m.addTriangle(a, c, d);
                m.addTriangle(a, d, b);
            }
        }
    }

    return std::make_unique<MeshPrim>(m);
}
