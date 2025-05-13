#include "nurbs_node.hpp"

#include "geometry/nurbs_geo.hpp"

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
          std::make_unique<NURBSGeo>(
              points, weights, u_knot_vector, v_knot_vector
          ),
          material
      ) {
}

void NURBSNode::setDivisions(const Size u_div, const Size v_div) {
    NURBSGeo* geo = static_cast<NURBSGeo*>(mGeometry.get());
    geo->setDivisions(u_div, v_div);
}
