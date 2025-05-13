#include "disk_geo.hpp"

#include "indexed_mesh.hpp"
#include "math/constants.hpp"
#include "primitive/disk_prim.hpp"
#include "primitive/mesh_prim.hpp"

DiskGeo::DiskGeo()
    : mQ(Point3D(0, 0, 0.0)),
      mU(Vector3D(0.5, 0.0, 0.0)),
      mV(Vector3D(0.0, 0.5, 0.0)) {
}

DiskGeo::DiskGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v)
    : mQ(Q), mU(u), mV(v) {
}

PrimitivePtr DiskGeo::buildPrimitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

void DiskGeo::setDivisions(const Size div) {
    assertm(div > 0, "div must be greater than 0");

    mDiv = div;
}

PrimitivePtr DiskGeo::buildImplicitPrimitive() const {
    return std::make_unique<DiskPrim>(mQ, mU, mV);
}

// TODO: normals and texture coordinates
PrimitivePtr DiskGeo::buildMeshPrimitive() const {
    IndexedMesh<VertexP> m;

    const Point3D& center = mQ;
    m.addVertex(VertexP{center});

    const Index a = 0;

    for (Index ui = 0; ui <= mDiv; ++ui) {
        const f64 u = static_cast<f64>(ui) / mDiv;
        const f64 theta = 2.0 * math::pi<f64>() * u;

        const Point3D p = mQ + std::cos(theta) * mU + std::sin(theta) * mV;
        m.addVertex(VertexP{p});

        if (ui < mDiv) {
            const Index b = ui + 1;
            const Index c = ui + 2;

            m.addTriangle(a, b, c);
        }
    }

    return std::make_unique<MeshPrim>(m);
}
