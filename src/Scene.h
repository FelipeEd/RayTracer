#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <vector>
#include <memory>
#include "Shapes.h"
#include "Texture.h"
#include "Ray.h"
#include "Light.h"

class Scene : public Shape
{
public:
    std::vector<std::shared_ptr<Texture>> textures;
    std::vector<std::shared_ptr<DATA_materialPhys>> materials;
    std::vector<std::shared_ptr<Shape>> objects;
    std::vector<std::shared_ptr<Light>> lights;

public:
    Scene() {}

    void clear() { objects.clear(); }
    void addShape(std::shared_ptr<Shape> object) { objects.push_back(object); }
    void addTexture(std::shared_ptr<Texture> texture) { textures.push_back(texture); }
    void addMaterial(std::shared_ptr<DATA_materialPhys> material) { materials.push_back(material); }

    std::shared_ptr<Texture> getTexture(unsigned int i) { return textures[i]; }
    std::shared_ptr<DATA_materialPhys> getMaterial(unsigned int i) { return materials[i]; }

    // Tests if the ray hit any of the objects in the scene and saves the hit data on a hit_record struct
    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif