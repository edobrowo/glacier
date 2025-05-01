#pragma once

#include "math/vector.hpp"
#include "primitive/intersect.hpp"
#include "scatter_record.hpp"

/// @brief Material base class. Defines how rays are scattered or transmitted
/// upon intersection with the geometry which the material is applied to.
class Material {
public:
    enum class Kind {
        Null = 0,
        Lambertian,
        Specular,
        MirrorSpecular,
    };

    Material();
    virtual ~Material();

    /// @brief Scatters the incident ray according to local surface geometry and
    /// material appearance properties.
    virtual ScatterRecord scatter(const Ray& incident,
                                  const Intersect& intersect) const = 0;

    /// @brief Retrieves the kind of the material.
    Kind kind() const;

protected:
    Kind mKind;
};

using MaterialPtr = std::shared_ptr<Material>;
using MaterialTempPtr = const Material*;
