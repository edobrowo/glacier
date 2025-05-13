#include "scene_graph.hpp"

#include "geometry_node.hpp"

SceneGraph::SceneGraph() : mRoot(std::make_unique<SceneNode>("root")) {
}

const SceneNodePtr& SceneGraph::root() const {
    return mRoot;
}

SceneNodePtr& SceneGraph::rootMutable() {
    return mRoot;
}

void SceneGraph::buildPrimitives() {
    buildPrimitivesRecursive(mRoot);
}

void SceneGraph::buildPrimitivesRecursive(SceneNodePtr& node) {
    if (node->kind() == SceneNode::Kind::Geometry) {
        GeometryNode* geo = static_cast<GeometryNode*>(node.get());
        geo->buildPrimitive();
    }

    for (SceneNodePtr& child : node->childrenMutable()) {
        buildPrimitivesRecursive(child);
    }
}
