#include "quad_node.hpp"

#include "geometry/quad_geo.hpp"

QuadNode::QuadNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<QuadGeo>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

QuadNode::QuadNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<QuadGeo>(Q, u, v), material) {
    mPrimKind = Primitive::Kind::Implicit;
}
