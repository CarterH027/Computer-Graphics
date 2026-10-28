#pragma once

#include "hittable.h"
#include "Shape.h"
#include "NormalShader.h"

class Sphere : public Shape {

    public: 
    Sphere(): center(vec3(0,0,0)), radius(1.0), shader(std::make_shared<NormalShader>()) {}
    Sphere(point3 center, float radius): center(center), radius(radius), shader(std::make_shared<NormalShader>()) {}
    Sphere(point3 center, float radius, std::shared_ptr<Shader> shader): center(center), radius(radius), shader(shader){}

    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) override;
    private:

    std::shared_ptr<Shader> shader;
    point3 center;
    float radius;
};