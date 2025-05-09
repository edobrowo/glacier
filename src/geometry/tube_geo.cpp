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

PrimitivePtr TubeGeo::primitive(const Primitive::Kind kind) const {
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

PrimitivePtr TubeGeo::buildImplicitPrimitive() const {
    return std::make_unique<TubePrim>(
        mCenter, mRadius, mHeight, mTopCap, mBottomCap
    );
}

// TODO: normals and texture coordinates
PrimitivePtr TubeGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    // TODO:

    return std::make_unique<MeshPrim>(m);
}
