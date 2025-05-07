#include "geometry_node.hpp"

GeometryNode::GeometryNode(
    const char* name, PrimitivePtr&& primitive, MaterialPtr material
)
    : SceneNode(name), mPrimitive(std::move(primitive)), mMaterial(material) {
    mKind = Kind::Geometry;
}

const PrimitivePtr& GeometryNode::primitive() const {
    return mPrimitive;
}

const MaterialPtr& GeometryNode::material() const {
    return mMaterial;
}
