#include "triangle_geo.hpp"

#include "math/constants.hpp"
#include "primitive/triangle_prim.hpp"

TriangleGeo::TriangleGeo()
    : mQ(Point3D(-0.5, -0.5, 0.0)),
      mU(Vector3D(1.0, 0.0, 0.0)),
      mV(Vector3D(0.0, 1.0, 0.0)) {
}

TriangleGeo::TriangleGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v)
    : mQ(Q), mU(u), mV(v) {
}

PrimitivePtr TriangleGeo::primitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Implicit:
        return buildImplicitPrimitive();
    default:
        unreachable;
    }
}

PrimitivePtr TriangleGeo::buildImplicitPrimitive() const {
    return std::make_unique<TrianglePrim>(mQ, mU, mV);
}
