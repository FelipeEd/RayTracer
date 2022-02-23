#pragma once

#include <glm\glm.hpp>
#include "Data.h"

// Virtual material class
class Texture
{
protected:
    Texture(DATA_materialPhys phys) : m_phys(phys) {}

public:
    DATA_materialPhys m_phys;
    // Should return a color based on where on the surface did the ray hit
    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const = 0;
};

// Flat color Shading
class Solid : public Texture
{
private:
    glm::vec3 m_flatColor;

public:
    Solid(glm::vec3 flatColor,
          DATA_materialPhys materialData)
        : m_flatColor(flatColor),
          Texture(materialData) {}

    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const override;
};

// Checker color Shading
class Checker : public Texture
{
private:
    glm::vec3 m_firstColor;
    glm::vec3 m_secondColor;
    float m_cubeSize;

public:
    Checker(glm::vec3 firstColor,
            glm::vec3 secondColor,
            float cubeSize,
            DATA_materialPhys materialData)
        : m_firstColor(firstColor),
          m_secondColor(secondColor),
          m_cubeSize(cubeSize),
          Texture(materialData) {}

    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const override;
};
