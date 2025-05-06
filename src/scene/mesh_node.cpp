#include "mesh_node.hpp"

#include "geometry/indexed_mesh.hpp"
#include "geometry/obj_parser.hpp"
#include "primitive/mesh.hpp"
#include "util/files.hpp"

MeshNode::MeshNode(const char* name, MaterialPtr material, const char* path)
    : GeometryNode(name, nullptr, material) {
    const std::string& raw = files::read_to_string(path);

    const ObjData data = ObjParser().parse(raw);

    const ObjObject& obj = data.objects.front();

    const IndexedMesh<VertexP> mesh(obj);

    mPrimitive = std::make_unique<Mesh>(mesh);
}
