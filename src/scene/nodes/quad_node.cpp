#include "quad_node.hpp"

#include "geometry/quad.hpp"
#include "render/primitive/mesh_prim.hpp"
#include "render/primitive/quad_prim.hpp"

QuadNode::QuadNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Quad>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

QuadNode::QuadNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<Quad>(Q, u, v), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

QuadNode::~QuadNode() {
}

void QuadNode::buildPrimitive() {
    switch (mPrimKind) {
    case Primitive::Kind::Mesh: {
        mPrimitive = std::make_unique<MeshPrim>(mGeometry->mesh());
        break;
    }
    case Primitive::Kind::Implicit: {
        const Quad* disk = static_cast<Quad*>(mGeometry.get());
        mPrimitive = std::make_unique<QuadPrim>(disk->Q, disk->x, disk->y);
        break;
    }
    default:
        unreachable;
    }
}
