#ifndef SCENE_H
#define SCENE_H

#pragma once
#include <vector>
#include <memory>
#include "Visible.h"
#include "Ray.h"
#include "Light.h"

class Scene : public Visible
{
public:
    std::vector<std::shared_ptr<Visible>> objects;
    std::vector<std::shared_ptr<Light>> lights;

public:
    Scene() {}

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Visible> object) { objects.push_back(object); }

    virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;
};

#endif