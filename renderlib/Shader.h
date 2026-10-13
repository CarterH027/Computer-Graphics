#pragma once

#include "vec3.h"
#include "color.h"
#include "hittable.h"
#include "Light.h"
#include <vector>

class Scene;

class Shader {
    public:
    Shader() = default;

    virtual color rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights, Scene* scene, int depth) const = 0;
};