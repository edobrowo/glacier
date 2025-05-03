#include "triangle_node.hpp"

#include "primitive/triangle.hpp"

TriangleNode::TriangleNode(const char* name, MaterialPtr material)
    : GeometryNode(name,
                   std::make_unique<Triangle>(Point3D(-0.5, 0.0, -0.5),
                                              Vector3D(1.0, 0.0, 0.0),
                                              Vector3D(0.0, 0.0, 1.0)),
                   material) {
}

TriangleNode::TriangleNode(const char* name,
                           MaterialPtr material,
                           const Point3D& Q,
                           const Vector3D& u,
                           const Vector3D& v)
    : GeometryNode(name, std::make_unique<Triangle>(Q, u, v), material) {
}
