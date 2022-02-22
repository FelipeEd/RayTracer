#pragma once

#include <glm\glm.hpp>

struct DATA_camSpecs
{
    glm::vec3 position, lookat, up;
    float aspectRatio, FOV;
};