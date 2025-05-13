#pragma once

#include "camera.hpp"
#include "config.hpp"
#include "image.hpp"
#include "material/surface_interaction.hpp"
#include "math/interval.hpp"
#include "math/ray.hpp"
#include "primitive/primitive.hpp"
#include "scene/scene_graph.hpp"
#include "util/common.hpp"

/// @brief Main path tracer routine class. Performs ray generation, intersection
/// testing, and pixel shading.
class Pathtracer {
public:
    Pathtracer(SceneGraph& scene, const Camera& camera);
    ~Pathtracer() = default;

    /// @brief Renders the scene from the view of the camera.
    Image render() const;

    Config config;

private:
    /// @brief Generates a ray from the camera origin to the given pixel
    /// coordinates in worldspace.
    Ray generate(const Index px, const Index py) const;

    /// @brief Recursively determines the pixel color.
    Vector3D shadeRecursive(const Ray& ray, const Size depth) const;

    /// @brief Finds the closest intersect of the ray with the scene.
    Option<SurfaceInteraction> intersect(const Ray& ray) const;

    /// @brief Recursively finds the closest intersect.
    Option<SurfaceInteraction> intersectRecursive(
        const SceneNodePtr& node, const Ray& ray, const Interval& bounds
    ) const;

    /// @brief Background color given a ray.
    Vector3D background(const Ray& ray) const;

    SceneGraph& mScene;
    const Camera& mCamera;
};
