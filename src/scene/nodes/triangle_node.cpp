#include "triangle_node.hpp"

#include "geometry/triangle_geo.hpp"

TriangleNode::TriangleNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<TriangleGeo>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

TriangleNode::TriangleNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<TriangleGeo>(Q, u, v), material) {
    mPrimKind = Primitive::Kind::Implicit;
}
