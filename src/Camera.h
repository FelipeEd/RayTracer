#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
    Camera(float aspectRatio = 800.0f / 600.0f);
    ~Camera();

private:
    glm::vec3 m_pos;
    glm::vec3 m_planeCenter;
    glm::vec3 m_up;
    glm::vec3 m_right;
    float m_fov;
    float m_aspectRatio;

public:
    float viewPortW;
    float viewPortH;
    float focalLength;
};

#endif