#include "glacier.hpp"

#include "common/util/image.hpp"
#include "common/util/log.hpp"
#include "render/pathtracer.hpp"

void render(
    const char* path,
    const Camera& camera,
    const SceneNodePtr& root,
    const Config& config
) {
    SceneGraph scene;

    scene.root()->addChild(root);

    Pathtracer pt(scene, camera);
    pt.config.renderingMode = config.renderingMode;
    pt.config.samplingKind = config.samplingKind;
    pt.config.samplesPerPixel = config.samplesPerPixel;
    pt.config.traceDepth = config.traceDepth;

    Log::i("Rendering mode = {}", config.renderingMode);
    Log::i("Sampling kind = {}", config.samplingKind);

    if (config.samplingKind == SamplingKind::Center)
        Log::i(
            "Samples per pixel = {} (overriden to 1 due to SamplingKind)",
            config.samplesPerPixel
        );
    else
        Log::i("Samples per pixel = {}", config.samplesPerPixel);

    if (config.renderingMode == RenderingMode::NormalMap)
        Log::i(
            "Trace depth = {} (overriden to 1 due to RenderingMode)",
            config.traceDepth
        );
    else
        Log::i("Trace depth = {}", config.traceDepth);

    const Image image = pt.render();

    image.save("out.png");
}
