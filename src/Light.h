#pragma once

#include <glm\glm.hpp>

class Light
{
public:
    Light(glm::vec3 pos,
          glm::vec3 color,
          float constAtt,
          float pDist,
          float pDist2) : m_pos(pos),
                          m_color(color),
                          m_constAtt(constAtt),
                          m_pDist(pDist),
                          m_pDist2(pDist2) {}

public:
    glm::vec3 m_pos;
    glm::vec3 m_color;

    float m_constAtt; // Constant attenuation
    float m_pDist;    // Attenuation proportional to the distance
    float m_pDist2;   // Attenuation proportional to the square of distance
};
