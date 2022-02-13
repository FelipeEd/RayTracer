#ifndef SPHERE_H
#define SPHERE_H

#pragma once

#include "Visible.h"

class Sphere : public Visible
{
public:
    glm::vec3 pos;
    float r;

public:
    Sphere(glm::vec3 center, float radius) : pos(center), r(radius) {}
    ~Sphere() {}

    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;

private:
};

#endif