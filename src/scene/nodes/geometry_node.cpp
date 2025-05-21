#include "geometry_node.hpp"

GeometryNode::GeometryNode(
    const char* name, GeometryPtr&& geometry, MaterialPtr material
)
    : SceneNode(name),
      mGeometry(std::move(geometry)),
      mMaterial(material),
      mPrimitive(nullptr),
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

const PrimitivePtr& GeometryNode::primitive() const {
    return mPrimitive;
}
