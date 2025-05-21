#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "common/math/numeric.hpp"
#include "common/prelude.hpp"
#include "render/camera.hpp"
#include "render/config.hpp"
#include "render/material/dielectric.hpp"
#include "render/material/emissive.hpp"
#include "render/material/lambertian.hpp"
#include "render/material/material.hpp"
#include "render/material/mirror_specular.hpp"
#include "render/material/specular.hpp"
#include "scene/nodes/bezier_patch_node.hpp"
#include "scene/nodes/cuboid_node.hpp"
#include "scene/nodes/disk_node.hpp"
#include "scene/nodes/geometry_node.hpp"
#include "scene/nodes/mesh_node.hpp"
#include "scene/nodes/nurbs_node.hpp"
#include "scene/nodes/quad_node.hpp"
#include "scene/nodes/scene_node.hpp"
#include "scene/nodes/sphere_node.hpp"
#include "scene/nodes/triangle_node.hpp"
#include "scene/nodes/tube_node.hpp"

namespace py = pybind11;

/// @brief Renders the scene from the given virtual camera to an image file at
/// the specified path.
void render(
    const char* path,
    const Camera& camera,
    const SceneNodePtr& root,
    const Config& config
);

PYBIND11_MODULE(glacier, m) {
    m.doc() = "Glacier renderer module.";

    // Transform::Order enum.
    py::enum_<SceneTransform::Order>(m, "TransformOrder")
        .value("SRT", SceneTransform::Order::SRT)
        .value("STR", SceneTransform::Order::STR)
        .value("RST", SceneTransform::Order::RST)
        .value("RTS", SceneTransform::Order::RTS)
        .value("TSR", SceneTransform::Order::TSR)
        .value("TRS", SceneTransform::Order::TRS)
        .export_values();

    // Transform::RotationOrder enum.
    py::enum_<SceneTransform::RotationOrder>(m, "RotationOrder")
        .value("XYZ", SceneTransform::RotationOrder::XYZ)
        .value("XZY", SceneTransform::RotationOrder::XZY)
        .value("YXZ", SceneTransform::RotationOrder::YXZ)
        .value("YZX", SceneTransform::RotationOrder::YZX)
        .value("ZXY", SceneTransform::RotationOrder::ZXY)
        .value("ZYX", SceneTransform::RotationOrder::ZYX)
        .export_values();

    // Transform class.
    py::class_<SceneTransform>(m, "Transform")
        .def(py::init<>())
        .def("s", py::overload_cast<f64, f64, f64>(&SceneTransform::s))
        .def(
            "r",
            [](SceneNode& self, const f64 x, const f64 y, const f64 z) {
                self.transform().r(math::rad(x), math::rad(y), math::rad(z));
            }
        )
        .def("t", py::overload_cast<f64, f64, f64>(&SceneTransform::t))
        .def("set_order", &SceneTransform::setOrder, py::arg("order"))
        .def(
            "set_rotation_order",
            &SceneTransform::setRotationOrder,
            py::arg("rot_order")
        );

    // Material::Kind enum.
    py::enum_<Material::Kind>(m, "MaterialKind")
        .value("Null", Material::Kind::Null)
        .value("Lambertian", Material::Kind::Lambertian)
        .value("Specular", Material::Kind::Specular)
        .value("MirrorSpecular", Material::Kind::MirrorSpecular)
        .value("Dielectric", Material::Kind::Dielectric)
        .value("Emissive", Material::Kind::Emissive)
        .export_values();

    // Material class.
    py::class_<Material, py::smart_holder>(m, "Material")
        .def_property_readonly("kind", &Material::kind);

    // LambertianMaterial class.
    py::class_<Lambertian, Material, py::smart_holder>(m, "LambertianMaterial")
        .def(
            py::init([](std::vector<f64> color) {
                if (color.size() != 3) {
                    throw std::runtime_error(
                        "Lambertian color must be a 3-element list"
                    );
                }
                return new Lambertian(Vector3D(color[0], color[1], color[2]));
            }),
            py::arg("color")
        );

    // SpecularMaterial class.
    py::class_<Specular, Material, py::smart_holder>(m, "SpecularMaterial")
        .def(
            py::init([](std::vector<f64> color, const f64 phong) {
                if (color.size() != 3) {
                    throw std::runtime_error(
                        "Specular color must be a 3-element list"
                    );
                }
                return new Specular(
                    Vector3D(color[0], color[1], color[2]), phong
                );
            }),
            py::arg("color"),
            py::arg("phong")
        );

    // MirrorSpecularMaterial class.
    py::class_<MirrorSpecular, Material, py::smart_holder>(
        m, "MirrorSpecularMaterial"
    )
        .def(
            py::init([](std::vector<f64> color) {
                if (color.size() != 3) {
                    throw std::runtime_error(
                        "MirrorSpecular color must be a 3-element list"
                    );
                }
                return new MirrorSpecular(
                    Vector3D(color[0], color[1], color[2])
                );
            }),
            py::arg("color")
        );

    // DielectricMaterial class.
    py::class_<Dielectric, Material, py::smart_holder>(m, "DielectricMaterial")
        .def(
            py::init([](const f64 eta) { return new Dielectric(eta); }),
            py::arg("eta")
        );

    // EmissiveMaterial class.
    py::class_<Emissive, Material, py::smart_holder>(m, "EmissiveMaterial")
        .def(
            py::init([](std::vector<f64> color) {
                if (color.size() != 3) {
                    throw std::runtime_error(
                        "Emissive color must be a 3-element list"
                    );
                }
                return new Emissive(Vector3D(color[0], color[1], color[2]));
            }),
            py::arg("color")
        );

    // Primitive::Kind enum.
    py::enum_<Primitive::Kind>(m, "PrimitiveKind")
        .value("Mesh", Primitive::Kind::Mesh)
        .value("Implicit", Primitive::Kind::Implicit)
        .export_values();

    // SceneNode::Kind enum.
    py::enum_<SceneNode::Kind>(m, "SceneNodeKind")
        .value("Null", SceneNode::Kind::Null)
        .value("Geometry", SceneNode::Kind::Geometry)
        .export_values();

    // SceneNode class.
    py::class_<SceneNode, py::smart_holder>(m, "SceneNode")
        .def(py::init<const char*>())
        .def("id", &SceneNode::id)
        .def("kind", &SceneNode::kind)
        .def(
            "transform",
            py::overload_cast<>(&SceneNode::transform),
            py::return_value_policy::reference_internal
        )
        .def(
            "s",
            [](SceneNode& self, const f64 x, const f64 y, const f64 z) {
                self.transform().s(x, y, z);
            }
        )
        .def(
            "r",
            [](SceneNode& self, const f64 x, const f64 y, const f64 z) {
                self.transform().r(math::rad(x), math::rad(y), math::rad(z));
            }
        )
        .def(
            "t",
            [](SceneNode& self, const f64 x, const f64 y, const f64 z) {
                self.transform().t(x, y, z);
            }
        )
        .def(
            "s",
            [](SceneNode& self, const f64 a) { self.transform().s(a, a, a); }
        )
        .def(
            "r",
            [](SceneNode& self, const f64 a) {
                const f64 r = math::rad(a);
                self.transform().r(r, r, r);
            }
        )
        .def(
            "t",
            [](SceneNode& self, const f64 a) { self.transform().t(a, a, a); }
        )
        .def("add_child", &SceneNode::addChild, py::arg("child"))
        .def_readwrite("name", &SceneNode::name);

    // GeometryNode class.
    py::class_<GeometryNode, SceneNode, py::smart_holder>(m, "GeometryNode")
        .def("set_primitive_kind", &GeometryNode::setPrimitiveKind);

    // SphereNode class.
    py::class_<SphereNode, GeometryNode, py::smart_holder>(m, "SphereNode")
        .def(
            py::init<const char*, MaterialPtr>(),
            py::arg("name"),
            py::arg("material")
        )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<f64> center,
                        const f64 radius) {
                if (center.size() != 3)
                    throw std::runtime_error("center must be 3-element list");

                if (radius <= 0)
                    throw std::runtime_error("radius must be nonnegative");

                return new SphereNode(
                    name, mat, Point3D(center[0], center[1], center[2]), radius
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("center"),
            py::arg("radius")
        )
        .def(
            "set_divisions",
            &SphereNode::setDivisions,
            py::arg("u_div"),
            py::arg("v_div")
        );

    // QuadNode class.
    py::class_<QuadNode, GeometryNode, py::smart_holder>(m, "QuadNode")
        .def(
            py::init<const char*, MaterialPtr>(),
            py::arg("name"),
            py::arg("material")
        )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<f64> Q,
                        std::vector<f64> u,
                        std::vector<f64> v) {
                if (Q.size() != 3 || u.size() != 3 || v.size() != 3)
                    throw std::runtime_error(
                        "Q, u, and v must be 3-element lists"
                    );

                return new QuadNode(
                    name,
                    mat,
                    Point3D(Q[0], Q[1], Q[2]),
                    Vector3D(u[0], u[1], u[2]),
                    Vector3D(v[0], v[1], v[2])
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("Q"),
            py::arg("u"),
            py::arg("v")
        );

    // TriangleNode class.
    py::class_<TriangleNode, GeometryNode, py::smart_holder>(m, "TriangleNode")
        .def(
            py::init<const char*, MaterialPtr>(),
            py::arg("name"),
            py::arg("material")
        )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<f64> Q,
                        std::vector<f64> u,
                        std::vector<f64> v) {
                if (Q.size() != 3 || u.size() != 3 || v.size() != 3)
                    throw std::runtime_error(
                        "Q, u, and v must be 3-element lists"
                    );

                return new TriangleNode(
                    name,
                    mat,
                    Point3D(Q[0], Q[1], Q[2]),
                    Vector3D(u[0], u[1], u[2]),
                    Vector3D(v[0], v[1], v[2])
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("Q"),
            py::arg("u"),
            py::arg("v")
        );

    // DiskNode class.
    py::class_<DiskNode, GeometryNode, py::smart_holder>(m, "DiskNode")
        .def(
            py::init<const char*, MaterialPtr>(),
            py::arg("name"),
            py::arg("material")
        )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<f64> Q,
                        std::vector<f64> u,
                        std::vector<f64> v) {
                if (Q.size() != 3 || u.size() != 3 || v.size() != 3)
                    throw std::runtime_error(
                        "Q, u, and v must be 3-element lists"
                    );

                return new DiskNode(
                    name,
                    mat,
                    Point3D(Q[0], Q[1], Q[2]),
                    Vector3D(u[0], u[1], u[2]),
                    Vector3D(v[0], v[1], v[2])
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("Q"),
            py::arg("u"),
            py::arg("v")
        )
        .def("set_divisions", &DiskNode::setDivisions, py::arg("div"));

    // Cuboid node.
    py::class_<CuboidNode, GeometryNode, py::smart_holder>(m, "CuboidNode")
        .def(
            py::init<const char*, MaterialPtr>(),
            py::arg("name"),
            py::arg("material")
        )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<f64> Q,
                        std::vector<f64> x,
                        std::vector<f64> y,
                        std::vector<f64> z) {
                if (Q.size() != 3 || x.size() != 3 || y.size() != 3 ||
                    z.size() != 3)
                    throw std::runtime_error(
                        "Q, x, y, and z must be 3-element lists"
                    );

                return new CuboidNode(
                    name,
                    mat,
                    Point3D(Q[0], Q[1], Q[2]),
                    Vector3D(x[0], x[1], x[2]),
                    Vector3D(y[0], y[1], y[2]),
                    Vector3D(z[0], z[1], z[2])
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("Q"),
            py::arg("x"),
            py::arg("y"),
            py::arg("z")
        );

    // Mesh node.
    py::class_<MeshNode, GeometryNode, py::smart_holder>(m, "MeshNode")
        .def(
            py::init<const char*, MaterialPtr, const char*>(),
            py::arg("name"),
            py::arg("material"),
            py::arg("path")
        );

    // Tube node.
    py::class_<TubeNode, GeometryNode, py::smart_holder>(m, "TubeNode")
        .def(
            py::init<const char*, MaterialPtr>(),
            py::arg("name"),
            py::arg("material")
        )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<f64> base,
                        const f64 radius,
                        const f64 height) {
                if (base.size() != 3) {
                    throw std::runtime_error("base must be 3-element lists");
                }
                return new TubeNode(
                    name,
                    mat,
                    Point3D(base[0], base[1], base[2]),
                    radius,
                    height
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("base"),
            py::arg("radius"),
            py::arg("height")
        )
        .def(
            "set_cap_vis",
            &TubeNode::setCapVisibility,
            py::arg("top"),
            py::arg("bottom")
        )
        .def("set_divisions", &TubeNode::setDivisions, py::arg("div"));

    // BezierPatch node.
    py::class_<BezierPatchNode, GeometryNode, py::smart_holder>(
        m, "BezierPatchNode"
    )
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<std::vector<f64>> points) {
                if (points.size() != 16)
                    throw std::runtime_error(
                        "points must be a 16-element lists"
                    );

                for (const std::vector<f64>& p : points) {
                    if (p.size() != 3)
                        throw std::runtime_error(
                            "point must be a 3-element list"
                        );
                }

                const std::array<Point3D, 16> control_points = {
                    Point3D(points[0][0], points[0][1], points[0][2]),
                    Point3D(points[1][0], points[1][1], points[1][2]),
                    Point3D(points[2][0], points[2][1], points[2][2]),
                    Point3D(points[3][0], points[3][1], points[3][2]),
                    Point3D(points[4][0], points[4][1], points[4][2]),
                    Point3D(points[5][0], points[5][1], points[5][2]),
                    Point3D(points[6][0], points[6][1], points[6][2]),
                    Point3D(points[7][0], points[7][1], points[7][2]),
                    Point3D(points[8][0], points[8][1], points[8][2]),
                    Point3D(points[9][0], points[9][1], points[9][2]),
                    Point3D(points[10][0], points[10][1], points[10][2]),
                    Point3D(points[11][0], points[11][1], points[11][2]),
                    Point3D(points[12][0], points[12][1], points[12][2]),
                    Point3D(points[13][0], points[13][1], points[13][2]),
                    Point3D(points[14][0], points[14][1], points[14][2]),
                    Point3D(points[15][0], points[15][1], points[15][2]),
                };

                return new BezierPatchNode(name, mat, control_points);
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("control_points")
        )
        .def(
            "set_divisions",
            &BezierPatchNode::setDivisions,
            py::arg("u_div"),
            py::arg("v_div")
        );

    // NURBS node.
    py::class_<NURBSNode, GeometryNode, py::smart_holder>(m, "NURBSNode")
        .def(
            py::init([](const char* name,
                        MaterialPtr mat,
                        std::vector<std::vector<f64>> points,
                        std::vector<f64> weights,
                        std::vector<f64> u_knot_vector,
                        std::vector<f64> v_knot_vector) {
                if (points.size() != 4 || weights.size() != 4)
                    throw std::runtime_error(
                        "points and weights must be 4-element lists"
                    );

                if (u_knot_vector.size() != 4 || v_knot_vector.size() != 4)
                    throw std::runtime_error(
                        "u_knot_vector and v_knot_vector must be 4-element "
                        "lists"
                    );

                for (const std::vector<f64>& p : points) {
                    if (p.size() != 3)
                        throw std::runtime_error(
                            "point must be a 3-element list"
                        );
                }

                const std::array<Point3D, 4> control_points = {
                    Point3D(points[0][0], points[0][1], points[0][2]),
                    Point3D(points[1][0], points[1][1], points[1][2]),
                    Point3D(points[2][0], points[2][1], points[2][2]),
                    Point3D(points[3][0], points[3][1], points[3][2])
                };

                return new NURBSNode(
                    name,
                    mat,
                    control_points,
                    weights,
                    u_knot_vector,
                    v_knot_vector
                );
            }),
            py::arg("name"),
            py::arg("material"),
            py::arg("control_points"),
            py::arg("control_weights"),
            py::arg("u_knot_vector"),
            py::arg("v_knot_vector")
        )
        .def(
            "set_divisions",
            &NURBSNode::setDivisions,
            py::arg("u_div"),
            py::arg("v_div")
        );

    // Camera class.
    py::class_<Camera>(m, "Camera")
        .def(
            py::init([](std::vector<f64> look_from,
                        std::vector<f64> look_at,
                        std::vector<f64> up,
                        f64 fov,
                        Size nx,
                        Size ny) {
                if (look_from.size() != 3 || look_at.size() != 3 ||
                    up.size() != 3) {
                    throw std::runtime_error(
                        "look_from, look_at, and up must be 3-element lists"
                    );
                }
                return new Camera(
                    Point3D(look_from[0], look_from[1], look_from[2]),
                    Point3D(look_at[0], look_at[1], look_at[2]),
                    Vector3D(up[0], up[1], up[2]),
                    fov,
                    nx,
                    ny
                );
            }),
            py::arg("look_from"),
            py::arg("look_at"),
            py::arg("up"),
            py::arg("fov"),
            py::arg("nx"),
            py::arg("ny")
        );

    // RenderingMode enum.
    py::enum_<RenderingMode>(m, "RenderingMode")
        .value("Full", RenderingMode::Full)
        .value("NormalMap", RenderingMode::NormalMap)
        .export_values();

    // SamplingKind enum.
    py::enum_<SamplingKind>(m, "SamplingKind")
        .value("Center", SamplingKind::Center)
        .value("UniformRandom", SamplingKind::UniformRandom)
        .export_values();

    // Config struct.
    py::class_<Config>(m, "Config")
        .def(py::init<>())
        .def_readwrite("rendering_mode", &Config::renderingMode)
        .def_readwrite("sampling_kind", &Config::samplingKind)
        .def_readwrite("samples_per_pixel", &Config::samplesPerPixel)
        .def_readwrite("trace_depth", &Config::traceDepth);

    // render function.
    m.def(
        "render",
        [](const std::string& path,
           const Camera& camera,
           SceneNodePtr root,
           std::optional<Config> config) {
            render(
                path.c_str(), camera, std::move(root), config.value_or(Config())
            );
        },
        py::arg("path"),
        py::arg("camera"),
        py::arg("root"),
        py::arg("config") = py::none()
    );
}
