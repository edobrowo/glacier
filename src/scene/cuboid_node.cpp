#include "cuboid_node.hpp"

#include "primitive/cuboid.hpp"

CuboidNode::CuboidNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Cuboid>(), material) {
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
}
