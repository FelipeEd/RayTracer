#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

#include <glm\glm.hpp>

class Material
{
public:
    virtual glm::vec3 getPigment() const = 0;
};

// Flat color Shading
class Solid : public Material
{
private:
    glm::vec3 m_flatColor;

public:
    Solid(glm::vec3 flatColor) : m_flatColor(flatColor) {}
    virtual glm::vec3 getPigment() const override;
};

#endif