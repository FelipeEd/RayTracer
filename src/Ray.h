#pragma once

#include <glm\glm.hpp>

// A Ray is defined by it starting point + a directon
class Ray
{
public:
    glm::vec3 origin;
    glm::vec3 dir;

public:
    Ray(glm::vec3 rayOrigin, glm::vec3 direction);

    bool hit_sphere(const glm::vec3 &center, double radius) const;
    glm::vec3 at(float t) const;
};
