#include "RayTracer.h"

RayTracer::RayTracer(DATA_camSpecs camSpecs, int w, int h)
{
    framebuffer = FrameBuffer(w, h);
    camera = Camera(camSpecs.position, camSpecs.lookat, camSpecs.up, camSpecs.aspectRatio, camSpecs.FOV);
}

glm::vec3 difuse(const Scene &scene, glm::vec3 hitpoint)
{
    hit_record aux;
    glm::vec3 diffuseColor(0.0f);
    for (auto light : scene.lights)
    {
        glm::vec3 target = light->m_pos;
        Ray ray = Ray(hitpoint, target - hitpoint);
        float d = glm::distance(target, hitpoint);

        if (!scene.hit(ray, 0, d, aux))
        {
            float attenuationCoefficient = (1.0f / (light->m_constAtt + light->m_pDist * d + light->m_pDist2 * d * d));
            // std::cerr << "att coef : " << attenuationCoefficient << "\n";
            diffuseColor += light->m_color * attenuationCoefficient;
        }
    }
    return diffuseColor;
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
        /*
        if (rec.material->kr > 0)
        {
            glm::vec3 target = rec.p + rec.normal; // + random_in_unit_sphere();
            return rec.material->ka * rec.material->kr * rec.texColor * recursiveRayTracing(Ray(rec.p, target - rec.p), scene, depth - 1);
        }
        else
        {
            return rec.material->ka * rec.texColor;
        }
        */
        return difuse(scene, rec.p) + rec.texColor * rec.material->ka; // * rec.material->kd;
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

            float u = float(i) / (framebuffer.width);
            float v = float(j) / (framebuffer.height);

            Ray ray = camera.getRay(u, v);
            pixColor += recursiveRayTracing(ray, scene, bounces);

            for (int k = 0; k < samples - 1; k++)
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