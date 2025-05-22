#include "bezier_patch_node.hpp"

#include "geometry/bezier_patch.hpp"
#include "render/primitive/mesh_prim.hpp"

BezierPatchNode::BezierPatchNode(
    const char* name,
    MaterialPtr material,
    const std::array<Point3D, 16>& control_points
)
    : GeometryNode(
          name, std::make_unique<BezierPatch>(control_points), material
      ) {
}

void BezierPatchNode::setDivisions(const Size u_div, const Size v_div) {
    BezierPatch* geo = static_cast<BezierPatch*>(mGeometry.get());
    geo->setDivisions(u_div, v_div);
}
