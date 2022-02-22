#include "RayTracer.h"

RayTracer::RayTracer(DATA_camSpecs camSpecs, int w, int h)
{
    framebuffer = FrameBuffer(w, h);
    camera = Camera(camSpecs.position, camSpecs.lookat, camSpecs.up, camSpecs.aspectRatio, camSpecs.FOV);
}

// Runs for each ray and returns a color
glm::vec3 RayTracer::getHitColor(const Ray &ray, const Scene &scene, int depth)
{
    hit_record rec;

    if (depth <= 0)
    {
        float t = 0.5f * (ray.dir.y + 1.0f);
        return (1.0f - t) * glm::vec3(0.6, 0.6, 0.6) + t * glm::vec3(0.054, 0.011, 0.188);
    }

    if (scene.hit(ray, 0, 9999999, rec))
    {
        glm::vec3 target = rec.p + rec.normal; // + random_in_unit_sphere();
        return 0.5f * rec.color * getHitColor(Ray(rec.p, target - rec.p), scene, depth - 1);
        // return glm::vec3(0.5, 0.0, 0.0);
    }

    float t = 0.5f * (ray.dir.y + 1.0f);
    return (1.0f - t) * glm::vec3(0.6, 0.6, 0.6) + t * glm::vec3(0.054, 0.011, 0.188);
}

static unsigned int g_seed;

inline int fastrand()
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

inline double random_double()
{
    // Returns a random real in [0,1).
    return fastrand() / (RAND_MAX + 1.0);
}

void printStatus()
{
    static int count = 0;
    std::cerr << "\r";
    for (int i = 0; i < 10; i++)
    {
        std::cerr << "\b";
    }

    std::string ready = "[";
    std::string notready = "";

    for (int i = 0; i < count; i++)
    {
        ready += "#";
    }
    for (int i = 0; i < 10 - count; i++)
    {
        notready += "-";
    }
    notready += "]";

    std::cerr << ready + notready;
    count++;
}

void RayTracer::render(const Scene &scene, int samples, int bounces)
{

    for (int j = 0; j < framebuffer.height; j++)
    {
        if (j % ((framebuffer.height - 1) / 10) == 0)
            printStatus();
        for (int i = 0; i < framebuffer.width; i++)
        {
            glm::vec3 pixColor(0.0f);
            for (int k = 0; k < samples; k++)
            {
                float u = float(i + random_double()) / (framebuffer.width - 1);
                float v = float(j + random_double()) / (framebuffer.height - 1);
                Ray ray = camera.getRay(u, v);
                pixColor += getHitColor(ray, scene, bounces);
            }
            framebuffer.at(i, j) = pixColor / (float)samples;
        }
    }
    std::cerr << "\n";
}