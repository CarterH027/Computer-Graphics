#pragma once

#include "Shader.h"
#include "PointLight.h"


class Lambertian : public Shader {
    public:
    Lambertian() = default;

    color rayColor(HitRecord& h, std::vector<PointLight> lights) const override;
};