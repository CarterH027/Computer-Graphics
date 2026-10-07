#pragma once

#include "Shader.h"

class NormalShader : public Shader {
    public:
    NormalShader() = default;

    color rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights) const override;
}; 