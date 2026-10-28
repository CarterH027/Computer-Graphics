#include "NormalShader.h"
color NormalShader:: rayColor(HitRecord& h, const std::vector<std::shared_ptr<Light>>& lights, const Scene& scene, int depth) const {
    color finalColor = 0.5 * (h.normal + vec3(1.0,1.0,1.0));
    return finalColor;
}