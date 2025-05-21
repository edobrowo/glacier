#pragma once

#include "math/normal.hpp"
#include "math/point.hpp"
#include "math/vector.hpp"
#include "util/format.hpp"

/// @brief Vertex with position, 2D texture, and surface normal attributes.
struct Vertex {
    Point3D p;
    Normal3D n;
    Point2D uv;
};

template <>
struct FormatWriter<Vertex> {
    static void write(const Vertex& v, StringBuffer& sb) {
        sb.append("V(");
        sb.appendFormat("p={}, n={}, uv={}", v.p, v.n, v.uv);
        sb.putSafe(')');
    }
};
