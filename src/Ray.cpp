#include "Ray.h"

Ray::Ray(glm::vec3 rayOrigin, glm::vec3 direction)
{
    origin = rayOrigin;
    dir = glm::normalize(direction);
}

glm::vec3 Ray::at(float t) const
{
    return origin + dir * t;
}

bool Ray::hit_sphere(const glm::vec3 &center, double radius) const
{
    glm::vec3 oc = origin - center;
    auto a = glm::dot(dir, dir);
    auto b = 2.0 * glm::dot(oc, dir);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}