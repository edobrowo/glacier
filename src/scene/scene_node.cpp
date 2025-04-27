#include "scene_node.hpp"

u64 SceneNode::sNextId = 0;

SceneNodePtr SceneNode::make(const char* name) {
    return std::make_unique<SceneNode>(name);
}

SceneNode::SceneNode(const char* name)
    : mName(name),
      mId(sNextId),
      mKind(SceneNode::Kind::Null),
      mTransform(),
      mChildren() {
    ++sNextId;
}

u64 SceneNode::id() const {
    return mId;
}

SceneNode::Kind SceneNode::kind() const {
    return mKind;
}

Transform& SceneNode::transform() {
    return mTransform;
}

const std::vector<SceneNodePtr>& SceneNode::children() const {
    return mChildren;
}

void SceneNode::addChild(SceneNodePtr&& child) {
    mChildren.push_back(std::move(child));
}
