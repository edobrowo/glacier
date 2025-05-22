#pragma once

#include "material.hpp"

/// @brief Mirror (reflective) material.
class MirrorSpecular : public Material {
public:
    MirrorSpecular(const Vector3D& color);
    ~MirrorSpecular() = default;

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a mirror reflector.
    Option<ScatterRecord> scatter(
        const Ray& incident, const SurfaceInteraction& interaction
    ) const override;

private:
    Vector3D mColor;
};
