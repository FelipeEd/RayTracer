#include "Camera.h"

Camera::Camera(float aspectRatio, float FOV)
{
    m_lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 m_right = glm::cross(m_lookAt, m_up);
    float m_aspectRatio = aspectRatio;

    fov = FOV;
    m_viewPortH = 2.0f * glm::tan(glm::radians(fov) / 2.0);
    m_viewPortW = m_aspectRatio * m_viewPortH;

    auto w = glm::normalize(pos - m_lookAt);
    auto u = glm::normalize(glm::cross(m_up, w));
    auto v = cross(w, u);

    pos = glm::vec3(0.0, 1.0, 0.0);
    vertical = m_viewPortH * v;
    horizontal = m_viewPortW * u;
    focalLength = 1.0f;
    lower_left_corner = pos - horizontal / 2.0f - vertical / 2.0f - w;
}

Ray Camera::getRay(float u, float v)
{
    return Ray(pos, lower_left_corner + u * horizontal + v * vertical - pos);
}

void Camera::setPos(glm::vec3 newPos)
{
    pos = newPos;
    glm::vec3 m_up = glm::vec3(0.0, 1.0, 0.0);
    auto w = glm::normalize(pos - m_lookAt);
    auto u = glm::normalize(glm::cross(m_up, w));
    auto v = cross(w, u);

    vertical = m_viewPortH * v;
    horizontal = m_viewPortW * u;
    lower_left_corner = pos - horizontal / 2.0f - vertical / 2.0f - w;
}