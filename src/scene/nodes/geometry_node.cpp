#include "geometry_node.hpp"

#include "render/primitive/mesh_prim.hpp"

GeometryNode::GeometryNode(
    const char* name, GeometryPtr&& geometry, MaterialPtr material
)
    : SceneNode(name),
      mGeometry(std::move(geometry)),
      mMaterial(material),
      mPrimitiveKind(Primitive::Kind::Mesh) {
    mKind = Kind::Geometry;
}

GeometryNode::~GeometryNode() {
}

const GeometryPtr& GeometryNode::geometry() const {
    return mGeometry;
}

const MaterialPtr& GeometryNode::material() const {
    return mMaterial;
}

Primitive::Kind GeometryNode::primitiveKind() const {
    return mPrimitiveKind;
}

void GeometryNode::setPrimitiveKind(const Primitive::Kind kind) {
    mPrimitiveKind = kind;
}

PrimitivePtr GeometryNode::buildPrimitive() const {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh:
        return std::make_unique<MeshPrim>(mGeometry->mesh());
    default:
        unreachable;
    }
}
