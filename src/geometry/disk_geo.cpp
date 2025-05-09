#include "disk_geo.hpp"

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "primitive/disk.hpp"
#include "primitive/mesh.hpp"

DiskGeo::DiskGeo()
    : mQ(Point3D(0, 0, 0.0)),
      mU(Vector3D(1.0, 0.0, 0.0)),
      mV(Vector3D(0.0, 1.0, 0.0)) {
}

DiskGeo::DiskGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v)
    : mQ(Q), mU(u), mV(v) {
}

PrimitivePtr DiskGeo::primitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

PrimitivePtr DiskGeo::buildImplicitPrimitive() const {
    return std::make_unique<Disk>(mQ, mU, mV);
}

// TODO: normals and texture coordinates
PrimitivePtr DiskGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    // TODO:

    return std::make_unique<Mesh>(m);
}
