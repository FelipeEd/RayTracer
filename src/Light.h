#pragma once

#include <glm\glm.hpp>

class Light
{
public:
    Light();
    ~Light();

private:
    glm::vec3 pos;
    glm::vec3 color;

    float constAtt;  // Constant attenuation
    float propDist;  // Attenuation proportional to the distance
    float propDist2; // Attenuation proportional to the square of distance
};
