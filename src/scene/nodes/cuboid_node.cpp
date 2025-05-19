#include "cuboid_node.hpp"

#include "geometry/cuboid.hpp"
#include "render/primitive/cuboid_prim.hpp"
#include "render/primitive/mesh_prim.hpp"

CuboidNode::CuboidNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Cuboid>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

CuboidNode::CuboidNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& x,
    const Vector3D& y,
    const Vector3D& z
)
    : GeometryNode(name, std::make_unique<Cuboid>(Q, x, y, z), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

CuboidNode::~CuboidNode() {
}

void CuboidNode::buildPrimitive() {
    switch (mPrimKind) {
    case Primitive::Kind::Mesh: {
        mPrimitive = std::make_unique<MeshPrim>(mGeometry->mesh());
        break;
    }
    case Primitive::Kind::Implicit: {
        const Cuboid* cuboid = static_cast<Cuboid*>(mGeometry.get());
        mPrimitive = std::make_unique<CuboidPrim>(
            cuboid->Q, cuboid->x, cuboid->y, cuboid->z
        );
        break;
    }
    default:
        unreachable;
    }
}
