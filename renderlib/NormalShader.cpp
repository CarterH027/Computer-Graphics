#include "NormalShader.h"

color NormalShader:: rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights) const {
    color finalColor = 0.5 * (h.normal + vec3(1.0,1.0,1.0));
    return finalColor;
}