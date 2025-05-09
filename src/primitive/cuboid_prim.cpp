#include "cuboid_prim.hpp"

CuboidPrim::CuboidPrim(
    const Point3D& o,
    const Vector3D& x,
    const Vector3D& y,
    const Vector3D& z
)
    : mQuads({// Front face.
              QuadPrim(o, y, x),

              // Back face.
              QuadPrim(o + z, x, y),

              // Left face.
              QuadPrim(o, z, y),

              // Right face.
              QuadPrim(o + x, y, z),

              // Bottom face.
              QuadPrim(o, x, z),

              // Top face.
              QuadPrim(o + y, z, x)

      }) {
    mKind = Kind::Implicit;
}

Option<Intersect> CuboidPrim::intersect(const Ray& ray, const Interval& bounds)
    const {
    Option<Intersect> closest = std::nullopt;
    for (const QuadPrim& quad : mQuads) {
        if (const Option<Intersect> i = quad.intersect(ray, bounds)) {
            if (!closest || i->t < closest->t)
                closest = i;
        }
    }
    return closest;
}
