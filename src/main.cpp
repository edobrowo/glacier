#include "material/lambertian.hpp"
#include "primitive/sphere.hpp"
#include "render/camera.hpp"
#include "render/image.hpp"
#include "render/pathtracer.hpp"
#include "scene/geometry_node.hpp"
#include "scene/scene_graph.hpp"
#include "scene/sphere_node.hpp"

int main() {
    SceneGraph scene;
    const Camera camera(Point3D(0.0, 0.0, 0.0),
                        Point3D(0.0, 0.0, -1.0),
                        Vector3D(0.0, 1.0, 0.0),
                        90.0,
                        400,
                        225);

    MaterialPtr mat = std::make_shared<Lambertian>(Vector3D::uniform(0.5));

    GeometryNodePtr sphere = std::make_unique<SphereNode>("sphere", mat);
    sphere->transform().t(0.0, 0.0, -1.0);
    sphere->transform().s(0.5, 0.5, 0.5);
    scene.root()->addChild(std::move(sphere));

    GeometryNodePtr ground = std::make_unique<SphereNode>("ground", mat);
    ground->transform().t(0.0, -100.5, -1.0);
    ground->transform().s(100.0, 100.0, 100.0);
    scene.root()->addChild(std::move(ground));

    const Image image = Pathtracer(scene, camera).render();

    image.save("out.png");
}
