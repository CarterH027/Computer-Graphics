#pragma once

#include "Shader.h"


class Lambertian : public Shader {
    public:
    Lambertian() = default;

    color rayColor(HitRecord& h, std::vector<PointLight> lights) const override;
};