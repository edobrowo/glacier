#include "quad_geo.hpp"

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "primitive/mesh_prim.hpp"
#include "primitive/quad_prim.hpp"

QuadGeo::QuadGeo()
    : mQ(Point3D(-0.5, -0.5, 0.0)),
      mU(Vector3D(1.0, 0.0, 0.0)),
      mV(Vector3D(0.0, 1.0, 0.0)) {
}

QuadGeo::QuadGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v)
    : mQ(Q), mU(u), mV(v) {
}

PrimitivePtr QuadGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

PrimitivePtr QuadGeo::buildImplicitPrimitive() const {
    return std::make_unique<QuadPrim>(mQ, mU, mV);
}

// TODO: normals and texture coordinates
PrimitivePtr QuadGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    m.addVertex(VertexP{mQ});
    m.addVertex(VertexP{mQ + mU});
    m.addVertex(VertexP{mQ + mV});
    m.addVertex(VertexP{mQ + mU + mV});

    m.addTriangle(0, 1, 3);
    m.addTriangle(0, 3, 2);

    return std::make_unique<MeshPrim>(m);
}
