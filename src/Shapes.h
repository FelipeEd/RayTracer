#ifndef SHAPES_H
#define SHAPES_H

#pragma once

#include <glm\glm.hpp>
#include "Ray.h"
#include "Texture.h"

// Struct used to store data about a ray, in order for example to determine which object was hit first
struct hit_record
{
    glm::vec3 p;       // Point
    glm::vec3 normal;  // Surface normal
    glm::vec3 color;   // Color of the shape
    Texture *material; // Texture
    float t;           // t in which the ray hits
    bool frontFace;
};

// Virtual class that objects, surfaces etc, must inherit in order to interact with rays
class Shape
{
public:
    Texture *material;
    virtual bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const = 0;
};

// Sphere class
class Sphere : public Shape
{
public:
    glm::vec3 pos;
    float r;

public:
    Sphere(glm::vec3 center, float radius, Texture &mat) : pos(center), r(radius) { this->material = &mat; }
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif