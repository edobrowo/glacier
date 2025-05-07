#include "quad_node.hpp"

#include "primitive/quad.hpp"

QuadNode::QuadNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Quad>(), material) {
}

QuadNode::QuadNode(
    const char* name,
    MaterialPtr material,
    const Point3D& Q,
    const Vector3D& u,
    const Vector3D& v
)
    : GeometryNode(name, std::make_unique<Quad>(Q, u, v), material) {
}
