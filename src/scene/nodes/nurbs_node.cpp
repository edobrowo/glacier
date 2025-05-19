#include "nurbs_node.hpp"

#include "geometry/nurbs.hpp"
#include "render/primitive/mesh_prim.hpp"

NURBSNode::NURBSNode(
    const char* name,
    MaterialPtr material,
    std::span<const Point3D> points,
    std::span<const f64> weights,
    std::span<const f64> u_knot_vector,
    std::span<const f64> v_knot_vector
)
    : GeometryNode(
          name,
          std::make_unique<NURBS>(
              points, weights, u_knot_vector, v_knot_vector
          ),
          material
      ) {
}

NURBSNode::~NURBSNode() {
}

void NURBSNode::buildPrimitive() {
    switch (mPrimKind) {
    case Primitive::Kind::Mesh: {
        mPrimitive = std::make_unique<MeshPrim>(mGeometry->mesh());
        break;
    }
    default:
        unreachable;
    }
}

void NURBSNode::setDivisions(const Size u_div, const Size v_div) {
    NURBS* geo = static_cast<NURBS*>(mGeometry.get());
    geo->setDivisions(u_div, v_div);
}
