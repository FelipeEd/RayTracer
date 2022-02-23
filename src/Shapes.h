#ifndef SHAPES_H
#define SHAPES_H

#pragma once

#include <glm\glm.hpp>
#include "Ray.h"
#include "Texture.h"

// Struct used to store data about a ray, in order for example to determine which object was hit first
struct hit_record
{
    glm::vec3 p;                       // Point
    glm::vec3 normal;                  // Surface normal
    glm::vec3 texColor;                // Color of the shape
    const DATA_materialPhys *material; // Material fisical proprieties
    float t;                           // t in which the ray hits
    bool frontFace;

    inline void set_face_normal(const Ray &ray, const glm::vec3 &outward_normal)
    {
        frontFace = glm::dot(ray.dir, outward_normal) < 0;
        normal = frontFace ? outward_normal : -outward_normal;
    }
};

// Virtual class that objects, surfaces etc, must inherit in order to interact with rays
class Shape
{
protected:
    Shape(const Texture &texture,
          const DATA_materialPhys &material) : m_texture(&texture),
                                               m_material(&material) {}
    Shape() {}

public:
    const Texture *m_texture;
    const DATA_materialPhys *m_material;
    virtual bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const = 0;
};

// Sphere class
class Sphere : public Shape
{
public:
    glm::vec3 pos;
    float r;

public:
    Sphere(glm::vec3 center,
           float radius,
           const Texture &texture,
           const DATA_materialPhys &material) : pos(center),
                                                r(radius),
                                                Shape(texture, material) {}

    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif