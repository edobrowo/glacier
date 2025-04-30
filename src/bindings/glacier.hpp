#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "material/lambertian.hpp"
#include "material/material.hpp"
#include "render/camera.hpp"
#include "scene/geometry_node.hpp"
#include "scene/scene_node.hpp"
#include "scene/sphere_node.hpp"
#include "util/common.hpp"

namespace py = pybind11;

/// @brief Renders the scene from the given virtual camera to an image file at
/// the specified path.
void render(const char* path, const Camera& camera, SceneNodePtr&& root);

PYBIND11_MODULE(glacier, m) {
    m.doc() = "Glacier renderer module.";

    // Transform::Order enum.
    py::enum_<Transform::Order>(m, "TransformOrder")
        .value("SRT", Transform::Order::SRT)
        .value("STR", Transform::Order::STR)
        .value("RST", Transform::Order::RST)
        .value("RTS", Transform::Order::RTS)
        .value("TSR", Transform::Order::TSR)
        .value("TRS", Transform::Order::TRS)
        .export_values();

    // Transform::RotationOrder enum.
    py::enum_<Transform::RotationOrder>(m, "RotationOrder")
        .value("XYZ", Transform::RotationOrder::XYZ)
        .value("XZY", Transform::RotationOrder::XZY)
        .value("YXZ", Transform::RotationOrder::YXZ)
        .value("YZX", Transform::RotationOrder::YZX)
        .value("ZXY", Transform::RotationOrder::ZXY)
        .value("ZYX", Transform::RotationOrder::ZYX)
        .export_values();

    // Transform class.
    py::class_<Transform>(m, "Transform")
        .def(py::init<>())
        .def("s", py::overload_cast<f64, f64, f64>(&Transform::s))
        .def("r", py::overload_cast<f64, f64, f64>(&Transform::r))
        .def("t", py::overload_cast<f64, f64, f64>(&Transform::t))
        .def("set_order", &Transform::setOrder)
        .def("set_rotation_order", &Transform::setRotationOrder);

    // Material::Kind enum.
    py::enum_<Material::Kind>(m, "MaterialKind")
        .value("Null", Material::Kind::Null)
        .value("Lambertian", Material::Kind::Lambertian)
        .export_values();

    // Material class.
    py::class_<Material, py::smart_holder>(m, "Material")
        .def_property_readonly("kind", &Material::kind);

    // LambertianMaterial class.
    py::class_<Lambertian, Material, py::smart_holder>(m, "LambertianMaterial")
        .def(py::init([](std::vector<f64> color) {
                 if (color.size() != 3) {
                     throw std::runtime_error(
                         "Lambertian color must be a 3-element list");
                 }
                 return new Lambertian(Vector3D(color[0], color[1], color[2]));
             }),
             py::arg("color"));

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
        .def("transform",
             py::overload_cast<>(&SceneNode::transform),
             py::return_value_policy::reference_internal)
        .def("s",
             [](SceneNode& self, f64 x, f64 y, f64 z) {
                 self.transform().s(x, y, z);
             })
        .def("r",
             [](SceneNode& self, f64 x, f64 y, f64 z) {
                 self.transform().r(x, y, z);
             })
        .def("t",
             [](SceneNode& self, f64 x, f64 y, f64 z) {
                 self.transform().t(x, y, z);
             })
        .def("add_child", &SceneNode::addChild)
        .def_readwrite("name", &SceneNode::name);

    // GeometryNode class.
    py::class_<GeometryNode, SceneNode, py::smart_holder>(m, "GeometryNode");

    // SphereNode class.
    py::class_<SphereNode, GeometryNode, py::smart_holder>(m, "SphereNode")
        .def(py::init<const char*, MaterialPtr>(),
             py::arg("name"),
             py::arg("material"));

    // Camera class.
    py::class_<Camera>(m, "Camera")
        .def(py::init([](std::vector<f64> look_from,
                         std::vector<f64> look_at,
                         std::vector<f64> up,
                         f64 fov,
                         Size nx,
                         Size ny) {
                 if (look_from.size() != 3 || look_at.size() != 3 ||
                     up.size() != 3) {
                     throw std::runtime_error(
                         "look_from, look_at, and up must be 3-element lists");
                 }
                 return new Camera(
                     Point3D(look_from[0], look_from[1], look_from[2]),
                     Point3D(look_at[0], look_at[1], look_at[2]),
                     Vector3D(up[0], up[1], up[2]),
                     fov,
                     nx,
                     ny);
             }),
             py::arg("look_from"),
             py::arg("look_at"),
             py::arg("up"),
             py::arg("fov"),
             py::arg("nx"),
             py::arg("ny"));

    // render function.
    m.def(
        "render",
        [](const std::string& path, const Camera& camera, SceneNodePtr root) {
            render(path.c_str(), camera, std::move(root));
        },
        py::arg("path"),
        py::arg("camera"),
        py::arg("root"));
}
