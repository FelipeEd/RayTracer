#include "Shapes.h"

bool Polyhedron::hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const
{
    float mindist = t_max;
    float T = -1.0f;
    for (auto face : m_faces)
    {

        glm::vec3 planeN = -glm::vec3(face);
        float d = face.w;

        glm::vec3 p0 = d * planeN / glm::dot(planeN, planeN);

        float num = glm::dot((p0 - ray.origin), planeN);
        float denom = glm::dot(ray.dir, planeN);

        if (denom > 1e-6)
        {
            float t = num / denom;
            if (t > 0.0f)
            {
                glm::vec3 p = ray.at(t);
                float dist = glm::distance(p, ray.origin);

                if (dist < t_max)
                {
                    mindist = dist;
                    T = t;
                    rec.t = t;
                    rec.p = ray.at(rec.t);
                    glm::vec3 outward_normal = glm::normalize(planeN);
                    rec.set_face_normal(ray, outward_normal);
                    rec.texColor = m_texture->getPigment(rec.p, planeN);
                    rec.material = m_material;
                    return true;
                }
            }
        }
    }

    return false;
}