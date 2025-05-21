#include "triangle_node.hpp"

#include "geometry/triangle.hpp"
#include "render/primitive/mesh_prim.hpp"
#include "render/primitive/triangle_prim.hpp"

TriangleNode::TriangleNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Triangle>(), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

TriangleNode::TriangleNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<Triangle>(Q, u, v), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

TriangleNode::~TriangleNode() {
}

void TriangleNode::buildPrimitive() {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh: {
        mPrimitive = std::make_unique<MeshPrim>(mGeometry->mesh());
        break;
    }
    case Primitive::Kind::Implicit: {
        const Triangle* tri = static_cast<Triangle*>(mGeometry.get());
        mPrimitive = std::make_unique<TrianglePrim>(tri->Q, tri->x, tri->y);
        break;
    }
    default:
        unimplemented;
    }
}
