#include "cuboid_node.hpp"

#include "geometry/cuboid.hpp"
#include "render/primitive/cuboid_prim.hpp"
#include "render/primitive/mesh_prim.hpp"

CuboidNode::CuboidNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Cuboid>(), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
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
    mPrimitiveKind = Primitive::Kind::Implicit;
}

PrimitivePtr CuboidNode::buildPrimitive() const {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh: {
        return std::make_unique<MeshPrim>(mGeometry->mesh());
    }
    case Primitive::Kind::Implicit: {
        const Cuboid* cuboid = static_cast<Cuboid*>(mGeometry.get());
        return std::make_unique<CuboidPrim>(
            cuboid->Q, cuboid->x, cuboid->y, cuboid->z
        );
    }
    default:
        unreachable;
    }
}
