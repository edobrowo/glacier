#pragma once

#include <string>

#include "transform.hpp"
#include "util/common.hpp"

class SceneNode;

using SceneNodePtr = std::unique_ptr<SceneNode>;

/// @brief Generic scene node. All scene nodes have an ID, name, and associated
/// local Transform.
class SceneNode {
public:
    enum class Kind {
        Null = 0,
        Geometry,
    };

    explicit SceneNode(const char* name);
    ~SceneNode() = default;

    /// @brief Constructs a SceneNodePtr.
    static SceneNodePtr make(const char* name);

    /// @brief Retrieves the ID of the node.
    u64 id() const;

    /// @brief Retrieves the kind of the node.
    Kind kind() const;

    /// @brief Retrieves a mutable reference to the node's transform.
    Transform& transform();

    /// @brief Retrieves a constant reference to the node's children.
    const std::vector<SceneNodePtr>& children() const;

    /// @brief Adds a child node to the node. Transfers ownership of the node
    /// pointer to this node.
    void addChild(SceneNodePtr&& child);

public:
    std::string mName;

protected:
    static u64 sNextId;

    u64 mId;
    Kind mKind;
    Transform mTransform;
    std::vector<SceneNodePtr> mChildren;
};
