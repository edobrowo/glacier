#include "bezier_patch_node.hpp"

#include "geometry/bezier_patch_geo.hpp"
#include "primitive/mesh.hpp"

BezierPatchNode::BezierPatchNode(
    const char* name,
    MaterialPtr material,
    const std::array<Point3D, 16>& control_points,
    const Size u_div,
    const Size v_div
)
    : GeometryNode(name, std::make_unique<Mesh>(), material) {
    mPrimitive = BezierPatchGeo(control_points).toMeshPrimitive(u_div, v_div);
}
