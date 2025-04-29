#include "sphere_node.hpp"

#include "primitive/sphere.hpp"

SphereNode::SphereNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Sphere>(), material) {
}
