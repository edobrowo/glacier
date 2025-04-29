#include "glacier.hpp"

#include "render/image.hpp"
#include "render/pathtracer.hpp"

void render(const char* path, const Camera& camera, SceneNodePtr&& root) {
    SceneGraph scene;

    scene.root()->addChild(std::move(root));

    const Image image = Pathtracer(scene, camera).render();

    image.save("out.png");
}
