#pragma once

#include <string>

#include "common/prelude.hpp"
#include "scene_transform.hpp"

class SceneNode;

using SceneNodePtr = std::shared_ptr<SceneNode>;

/// @brief Generic scene node. All scene nodes have an ID, name, and associated
/// local Transform.
class SceneNode {
public:
    enum class Kind {
        Null = 0,
        Geometry,
    };

    explicit SceneNode(const char* name);
    virtual ~SceneNode();

    /// @brief Retrieves the ID of the node.
    u64 id() const;

    /// @brief Retrieves the kind of the node.
    Kind kind() const;

    /// @brief Retrieves a mutable reference to the node's transform.
    SceneTransform& transform();

    /// @brief Retrieves a constant reference to the node's children.
    const std::vector<SceneNodePtr>& children() const;

    /// @brief Retrieves a mutable reference to the node's children.
    std::vector<SceneNodePtr>& childrenMutable();

    /// @brief Adds a child node to the node.
    void addChild(const SceneNodePtr& child);

public:
    std::string name;

protected:
    static u64 sNextId;

    u64 mId;
    Kind mKind;
    SceneTransform mTransform;
    std::vector<SceneNodePtr> mChildren;
};
