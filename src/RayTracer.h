#ifndef RAYTRACER_H
#define RAYTRACER_H

#pragma once

#include "Ray.h"
#include "Scene.h"
#include "Camera.h"
#include "FrameBuffer.h"

// A class responsable for controling all raytracing components
// acts like a renderer
class RayTracer
{
public:
    Camera camera;
    FrameBuffer framebuffer;

public:
    RayTracer();
    ~RayTracer();
    void render(const Scene &scene);

private:
    glm::vec3 getHitColor(const Ray &ray, const Scene &scene);
};

#endif