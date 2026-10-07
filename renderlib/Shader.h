#pragma once

#include "vec3.h"
#include "color.h"
#include "hittable.h"
#include "Light.h"
#include <vector>

class Shader {
    public:
    Shader() = default;

    virtual color rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights) const = 0;
};