#ifndef RAYTRACER_H
#define RAYTRACER_H

#pragma once

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
    RayTracer(DATA_camSpecs camSpecs, int w, int h);
    RayTracer() {}
    void render(const Scene &scene, int samples, int bounces);

private:
    glm::vec3 getHitColor(const Ray &ray, const Scene &scene, int depth);
};

#endif