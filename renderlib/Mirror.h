#pragma once

#include "Shape.h"
#include "Shader.h"
#include "Scene.h"
#include <limits>

class Mirror : public Shader{
    public:
    Mirror() = default;

    color rayColor(HitRecord& h, const std::vector<std::shared_ptr<Light>>& lights, const Scene& scene, int depth) const override;

    private:
    float inf = std::numeric_limits<float>::max();
};