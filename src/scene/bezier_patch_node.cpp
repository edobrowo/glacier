#include "bezier_patch_node.hpp"

#include "primitive/mesh.hpp"

BezierPatchNode::BezierPatchNode(
    const char* name,
    MaterialPtr material,
    const std::array<Point3D, 16>& control_points
)
    : GeometryNode(
          name, std::make_unique<BezierPatchGeo>(control_points), material
      ) {
}

void BezierPatchNode::setDivisions(const Size u_div, const Size v_div) {
    BezierPatchGeo* geo = static_cast<BezierPatchGeo*>(mGeometry.get());
    geo->setDivisions(u_div, v_div);
}
