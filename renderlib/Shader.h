#pragma once

#include "vec3.h"
#include "color.h"
#include "hittable.h"
#include "PointLight.h"
#include <vector>

class Shader {
    public:
    Shader() = default;

    virtual color rayColor(HitRecord& h, std::vector<PointLight> lights) const = 0;
};