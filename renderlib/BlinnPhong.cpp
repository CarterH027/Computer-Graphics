#include "Shape.h"
#include "BlinnPhong.h"

#include <algorithm>

color BlinnPhong::rayColor(HitRecord& hit, std::vector<std::shared_ptr<Light>> lights) const {
    

    
    color finalColor = color(0,0,0);
    for(const auto& light : lights){
        color lambertianComponent = Lambertian().rayColor(hit, light);
        vec3 halfVector = unit_vector(-hit.r.direction() + light->direction(hit.point));

        auto nDoth_p = std::pow(std::max(0.0,dot(hit.normal,halfVector)), phongExp);
        
        color lightColor = light->getColor();
        auto x = specCoefficient.x() * lightColor.x() * nDoth_p;
        auto y = specCoefficient.y() * lightColor.y() * nDoth_p;
        auto z = specCoefficient.z() * lightColor.z() * nDoth_p;

        color litColor = lambertianComponent + color(x,y,z);

        finalColor += litColor;
    }

    return finalColor;
}