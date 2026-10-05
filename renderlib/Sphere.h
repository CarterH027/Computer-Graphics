#pragma once

#include "hittable.h"
#include "Shape.h"

class Sphere : public Shape {

    public: 
    Sphere(): center(vec3(0,0,0)), radius(1.0), color(vec3(1.0, 1.0, 1.0)) {}
    Sphere(point3 center, float radius): center(center), radius(radius), color(vec3(1.0,1.0,1.0)) {}
    Sphere(point3 center, float radius, vec3 color): center(center), radius(radius), color(color) {}
    Sphere(point3 center, float radius, vec3 color, std::shared_ptr<Shader> shader): center(center), radius(radius), color(color), shader(shader){}

    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) override;
    vec3 getColor() const override;
    private:

    std::shared_ptr<Shader> shader;
    point3 center;
    float radius;
    vec3 color;
};