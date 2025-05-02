#include "quad_node.hpp"

#include "primitive/quad.hpp"

QuadNode::QuadNode(const char* name, MaterialPtr material)
    : GeometryNode(name,
                   std::make_unique<Quad>(Point3D(-0.5, 0.0, -0.5),
                                          Vector3D(1.0, 0.0, 0.0),
                                          Vector3D(0.0, 0.0, 1.0)),
                   material) {
}
