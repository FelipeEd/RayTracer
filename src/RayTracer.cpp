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
        return 0.5f * (rec.normal + glm::vec3(1, 1, 1));
    }

    float t = 0.5f * (ray.dir.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.054, 0.011, 0.188);
}

void RayTracer::render(const Scene &scene)
{
    glm::vec3 origin(0.0);
    auto horizontal = glm::vec3(camera.viewPortW, 0, 0);
    auto vertical = glm::vec3(0, camera.viewPortH, 0);
    auto lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, camera.focalLength);

    for (int j = 0; j < framebuffer.height; j++)
        for (int i = 0; i < framebuffer.width; i++)
        {
            float u = float(i) / (framebuffer.width - 1);
            float v = float(j) / (framebuffer.height - 1);
            Ray ray({0.0, 0.0, 0.0}, lower_left_corner + u * horizontal + v * vertical - origin);
            framebuffer.at(i, j) = getHitColor(ray, scene);
        }
}