#include "disk_node.hpp"

#include "primitive/disk.hpp"

DiskNode::DiskNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Disk>(), material) {
}

DiskNode::DiskNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<Disk>(Q, u, v), material) {
}
