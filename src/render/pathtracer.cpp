#include "render/pathtracer.hpp"

#include <thread>
#include <vector>

#include "common/util/log.hpp"
#include "render/material/emissive.hpp"
#include "scene/nodes/geometry_node.hpp"

Pathtracer::Pathtracer(SceneGraph& scene, const Camera& camera)
    : mScene(scene), mCamera(camera) {
    mScene.buildPrimitives();
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

    if (const Option<SurfaceInteraction> option = intersect(ray)) {
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

Option<SurfaceInteraction> Pathtracer::intersect(const Ray& ray) const {
    return intersectRecursive(
        mScene.root(), ray, Interval(0.001, math::infinity<f64>())
    );
}

Option<SurfaceInteraction> Pathtracer::intersectRecursive(
    const SceneNodePtr& node, const Ray& ray, const Interval& bounds
) const {
    // Current closest intersection and interval.
    Option<SurfaceInteraction> closest = std::nullopt;
    Interval closest_bounds(bounds);

    // On "the way down", transform the ray with the current node's inverse
    // transformation.
    const Ray inverse_ray =
        Ray(node->transform().inverse() * ray.origin,
            node->transform().inverse() * ray.direction);

    // Compute the intersect with the current node if it contains a primitive.
    if (node->kind() == SceneNode::Kind::Geometry) {
        const GeometryNode* geo = static_cast<GeometryNode*>(node.get());
        if (const Option<SurfaceInteraction> interaction =
                geo->primitive()->intersect(inverse_ray, bounds)) {
            closest = interaction;
            closest->mat = geo->material();
            closest_bounds.max = std::min(closest->t, closest_bounds.max);
        }
    }

    // Recursively compute the intersection over all children nodes, and
    // determine the minimum intersection.
    for (const SceneNodePtr& child : node->children()) {
        if (const Option<SurfaceInteraction> interaction =
                intersectRecursive(child, inverse_ray, closest_bounds)) {
            if (!closest || interaction->t < closest->t) {
                closest = interaction;
                closest_bounds.max = interaction->t;
            }
        }
    }

    // On "the way up", create a new ray where the origin is transformed with
    // the current node's transformation, and the normal is transformed with
    // the upper 3x3 of the transpose of the inverse of the current node's
    // transformation.
    if (closest) {
        closest->p = node->transform().matrix() * closest->p;
        closest->n =
            (Matrix3D(transpose(node->transform().inverse())) * closest->n)
                .normalize();
    }

    return closest;
}

Vector3D Pathtracer::background(const Ray& ray) const {
    const Vector3D direction = ray.direction.normalize();
    const f64 a = 0.5 * (direction.y + 1.0);
    return (1.0 - a) * Vector3D::uniform(1.0) + a * Vector3D(0.5, 0.7, 1.0);
}
