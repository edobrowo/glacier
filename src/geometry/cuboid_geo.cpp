#include "cuboid_geo.hpp"

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "primitive/cuboid_prim.hpp"
#include "primitive/mesh_prim.hpp"

CuboidGeo::CuboidGeo()
    : mQ(-0.5, -0.5, -0.5),
      mX(1.0, 0.0, 0.0),
      mY(0.0, 1.0, 0.0),
      mZ(0.0, 0.0, 1.0) {
}

CuboidGeo::CuboidGeo(
    const Point3D& Q, const Vector3D& x, const Vector3D& y, const Vector3D& z
)
    : mQ(Q), mX(x), mY(y), mZ(z) {
}

PrimitivePtr CuboidGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

PrimitivePtr CuboidGeo::buildImplicitPrimitive() const {
    return std::make_unique<CuboidPrim>(mQ, mX, mY, mZ);
}

// TODO: normals and texture coordinates
PrimitivePtr CuboidGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    m.addVertex(VertexP{mQ});
    m.addVertex(VertexP{mQ + mX});
    m.addVertex(VertexP{mQ + mY});
    m.addVertex(VertexP{mQ + mX + mY});

    m.addVertex(VertexP{mQ + mZ});
    m.addVertex(VertexP{mQ + mZ + mX});
    m.addVertex(VertexP{mQ + mZ + mY});
    m.addVertex(VertexP{mQ + mZ + mX + mY});

    // Front face (-Z).
    m.addTriangle(0, 2, 3);
    m.addTriangle(0, 3, 1);

    // Back face (+Z).
    m.addTriangle(4, 5, 7);
    m.addTriangle(4, 7, 6);

    // Left face (-X).
    m.addTriangle(4, 6, 2);
    m.addTriangle(4, 2, 0);

    // Right face (+X).
    m.addTriangle(1, 3, 7);
    m.addTriangle(1, 7, 5);

    // Top face (+Y).
    m.addTriangle(2, 6, 7);
    m.addTriangle(2, 7, 3);

    // Bottom face (-Y).
    m.addTriangle(4, 0, 1);
    m.addTriangle(4, 1, 5);

    return std::make_unique<MeshPrim>(m);
}
