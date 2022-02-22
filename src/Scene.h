#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <vector>
#include <memory>
#include "Shapes.h"
#include "Material.h"
#include "Ray.h"
#include "Light.h"

class Scene : public Shape
{
public:
    std::vector<std::shared_ptr<Shape>> objects;
    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Light>> lights;

public:
    Scene() {}

    void clear() { objects.clear(); }
    void addShape(std::shared_ptr<Shape> object) { objects.push_back(object); }
    void addMaterial(std::shared_ptr<Material> material) { materials.push_back(material); }

    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif