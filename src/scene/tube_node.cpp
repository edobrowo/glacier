#include "tube_node.hpp"

#include "primitive/tube.hpp"

TubeNode::TubeNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Tube>(), material) {
}

TubeNode::TubeNode(
    const char* name,
    MaterialPtr material,
    const Point3D& base,
    const f64 radius,
    const f64 height
)
    : GeometryNode(
          name, std::make_unique<Tube>(base, radius, height), material
      ) {
}
