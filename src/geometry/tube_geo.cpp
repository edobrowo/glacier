#include "tube_geo.hpp"

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "primitive/mesh_prim.hpp"
#include "primitive/tube_prim.hpp"

TubeGeo::TubeGeo()
    : mCenter(), mRadius(0.5), mHeight(1.0), mTopCap(true), mBottomCap(true) {
}

TubeGeo::TubeGeo(const Point3D& center, const f64 radius, const f64 height)
    : mCenter(center),
      mRadius(radius),
      mHeight(height),
      mTopCap(true),
      mBottomCap(true) {
}

PrimitivePtr TubeGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

void TubeGeo::setCapVisibility(const bool top, const bool bottom) {
    mTopCap = top;
    mBottomCap = bottom;
}

void TubeGeo::setDivisions(const Size div) {
    assertm(div > 0, "div must be greater than 0");

    mDiv = div;
}

PrimitivePtr TubeGeo::buildImplicitPrimitive() const {
    return std::make_unique<TubePrim>(
        mCenter, mRadius, mHeight, mTopCap, mBottomCap
    );
}

// TODO: normals and texture coordinates
PrimitivePtr TubeGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    const Vector3D top_offset(0.0, 0.0, mHeight / 2.0);
    const Vector3D bottom_offset(0.0, 0.0, -mHeight / 2.0);

    if (mTopCap)
        m.addVertex(VertexP{mCenter + top_offset});

    if (mBottomCap)
        m.addVertex(VertexP{mCenter + bottom_offset});

    const Index start = mTopCap + mBottomCap;

    for (Index ui = 0; ui <= mDiv; ++ui) {
        const f64 u = static_cast<f64>(ui) / mDiv;
        const f64 theta = 2.0 * math::pi<f64>() * u;

        const Point3D p_top =
            mCenter + top_offset +
            mRadius * (std::cos(theta) * Vector3D(1.0, 0.0, 0.0) +
                       std::sin(theta) * Vector3D(0.0, 1.0, 0.0));
        m.addVertex(VertexP{p_top});

        const Point3D p_bottom =
            mCenter + bottom_offset +
            mRadius * (std::cos(theta) * Vector3D(1.0, 0.0, 0.0) +
                       std::sin(theta) * Vector3D(0.0, 1.0, 0.0));
        m.addVertex(VertexP{p_bottom});

        if (ui < mDiv) {
            const Index a = start + 2 * ui;
            const Index b = start + 2 * ui + 1;
            const Index c = start + 2 * ui + 2;
            const Index d = start + 2 * ui + 3;

            m.addTriangle(a, b, c);
            m.addTriangle(b, d, c);

            if (mTopCap) {
                const Index top = 0;
                m.addTriangle(top, a, c);
            }

            if (mBottomCap) {
                const Index bottom = mBottomCap == mTopCap;
                m.addTriangle(bottom, d, b);
            }
        }
    }

    return std::make_unique<MeshPrim>(m);
}
