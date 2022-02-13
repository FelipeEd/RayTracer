#include "Camera.h"

Camera::Camera(float aspectRatio)
{
    m_pos = glm::vec3(0.0);
    m_planeCenter = glm::vec3(0.0, 0.0, 1.0);
    m_up = glm::vec3(0.0, 1.0, 0.0);
    m_right = glm::cross(m_planeCenter, m_up);
    m_fov = 60.0f;
    m_aspectRatio = aspectRatio;

    viewPortH = 2.0f;
    viewPortW = m_aspectRatio * viewPortH;
    focalLength = 1.0f; //! PlaceHolder
}

Camera::~Camera()
{
}