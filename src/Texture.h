#pragma once

#include <glm\glm.hpp>
#include "Data.h"

// Virtual texture class
class Texture
{
public:
    int type = 0;
    // Should return a color based on where on the surface did the ray hit
    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const = 0;
    virtual int getType() { return this->type; }
};

// Flat color Shading
class Solid : public Texture
{
private:
    glm::vec3 m_flatColor;

public:
    int type = 1;
    Solid(glm::vec3 flatColor) : m_flatColor(flatColor) {}

    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const override;
    virtual int getType() override { return this->type; }
};

// Checker color Shading
class Checker : public Texture
{
private:
    glm::vec3 m_firstColor;
    glm::vec3 m_secondColor;
    float m_cubeSize;

public:
    int type = 2;
    Checker(glm::vec3 firstColor,
            glm::vec3 secondColor,
            float cubeSize) : m_firstColor(firstColor),
                              m_secondColor(secondColor),
                              m_cubeSize(cubeSize) {}

    virtual glm::vec3 getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const override;
    virtual int getType() override { return this->type; }
};
