#include "geometry_node.hpp"

GeometryNode::GeometryNode(const char* name,
                           PrimitivePtr&& primitive,
                           MaterialPtr&& material)
    : SceneNode(name),
      mPrimitive(std::move(primitive)),
      mMaterial(std::move(material)) {
    mKind = Kind::Geometry;
}

GeometryNodePtr GeometryNode::make(const char* name,
                                   PrimitivePtr&& primitive,
                                   MaterialPtr&& material) {
    return std::make_unique<GeometryNode>(
        name, std::move(primitive), std::move(material));
}

const PrimitivePtr& GeometryNode::primitive() const {
    return mPrimitive;
}

const MaterialPtr& GeometryNode::material() const {
    return mMaterial;
}
