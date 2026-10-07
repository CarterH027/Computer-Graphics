#include "Shape.h"
#include "Lambertian.h"
#include <algorithm>

color Lambertian::rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights) const {
   
    color finalColor = color(0.0,0.0,0.0);

    for(const auto& light : lights){
        double nDotl = std::max(0.0, dot(h.normal, light->direction(h.point)));

        auto x = h.shape->getColor().x() * light->getColor().x();
        auto y = h.shape->getColor().y() * light->getColor().y();
        auto z = h.shape->getColor().z() * light->getColor().z();

        color litColor = color(x,y,z);

        finalColor += litColor *nDotl;
    }

    return finalColor;
}

color Lambertian::rayColor(HitRecord& h, std::shared_ptr<Light> light) const {
    double nDotl = std::max(0.0, dot(h.normal, light->direction(h.point)));

    auto x = h.shape->getColor().x() * light->getColor().x();
    auto y = h.shape->getColor().y() * light->getColor().y();
    auto z = h.shape->getColor().z() * light->getColor().z();

    
    return color(x,y,z) * nDotl;
}