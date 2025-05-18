#pragma once

#include "material/material.hpp"

/// @brief Mirror (reflective) material.
class MirrorSpecular : public Material {
public:
    MirrorSpecular(const Vector3D& color);
    virtual ~MirrorSpecular();

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a mirror reflector.
    virtual Option<ScatterRecord> scatter(
        const Ray& incident, const SurfaceInteraction& interaction
    ) const override;

private:
    Vector3D mColor;
};
