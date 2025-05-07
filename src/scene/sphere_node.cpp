#include "sphere_node.hpp"

#include "primitive/sphere.hpp"

SphereNode::SphereNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Sphere>(), material) {
}

SphereNode::SphereNode(
    const char* name,
    MaterialPtr material,
    const Point3D& center,
    const f64 radius
)
    : GeometryNode(name, std::make_unique<Sphere>(center, radius), material) {
}
