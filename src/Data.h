#pragma once

#include <glm\glm.hpp>

struct DATA_camSpecs
{
    glm::vec3 position, lookat, up;
    float aspectRatio, FOV;
};

struct DATA_materialPhys
{
    float ka,  // Ambient light coefficient
        kd,    // Diffusion coefficient
        ks,    // Specular coefficient
        alpha, // Specular expoent
        kr,    // Reflection coefficient
        kt,    // Transmission coefficient
        ior;   // Index of refraction
};