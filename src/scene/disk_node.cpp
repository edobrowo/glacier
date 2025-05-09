#include "disk_node.hpp"

#include "geometry/disk_geo.hpp"

DiskNode::DiskNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<DiskGeo>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

DiskNode::DiskNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<DiskGeo>(Q, u, v), material) {
    mPrimKind = Primitive::Kind::Implicit;
}
