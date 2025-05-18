#include "cuboid_node.hpp"

#include "geometry/cuboid_geo.hpp"

CuboidNode::CuboidNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<CuboidGeo>(), material) {
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
    : GeometryNode(name, std::make_unique<CuboidGeo>(Q, x, y, z), material) {
    mPrimKind = Primitive::Kind::Implicit;
}
