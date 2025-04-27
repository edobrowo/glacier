#include "geometry/sphere.hpp"
#include "material/lambertian.hpp"
#include "render/camera.hpp"
#include "render/image.hpp"
#include "render/pathtracer.hpp"
#include "scene/geometry_node.hpp"
#include "scene/scene_graph.hpp"

int main() {
    SceneGraph scene;
    const Camera camera(Point3D(0.0, 0.0, 0.0),
                        Point3D(0.0, 0.0, -1.0),
                        Vector3D(0.0, 1.0, 0.0),
                        90.0,
                        400,
                        225);

    std::unique_ptr<Lambertian> mat1 =
        std::make_unique<Lambertian>(Vector3D::uniform(0.5));
    std::unique_ptr<Sphere> sphere = std::make_unique<Sphere>();
    GeometryNodePtr node1 =
        GeometryNode::make("sphere", std::move(sphere), std::move(mat1));
    node1->transform().t(0.0, 0.0, -1.0);
    node1->transform().s(0.5, 0.5, 0.5);
    scene.root()->addChild(std::move(node1));

    std::unique_ptr<Lambertian> mat2 =
        std::make_unique<Lambertian>(Vector3D(0.1, 0.5, 0.1));
    std::unique_ptr<Sphere> ground = std::make_unique<Sphere>();
    GeometryNodePtr node2 =
        GeometryNode::make("ground", std::move(ground), std::move(mat2));
    node2->transform().t(0.0, -100.5, -1.0);
    node2->transform().s(100.0, 100.0, 100.0);
    scene.root()->addChild(std::move(node2));

    const Pathtracer pathtracer(scene, camera);

    const Image image = pathtracer.render();
    image.save("out.png");
}
