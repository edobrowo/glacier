#include "disk_node.hpp"

#include "geometry/disk.hpp"
#include "render/primitive/disk_prim.hpp"
#include "render/primitive/mesh_prim.hpp"

DiskNode::DiskNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Disk>(), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

DiskNode::DiskNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<Disk>(Q, u, v), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

PrimitivePtr DiskNode::buildPrimitive() const {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh: {
        return std::make_unique<MeshPrim>(mGeometry->mesh());
    }
    case Primitive::Kind::Implicit: {
        const Disk* disk = static_cast<Disk*>(mGeometry.get());
        return std::make_unique<DiskPrim>(disk->Q, disk->x, disk->y);
    }
    default:
        unreachable;
    }
}

void DiskNode::setDivisions(const Size div) {
    Disk* geo = static_cast<Disk*>(mGeometry.get());
    geo->setDivisions(div);
}
