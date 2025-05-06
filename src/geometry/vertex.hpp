#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "util/format.hpp"

struct VertexP {
    Point3D position;
};

struct VertexPT2 {
    Point3D position;
    Point2D texture;
};

struct VertexPT3 {
    Point3D position;
    Point3D texture;
};

struct VertexPN {
    Point3D position;
    Vector3D normal;
};

struct VertexPT2N {
    Point3D position;
    Point2D texture;
    Vector3D normal;
};

struct VertexPT3N {
    Point3D position;
    Point3D texture;
    Vector3D normal;
};

template <>
struct FormatWriter<VertexP> {
    static void write(const VertexP& v, StringBuffer& sb) {
        sb.append("V(", 2);
        sb.appendFormat("p={}", v.position);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<VertexPT2> {
    static void write(const VertexPT2& v, StringBuffer& sb) {
        sb.append("V(", 2);
        sb.appendFormat("p={}, t={}", v.position, v.texture);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<VertexPT3> {
    static void write(const VertexPT3& v, StringBuffer& sb) {
        sb.append("V(", 2);
        sb.appendFormat("p={}, t={}", v.position, v.texture);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<VertexPN> {
    static void write(const VertexPN& v, StringBuffer& sb) {
        sb.append("V(", 2);
        sb.appendFormat("p={}, n={}", v.position, v.normal);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<VertexPT2N> {
    static void write(const VertexPT2N& v, StringBuffer& sb) {
        sb.append("V(", 2);
        sb.appendFormat("p={}, t={}, n={}", v.position, v.texture, v.normal);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<VertexPT3N> {
    static void write(const VertexPT3N& v, StringBuffer& sb) {
        sb.append("V(", 2);
        sb.appendFormat("p={}, t={}, n={}", v.position, v.texture, v.normal);
        sb.putSafe(')');
    }
};
