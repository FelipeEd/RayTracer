#include "Shapes.h"

bool Sphere::hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const
{
    glm::vec3 oc = ray.origin - this->pos;
    float a = glm::dot(ray.dir, ray.dir);
    float half_b = dot(oc, ray.dir);
    float c = glm::dot(oc, oc) - r * r;

    float discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    rec.normal = (rec.p - this->pos) / r;
    rec.texColor = m_texture->getPigment(rec.p, pos);
    rec.material = m_material;

    return true;
}