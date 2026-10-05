#include "Shape.h"
#include "Lambertian.h"
#include <algorithm>

color Lambertian::rayColor(HitRecord& h, std::vector<PointLight> lights) const {
    //for now just going to give it one singular light
    //so it will be hardcoded in for the moment to test shading
    PointLight light = PointLight(vec3(0,10,4), color(1,1,1));

    double nDotl = std::max(0.0, dot(h.normal, light.direction(h.point)));
    color finalColor = h.shape->getColor() * nDotl;
    return finalColor;
}