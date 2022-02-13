#ifndef VISIBLE_H
#define VISIBLE_H

#pragma once

#include <glm\glm.hpp>
#include "Ray.h"

// Struct used to store data about a ray, in order for example to determine which object was hit first
struct hit_record
{
    glm::vec3 p;
    glm::vec3 normal;
    float t;
};

// Virtual class that objects, surfaces etc, must inherit in order to interact with rays
class Visible
{
public:
    virtual bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif