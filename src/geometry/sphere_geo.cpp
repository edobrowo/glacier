#include "sphere_geo.hpp"

SphereGeo::SphereGeo() : mCenter(Point3D::zero()), mRadius(1.0) {
}

SphereGeo::SphereGeo(const Point3D& center, const f64 radius)
    : mCenter(center), mRadius(radius) {
}

PrimitivePtr SphereGeo::toImplicitPrimitive() const {
    return std::make_unique<Sphere>(mCenter, mRadius);
}

// TODO: normals and texture coordinates
PrimitivePtr SphereGeo::toMeshPrimitive(const Size u_div, const Size v_div)
    const {
    assertm(u_div > 0, "u_div must be greater than 0");
    assertm(v_div > 0, "v_div must be greater than 0");

    const Index row = u_div + 1;

    IndexedMesh<VertexP> m;
    for (Index vi = 0; vi <= v_div; ++vi) {
        const f64 v = static_cast<f64>(vi) / v_div;
        const f64 polar = math::pi<f64>() * v;

        for (Index ui = 0; ui <= u_div; ++ui) {
            const f64 u = static_cast<f64>(ui) / u_div;
            const f64 azimuthal = 2.0 * math::pi<f64>() * u;

            const Point3D p(
                std::cos(azimuthal) * std::sin(polar),
                std::cos(polar),
                std::sin(azimuthal) * std::sin(polar)
            );

            m.addVertex(VertexP{p});

            if (ui < u_div && vi < v_div) {
                const Index a = vi * row + ui;
                const Index b = (vi + 1) * row + ui;
                const Index c = vi * row + (ui + 1);
                const Index d = (vi + 1) * row + (ui + 1);

                m.addTriangle(a, c, d);
                m.addTriangle(a, d, b);
            }
        }
    }

    return std::make_unique<Mesh>(m);
}
