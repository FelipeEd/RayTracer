#pragma once

#include <glm\glm.hpp>

#include "Ray.h"

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float aspectRatio, float FOV);

    Ray getRay(float u, float v);
    void setPos(glm::vec3 newPos);
    glm::vec3 getPos() { return pos; };

private:
    glm::vec3 m_up;
    glm::vec3 m_lookAt;
    float m_viewPortH;
    float m_viewPortW;

public:
    glm::vec3 pos;
    glm::vec3 vertical;
    glm::vec3 horizontal;
    glm::vec3 lower_left_corner;
    float focalLength;
    float fov;
};
