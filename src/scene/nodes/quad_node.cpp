#include "quad_node.hpp"

#include "geometry/quad.hpp"
#include "render/primitive/mesh_prim.hpp"
#include "render/primitive/quad_prim.hpp"

QuadNode::QuadNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Quad>(), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

QuadNode::QuadNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<Quad>(Q, u, v), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

PrimitivePtr QuadNode::buildPrimitive() const {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh: {
        return std::make_unique<MeshPrim>(mGeometry->mesh());
    }
    case Primitive::Kind::Implicit: {
        const Quad* disk = static_cast<Quad*>(mGeometry.get());
        return std::make_unique<QuadPrim>(disk->Q, disk->x, disk->y);
    }
    default:
        unreachable;
    }
}
