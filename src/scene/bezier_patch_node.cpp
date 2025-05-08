#include "bezier_patch_node.hpp"

#include "primitive/mesh.hpp"

BezierPatchNode::BezierPatchNode(
    const char* name,
    MaterialPtr material,
    const std::array<Point3D, 16>& control_points,
    const Size u_div,
    const Size v_div
)
    : GeometryNode(name, std::make_unique<Mesh>(), material) {
    const IndexedMesh<VertexP> mesh =
        BezierPatch(control_points).mesh<VertexP>(u_div, v_div);
    mPrimitive = std::make_unique<Mesh>(mesh);
}
