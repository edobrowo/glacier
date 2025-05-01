#pragma once

#include "material.hpp"

class MirrorSpecular : public Material {
public:
    MirrorSpecular(const Vector3D& color);
    ~MirrorSpecular() = default;

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a mirror reflector.
    virtual ScatterRecord scatter(const Ray& incident,
                                  const Intersect& intersect) const override;

private:
    Vector3D mColor;
};
