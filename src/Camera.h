#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <glm\glm.hpp>

#include "Ray.h"

class Camera
{
public:
    Camera(float aspectRatio = 800.0f / 600.0f, float FOV = 60.0f);
    ~Camera() {}

    Ray getRay(float u, float v);
    void setPos(glm::vec3 newPos);
    glm::vec3 getPos() { return pos; };

private:
    glm::vec3 pos;
    float m_viewPortH;
    float m_viewPortW;
    glm::vec3 m_lookAt;

public:
    glm::vec3 vertical;
    glm::vec3 horizontal;
    glm::vec3 lower_left_corner;
    float focalLength;
    float fov;
};

#endif