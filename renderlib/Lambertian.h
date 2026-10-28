#pragma once

#include "Shader.h"
#include "color.h"

class Lambertian : public Shader {
    public:
    Lambertian() : shader_color(color(1.0,0.2,0.2)) {}
    Lambertian(color col) : shader_color(col) {}

    color rayColor(HitRecord& h, const std::vector<std::shared_ptr<Light>>& lightss, const Scene& scene, int depth) const override;
    color rayColor(HitRecord& h, std::shared_ptr<Light> light) const;

    private:
    color shader_color;
};