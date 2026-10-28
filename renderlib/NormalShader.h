#pragma once

#include "Shader.h"

class NormalShader : public Shader {
    public:
    NormalShader() = default;

    color rayColor(HitRecord& h, const std::vector<std::shared_ptr<Light>>& lights, const Scene& scene, int depth) const override;
}; 