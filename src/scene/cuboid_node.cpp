#include "cuboid_node.hpp"

#include "primitive/cuboid.hpp"

CuboidNode::CuboidNode(const char* name, MaterialPtr material)
    : GeometryNode(name,
                   std::make_unique<Cuboid>(Point3D(-0.5, -0.5, -0.5),
                                            Vector3D(1.0, 0.0, 0.0),
                                            Vector3D(0.0, 1.0, 0.0),
                                            Vector3D(0.0, 0.0, 1.0)),
                   material) {
}

CuboidNode::CuboidNode(const char* name,
                       MaterialPtr material,
                       const Point3D& Q,
                       const Vector3D& x,
                       const Vector3D& y,
                       const Vector3D& z)
    : GeometryNode(name, std::make_unique<Cuboid>(Q, x, y, z), material) {
}
