#pragma once

#include "common/math/interval.hpp"
#include "common/math/ray.hpp"
#include "common/prelude.hpp"
#include "common/util/image.hpp"
#include "render/camera.hpp"
#include "render/config.hpp"
#include "render/material/surface_interaction.hpp"
#include "render/primitive/primitive.hpp"
#include "scene/scene_graph.hpp"

/// @brief Main path tracer routine class. Performs ray generation, intersection
/// testing, and pixel shading.
class Pathtracer {
public:
    Pathtracer(const SceneGraph& scene, const Camera& camera);
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

    /// @brief Background color given a ray.
    Vector3D background(const Ray& ray) const;

    std::vector<PrimitivePtr> mPrimitives;
    const Camera& mCamera;
};
