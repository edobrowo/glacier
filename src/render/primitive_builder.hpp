#pragma once

#include "common/prelude.hpp"
#include "primitive/cuboid_prim.hpp"
#include "primitive/disk_prim.hpp"
#include "primitive/mesh_prim.hpp"
#include "primitive/quad_prim.hpp"
#include "primitive/sphere_prim.hpp"
#include "primitive/triangle_prim.hpp"
#include "primitive/tube_prim.hpp"
#include "scene/nodes/geometry_node.hpp"

// CuboidNode.
#include "common/geometry/cuboid.hpp"
#include "scene/nodes/cuboid_node.hpp"

// DiskNode.
#include "common/geometry/disk.hpp"
#include "scene/nodes/disk_node.hpp"

// QuadNode.
#include "common/geometry/quad.hpp"
#include "scene/nodes/quad_node.hpp"

// SphereNode.
#include "common/geometry/sphere.hpp"
#include "scene/nodes/sphere_node.hpp"

// TriangleNode.
#include "common/geometry/triangle.hpp"
#include "scene/nodes/triangle_node.hpp"

// TubeNode.
#include "common/geometry/tube.hpp"
#include "scene/nodes/tube_node.hpp"

/// @brief Concept asserting a node is geometric.
template <typename T>
concept Geometric = std::derived_from<T, GeometryNode>;

/// @brief Primitive builder template.
template <Geometric T>
struct PrimitiveBuilder;

/// @brief Concept-based interface used to render a GeometryNode.
template <typename T>
concept Renderable = requires(T node) {
    { PrimitiveBuilder<T>::build(node) } -> std::same_as<PrimitivePtr>;
};

/// @brief Primary implementation for primitive construction. All Geometry
/// subclasses must provide a mesh implementation.
template <Geometric T>
struct PrimitiveBuilder {
    static PrimitivePtr build(const T& node) {
        if (node.primitiveKind() == Primitive::Kind::Mesh)
            return std::make_unique<MeshPrim>(node.geometry()->mesh());
        else
            unreachable;
    }
};

/// @brief CuboidNode specialization.
template <>
struct PrimitiveBuilder<CuboidNode> {
    static PrimitivePtr build(const CuboidNode& node) {
        const Cuboid* cuboid = static_cast<Cuboid*>(node.geometry().get());

        switch (node.primitiveKind()) {
        case Primitive::Kind::Mesh:
            return std::make_unique<MeshPrim>(cuboid->mesh());
        case Primitive::Kind::Implicit:
            return std::make_unique<CuboidPrim>(
                cuboid->Q, cuboid->x, cuboid->y, cuboid->z
            );
        default:
            unimplemented;
        }
    }
};

/// @brief DiskNode specialization.
template <>
struct PrimitiveBuilder<DiskNode> {
    static PrimitivePtr build(const DiskNode& node) {
        const Disk* disk = static_cast<Disk*>(node.geometry().get());

        switch (node.primitiveKind()) {
        case Primitive::Kind::Mesh:
            return std::make_unique<MeshPrim>(disk->mesh());
        case Primitive::Kind::Implicit:
            return std::make_unique<DiskPrim>(disk->Q, disk->x, disk->y);
        default:
            unreachable;
        }
    }
};

/// @brief QuadNode specialization.
template <>
struct PrimitiveBuilder<QuadNode> {
    static PrimitivePtr build(const QuadNode& node) {
        const Quad* disk = static_cast<Quad*>(node.geometry().get());

        switch (node.primitiveKind()) {
        case Primitive::Kind::Mesh:
            return std::make_unique<MeshPrim>(disk->mesh());
        case Primitive::Kind::Implicit:
            return std::make_unique<QuadPrim>(disk->Q, disk->x, disk->y);
        default:
            unreachable;
        }
    }
};

/// @brief SphereNode specialization.
template <>
struct PrimitiveBuilder<SphereNode> {
    static PrimitivePtr build(const SphereNode& node) {
        const Sphere* sphere = static_cast<Sphere*>(node.geometry().get());

        switch (node.primitiveKind()) {
        case Primitive::Kind::Mesh:
            return std::make_unique<MeshPrim>(sphere->mesh());
        case Primitive::Kind::Implicit:
            return std::make_unique<SpherePrim>(
                sphere->center(), sphere->radius()
            );
        default:
            unimplemented;
        }
    }
};

/// @brief TriangleNode specialization.
template <>
struct PrimitiveBuilder<TriangleNode> {
    static PrimitivePtr build(const TriangleNode& node) {
        const Triangle* tri = static_cast<Triangle*>(node.geometry().get());

        switch (node.primitiveKind()) {
        case Primitive::Kind::Mesh:
            return std::make_unique<MeshPrim>(tri->mesh());
        case Primitive::Kind::Implicit:
            return std::make_unique<TrianglePrim>(tri->Q, tri->x, tri->y);
        default:
            unimplemented;
        }
    }
};

/// @brief TubeNode specialization.
template <>
struct PrimitiveBuilder<TubeNode> {
    static PrimitivePtr build(const TubeNode& node) {
        const Tube* tube = static_cast<Tube*>(node.geometry().get());

        switch (node.primitiveKind()) {
        case Primitive::Kind::Mesh:
            return std::make_unique<MeshPrim>(tube->mesh());
        case Primitive::Kind::Implicit:
            return std::make_unique<TubePrim>(
                tube->center(),
                tube->radius(),
                tube->height(),
                tube->topCapVisible(),
                tube->bottomCapVisible()
            );
        default:
            unimplemented;
        }
    }
};
