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

    /// @brief Builds all primitives in the scene.
    void buildPrimitives();

private:
    /// @brief Recursively builds all primitives in the scene.
    void buildPrimitivesRecursive(SceneNodePtr& node);

    SceneNodePtr mRoot;
};
