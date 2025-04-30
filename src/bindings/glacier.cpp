#include "glacier.hpp"

#include "render/image.hpp"
#include "render/pathtracer.hpp"
#include "util/log.hpp"

void render(const char* path,
            const Camera& camera,
            SceneNodePtr&& root,
            const Config& config) {
    SceneGraph scene;

    scene.root()->addChild(std::move(root));

    Pathtracer pt(scene, camera);
    pt.config.renderingMode = config.renderingMode;
    pt.config.samplesPerPixel = config.samplesPerPixel;
    pt.config.traceDepth = config.traceDepth;

    Log::i("Rendering mode = {}", config.renderingMode);
    Log::i("Samples per pixel = {}", config.samplesPerPixel);
    Log::i("Trace depth = {}", config.traceDepth);

    const Image image = pt.render();

    image.save("out.png");
}
