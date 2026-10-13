#pragma once

#include "Shader.h"


class Lambertian : public Shader {
    public:
    Lambertian() = default;

    color rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights, Scene* scene, int depth) const override;
    color rayColor(HitRecord& h, std::shared_ptr<Light> light) const;
};