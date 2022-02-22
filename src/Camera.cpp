#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float aspectRatio, float FOV)
{
    pos = position;
    m_lookAt = lookat;
    fov = FOV;
    m_up = up;

    m_viewPortH = 2.0f * glm::tan(glm::radians(fov) / 2.0);
    m_viewPortW = aspectRatio * m_viewPortH;

    auto w = glm::normalize(pos - m_lookAt);
    auto u = glm::normalize(glm::cross(m_up, w));
    auto v = cross(w, u);

    vertical = m_viewPortH * v;
    horizontal = m_viewPortW * u;

    lower_left_corner = pos - horizontal / 2.0f - vertical / 2.0f - w;
}

Ray Camera::getRay(float u, float v)
{
    return Ray(pos, lower_left_corner + u * horizontal + v * vertical - pos);
}

void Camera::setPos(glm::vec3 newPos)
{
    pos = newPos;
    auto w = glm::normalize(pos - m_lookAt);
    auto u = glm::normalize(glm::cross(m_up, w));
    auto v = cross(w, u);

    vertical = m_viewPortH * v;
    horizontal = m_viewPortW * u;
    lower_left_corner = pos - horizontal / 2.0f - vertical / 2.0f - w;
}