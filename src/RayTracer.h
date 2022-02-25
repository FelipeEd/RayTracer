#ifndef RAYTRACER_H
#define RAYTRACER_H

#pragma once

#include <glm/gtc/random.hpp>

#include "AuxFunctions.h"
#include "Data.h"
#include "Ray.h"
#include "Scene.h"
#include "Camera.h"
#include "FrameBuffer.h"

// A class responsable for controling all raytracing components
// acts like a renderer
class RayTracer
{
public:
    Camera camera = Camera({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, 800.0f / 600.0f, 60.0f);
    FrameBuffer framebuffer = FrameBuffer(800, 600);

public:
    bool imperfectReflection = false;
    bool imperfectShadows = false;

    RayTracer(DATA_camSpecs camSpecs, int w, int h);
    RayTracer() {}
    glm::vec3 difuseSpecular(const Scene &scene, hit_record hitpoint, const Camera &cam);
    void render(const Scene &scene, int samples, int bounces);

private:
    glm::vec3 recursiveRayTracing(const Ray &ray, const Scene &scene, int depth);
};

#endif