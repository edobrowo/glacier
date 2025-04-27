#include "scene_graph.hpp"

SceneGraph::SceneGraph() : mRoot(SceneNode::make("root")) {
}

const SceneNodePtr& SceneGraph::root() const {
    return mRoot;
}

SceneNodePtr& SceneGraph::rootMutable() {
    return mRoot;
}
