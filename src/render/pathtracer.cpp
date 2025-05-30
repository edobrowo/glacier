#include "render/pathtracer.hpp"

#include <thread>
#include <vector>

#include "common/util/log.hpp"
#include "matrix_stack.hpp"
#include "render/bvh.hpp"
#include "render/material/emissive.hpp"
#include "render/prim_list.hpp"
#include "scene/nodes/geometry_node.hpp"

namespace {

void collapsePrimitivesRecursive(
    const SceneNodePtr& node,
    MatrixStack& stack,
    std::vector<PrimitivePtr>& primitives
) {
    stack.push(node->transform().transform());

    if (const GeometryNode* geo = dynamic_cast<GeometryNode*>(node.get())) {
        PrimitivePtr primitive = geo->buildPrimitive();

        primitive->setMaterial(geo->material());
        primitive->setObjectToWorld(stack.reduce());

        primitives.push_back(std::move(primitive));
    }

    for (const SceneNodePtr& child : node->children())
        collapsePrimitivesRecursive(child, stack, primitives);

    stack.pop();
}

}

Pathtracer::Pathtracer(
    const SceneGraph& scene, const Camera& camera, const Config& config
)
    : config(config), mWorld(nullptr), mCamera(camera) {
    MatrixStack stack;
    std::vector<PrimitivePtr> primitives;
    collapsePrimitivesRecursive(scene.root(), stack, primitives);

    switch (config.spatialKind) {
    case SpatialKind::PrimList:
        mWorld = std::make_unique<PrimList>();
        break;
    case SpatialKind::BVH:
        mWorld = std::make_unique<BVH>();
        break;
    default:
        unreachable;
    }

    mWorld->build(primitives);
}

Image Pathtracer::render() const {
    Image image(mCamera.nx(), mCamera.ny());

    const Size thread_count = 8;
    Log::i("Hardware concurrency = {}", thread_count);

    std::vector<std::thread> threads;

    const f64 color_scale = 1.0 / static_cast<f64>(config.samplesPerPixel);

    auto render_rows = [&](Index row_start, Index row_end) {
        for (Index py = row_start; py < row_end; ++py) {
            for (Index px = 0; px < mCamera.nx(); ++px) {
                Vector3D color = Vector3D::zero();

                if (config.samplingKind == SamplingKind::Center) {
                    const Ray ray = generate(px, py);
                    color = shadeRecursive(ray, 1);
                } else {
                    for (Index sample = 0; sample < config.samplesPerPixel;
                         ++sample) {
                        const Ray ray = generate(px, py);

                        color += shadeRecursive(ray, 1);
                    }

                    color *= color_scale;
                }

                image.set(px, py, color);
            }
        }
    };

    const Size rows_per_thread = mCamera.ny() / thread_count;

    for (Index i = 0; i < thread_count; ++i) {
        const Index row_start = i * rows_per_thread;
        const Index row_end = (i == thread_count - 1)
                                  ? mCamera.ny()
                                  : row_start + rows_per_thread;

        threads.emplace_back(render_rows, row_start, row_end);
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    return image;
}

Ray Pathtracer::generate(const Index px, const Index py) const {
    const Point3D origin = mCamera.origin();

    Point3D point_sample;

    switch (config.samplingKind) {
    case SamplingKind::Center:
        point_sample = mCamera.p(px, py);
        break;
    case SamplingKind::UniformRandom:
        point_sample = mCamera.sample(px, py);
        break;
    default:
        unreachable;
    }

    const Vector3D direction = (point_sample - origin).normalize();

    return Ray(origin, direction);
}

Vector3D Pathtracer::shadeRecursive(const Ray& ray, const Size depth) const {
    if (depth >= config.traceDepth)
        return Vector3D::zero();

    if (const Option<SurfaceInteraction> option = mWorld->intersect(ray)) {
        const MaterialPtr mat = option->mat;

        const Option<ScatterRecord> record = mat->scatter(ray, *option);

        switch (config.renderingMode) {
        case RenderingMode::Full:
            if (record) {
                return record->color *
                       shadeRecursive(record->scattered, depth + 1);
            } else {
                if (mat->kind() == Material::Kind::Emissive)
                    return static_cast<Emissive*>(mat.get())->emitted();
                else
                    return Vector3D::zero();
            }
            break;
        case RenderingMode::NormalMap:
            return 0.5 * (option->n.normalize() + Vector3D::one());
            break;
        default:
            unreachable;
        }
    }

    return background(ray);
}

Vector3D Pathtracer::background(const Ray& ray) const {
    const Vector3D direction = ray.direction.normalize();
    const f64 a = 0.5 * (direction.y + 1.0);
    return (1.0 - a) * Vector3D::uniform(1.0) + a * Vector3D(0.5, 0.7, 1.0);
}
