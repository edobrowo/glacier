#include "scene_graph.hpp"

#include "nodes/geometry_node.hpp"

SceneGraph::SceneGraph() : mRoot(std::make_unique<SceneNode>("root")) {
}

const SceneNodePtr& SceneGraph::root() const {
    return mRoot;
}

SceneNodePtr& SceneGraph::rootMutable() {
    return mRoot;
}
