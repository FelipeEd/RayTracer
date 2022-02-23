#include "Texture.h"

glm::vec3 Solid::getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const
{
    return m_flatColor;
}

glm::vec3 Checker::getPigment(glm::vec3 hitPoint, glm::vec3 shapePos) const
{
    bool oddX = (int)glm::floor((hitPoint.x - shapePos.x) / m_cubeSize) % 2 != 0;
    bool oddY = (int)glm::floor((hitPoint.y - shapePos.y) / m_cubeSize) % 2 != 0;
    bool oddZ = (int)glm::floor((hitPoint.z - shapePos.z) / m_cubeSize) % 2 != 0;

    // even = false

    if (oddX && oddY && oddZ)
        return m_firstColor;
    else if ((oddX ^ oddY ^ oddZ)) // (a ^ b ^ c) && !(a && b && c) triple XOR
        return m_firstColor;
    else
        return m_secondColor;
}
