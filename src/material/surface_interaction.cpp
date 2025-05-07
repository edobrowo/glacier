#include "surface_interaction.hpp"

SurfaceInteraction::SurfaceInteraction(
    const Intersect& intersect, MaterialPtr material
)
    : intersect(intersect), material(material) {
}

SurfaceInteraction::SurfaceInteraction(const SurfaceInteraction& other)
    : intersect(other.intersect), material(other.material) {
}

SurfaceInteraction SurfaceInteraction::operator=(const SurfaceInteraction& other
) {
    intersect = other.intersect;
    material = other.material;

    return *this;
}

SurfaceInteraction::SurfaceInteraction(SurfaceInteraction&& other)
    : intersect(std::move(other.intersect)),
      material(std::move(other.material)) {
}

SurfaceInteraction SurfaceInteraction::operator=(SurfaceInteraction&& other) {
    intersect = std::move(other.intersect);
    material = std::move(other.material);

    return *this;
}
