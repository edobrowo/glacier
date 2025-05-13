#include "scene_node.hpp"

u64 SceneNode::sNextId = 0;

SceneNode::SceneNode(const char* name)
    : name(name),
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

std::vector<SceneNodePtr>& SceneNode::childrenMutable() {
    return mChildren;
}

void SceneNode::addChild(SceneNodePtr&& child) {
    mChildren.push_back(std::move(child));
}
