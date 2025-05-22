#pragma once

#include "nodes/scene_node.hpp"

/// @brief Hierarchical scene graph class.
class SceneGraph {
public:
    SceneGraph();
    ~SceneGraph() = default;

    /// @brief Retrieves a constant reference to the root node.
    const SceneNodePtr& root() const;

    /// @brief Retrieves a mutable reference to the root node.
    SceneNodePtr& rootMutable();

private:
    SceneNodePtr mRoot;
};
