#include "RayTracer.h"

RayTracer::RayTracer()
{
}

RayTracer::~RayTracer()
{
}

glm::vec3 RayTracer::getHitColor(const Ray &ray, const Scene &scene)
{
    hit_record rec;
    if (scene.hit(ray, 0, 999999.0f, rec))
    {
        // glm::vec3 color(0.0f);
        // for (auto light : scene.lights)
        // {
        // }

        return 0.5f * (rec.normal + glm::vec3(1, 1, 1));
    }

    float t = 0.5f * (ray.dir.y + 1.0f);
    return (1.0f - t) * glm::vec3(0.6, 0.6, 0.6) + t * glm::vec3(0.054, 0.011, 0.188);
}

void RayTracer::render(const Scene &scene)
{

    for (int j = 0; j < framebuffer.height; j++)
        for (int i = 0; i < framebuffer.width; i++)
        {
            float u = float(i) / (framebuffer.width - 1);
            float v = float(j) / (framebuffer.height - 1);
            Ray ray = camera.getRay(u, v);
            framebuffer.at(i, j) = getHitColor(ray, scene);
        }
}