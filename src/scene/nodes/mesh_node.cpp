#include "mesh_node.hpp"

#include "common/util/files.hpp"
#include "common/util/log.hpp"
#include "geometry/mesh.hpp"
#include "geometry/obj_parser.hpp"
#include "geometry/triangle_mesh.hpp"
#include "render/primitive/mesh_prim.hpp"

MeshNode::MeshNode(const char* name, MaterialPtr material, const char* path)
    : GeometryNode(name, nullptr, material) {
    mPrimitiveKind = Primitive::Kind::Mesh;

    const std::string& raw = files::read_to_string(path);

    const ObjData data = ObjParser().parse(raw);

    const ObjObject& obj = data.objects.front();

    const TriangleMesh mesh(obj);

    mGeometry = std::make_unique<Mesh>(mesh);
}

MeshNode::~MeshNode() {
}

void MeshNode::buildPrimitive() {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh: {
        mPrimitive = std::make_unique<MeshPrim>(mGeometry->mesh());
        break;
    }
    default:
        unreachable;
    }
}
