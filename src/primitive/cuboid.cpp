#include "cuboid.hpp"

Cuboid::Cuboid(const Point3D& o,
               const Vector3D& x,
               const Vector3D& y,
               const Vector3D& z)
    : mQuads({// Front face.
              Quad(o, y, x),

              // Back face.
              Quad(o + z, x, y),

              // Left face.
              Quad(o, z, y),

              // Right face.
              Quad(o + x, y, z),

              // Bottom face.
              Quad(o, x, z),

              // Top face.
              Quad(o + y, z, x)

      }) {
}

Option<Intersect> Cuboid::intersect(const Ray& ray,
                                    const Interval& bounds) const {
    Option<Intersect> closest = std::nullopt;
    for (const Quad& quad : mQuads) {
        if (const Option<Intersect> i = quad.intersect(ray, bounds)) {
            if (!closest || i->t < closest->t)
                closest = i;
        }
    }
    return closest;
}
