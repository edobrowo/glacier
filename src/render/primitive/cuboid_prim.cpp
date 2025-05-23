#include "cuboid_prim.hpp"

CuboidPrim::CuboidPrim(
    const Point3D& o,
    const Vector3D& x,
    const Vector3D& y,
    const Vector3D& z
)
    : mQuads(
          {// Front face.
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

          }
      ) {
    mKind = Kind::Implicit;

    // clang-format off
    std::array<Point3D, 8> corners = {
        o,
        o + x,
        o + y,
        o + x + y,
        o + z,
        o + z + x,
        o + z + y,
        o + z + x + y
    };
    // clang-format on

    Point3D min = corners.front();
    Point3D max = corners.front();

    for (Index i = 1; i < corners.size(); ++i) {
        min = min.min(corners[i]);
        max = max.max(corners[i]);
    }

    mBbox = AABB(min, max);
}

Option<SurfaceInteraction> CuboidPrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    Option<SurfaceInteraction> closest = std::nullopt;
    for (const QuadPrim& quad : mQuads) {
        if (const Option<SurfaceInteraction> i = quad.intersect(ray, bounds)) {
            if (!closest || i->t < closest->t)
                closest = i;
        }
    }
    return closest;
}
