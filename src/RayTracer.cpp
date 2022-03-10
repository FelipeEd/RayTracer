#include "RayTracer.h"

RayTracer::RayTracer(DATA_camSpecs camSpecs, int w, int h)
{
    framebuffer = FrameBuffer(w, h);
    camera = Camera(camSpecs.position, camSpecs.lookat, camSpecs.up, camSpecs.aspectRatio, camSpecs.FOV);
}

glm::vec3 random_vec3(float size)
{
    glm::vec3 a = glm::normalize(glm::vec3(random_float()));
    return a * size;
}

glm::vec3 RayTracer::difuseSpecular(const Scene &scene, hit_record hitpoint, const Camera &cam)
{
    hit_record aux;
    glm::vec3 specularColor(0.0f);
    glm::vec3 diffuseColor(0.0f);

    glm::vec3 viewDir = glm::normalize(cam.pos - hitpoint.p);
    for (int i = 1; i < scene.lights.size(); i++)
    {
        std::shared_ptr<Light> light = scene.lights[i];

        glm::vec3 lightDir = glm::normalize(light->m_pos - hitpoint.p);

        Ray ray = Ray(hitpoint.p, light->m_pos - hitpoint.p);
        if (imperfectShadows)
            ray = Ray(hitpoint.p, light->m_pos - hitpoint.p + glm::sphericalRand(0.5f));

        float d = glm::distance(lightDir, hitpoint.p);

        glm::vec3 reflectDir = glm::reflect(-lightDir, hitpoint.normal);

        if (!scene.hit(ray, 0.001f, d, aux))
        {
            float attenuationCoefficient = (1.0f / (light->m_constAtt + light->m_pDist * d +
                                                    light->m_pDist2 * d * d));
            // Specular
            float spec = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f),
                                  hitpoint.material->alpha);
            specularColor += spec * light->m_color * attenuationCoefficient;

            // Diffuse
            float diff = glm::max(glm::dot(hitpoint.normal, lightDir), 0.0f);
            diffuseColor += diff * light->m_color * attenuationCoefficient;
        }
    }
    return (specularColor * hitpoint.material->ks +
            diffuseColor * hitpoint.material->kd) *
           hitpoint.texColor;
}

glm::vec3 refract(const glm::vec3 &uv, const glm::vec3 &n, float etai_over_etat)
{
    float cos_theta = fmin(dot(-uv, n), 1.0f);
    glm::vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    glm::vec3 r_out_parallel = (float)-sqrt(fabs(1.0f - glm::dot(r_out_perp, r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}

float reflectance(float cosine, float ref_idx)
{
    // Use Schlick's approximation for reflectance.
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// Runs for each ray and returns a color
glm::vec3 RayTracer::recursiveRayTracing(const Ray &ray, const Scene &scene, int depth)
{
    hit_record rec;

    // If the max bounce limit has been reached
    if (depth <= 0)
    {
        // Skycolor
        return glm::vec3(0.0f);
    }

    if (scene.hit(ray, 0, 9999999, rec))
    {

        if (rec.material->kr == 0.0 && rec.material->kt == 0.0) // if (rec.material->kr == 0 && rec.material->kt == 0)
        {
            glm::vec3 ambient = scene.lights[0]->m_color * rec.material->ka * rec.texColor;
            return difuseSpecular(scene, rec, camera) + ambient;
        }
        if ((rec.material->kr > 0.0) && rec.material->kt == 0.0)
        {
            glm::vec3 target;
            if (imperfectReflection)
                target = rec.p + rec.normal + glm::sphericalRand(0.1f);
            else
                target = rec.p + rec.normal;

            glm::vec3 ambient = scene.lights[0]->m_color * rec.material->ka * rec.texColor;
            ambient = rec.material->ka * rec.texColor;
            return (1 - rec.material->kr) * (difuseSpecular(scene, rec, camera) + ambient) +
                   rec.material->kr * recursiveRayTracing(Ray(rec.p + 0.001f * rec.normal,
                                                              target - rec.p),
                                                          scene, depth - 1);
        }
        if (rec.material->kt > 0)
        {
            float ir = rec.material->ior;
            double refraction_ratio = rec.frontFace ? (1.0 / ir) : ir;

            glm::vec3 unit_direction = glm::normalize(ray.dir);
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            glm::vec3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, refraction_ratio);

            Ray scattered(glm::vec3(0), glm::vec3(0));
            if (rec.frontFace)
                scattered = Ray(rec.p - 0.001f * rec.normal, direction);
            else
                scattered = Ray(rec.p + 0.001f * rec.normal, direction);

            // glm::vec3 target = refract(rec.p, rec.normal, rec.material->ior); //+ glm::sphericalRand(1.0f);

            glm::vec3 ambient = scene.lights[0]->m_color * rec.material->ka * rec.texColor;
            return (1 - rec.material->kt) * (difuseSpecular(scene, rec, camera) + ambient) +
                   rec.material->kt * recursiveRayTracing(scattered, scene, depth - 1);
        }
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