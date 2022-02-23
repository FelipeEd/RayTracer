#pragma once

#include <glm\glm.hpp>
#include "Data.h"

// Virtual texture class
class Texture
{
public:
    // Should return a color based on where on the surface did the ray hit
    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const = 0;
};

// Flat color Shading
class Solid : public Texture
{
private:
    glm::vec3 m_flatColor;

public:
    Solid(glm::vec3 flatColor) : m_flatColor(flatColor) {}

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
            float cubeSize) : m_firstColor(firstColor),
                              m_secondColor(secondColor),
                              m_cubeSize(cubeSize) {}

    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const override;
};
