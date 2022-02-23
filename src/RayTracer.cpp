#include "RayTracer.h"

RayTracer::RayTracer(DATA_camSpecs camSpecs, int w, int h)
{
    framebuffer = FrameBuffer(w, h);
    camera = Camera(camSpecs.position, camSpecs.lookat, camSpecs.up, camSpecs.aspectRatio, camSpecs.FOV);
}

// Runs for each ray and returns a color
glm::vec3 RayTracer::recursiveRayTracing(const Ray &ray, const Scene &scene, int depth)
{
    hit_record rec;

    // If the max bounce limit has been reached
    if (depth <= 0)
    {
        // Skycolor
        float t = 0.5f * (ray.dir.y + 1.0f);
        return (1.0f - t) * glm::vec3(0.6, 0.6, 0.6) + t * glm::vec3(0.054, 0.011, 0.188);
    }

    if (scene.hit(ray, 0, 9999999, rec))
    {
        glm::vec3 target = rec.p + rec.normal; // + random_in_unit_sphere();
        if (rec.material->kr > 0)
            return rec.material->ka * rec.material->kr * rec.texColor * recursiveRayTracing(Ray(rec.p, target - rec.p), scene, depth - 1);
        return rec.material->ka * rec.texColor;
    }

    // if the ray goes to infinity return a Skycolor
    float t = 0.5f * (ray.dir.y + 1.0f);
    return (1.0f - t) * glm::vec3(0.6, 0.6, 0.6) + t * glm::vec3(0.054, 0.011, 0.188);
}

void RayTracer::render(const Scene &scene, int samples, int bounces)
{

    // For every row
    for (int j = 0; j < framebuffer.height; j++)
    {
        // Updates the status bar every 10%
        if (j % ((framebuffer.height - 1) / 10) == 0)
            printStatus();

        // For every column
        for (int i = 0; i < framebuffer.width; i++)
        {
            // Pixels starts as black
            glm::vec3 pixColor(0.0f);
            for (int k = 0; k < samples; k++)
            {
                float u = float(i + random_float()) / (framebuffer.width - 1);
                float v = float(j + random_float()) / (framebuffer.height - 1);
                Ray ray = camera.getRay(u, v);
                pixColor += recursiveRayTracing(ray, scene, bounces);
            }
            // Updates the framebuffer with the mean of the many samples
            framebuffer.at(i, j) = pixColor / (float)samples;
        }
    }
}