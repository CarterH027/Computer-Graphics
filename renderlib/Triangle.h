#pragma once

#include "hittable.h"
#include "Shape.h"
#include "NormalShader.h"

class Triangle : public Shape {

    public:
    Triangle(): point_a(vec3(0,0,0)), point_b(vec3(1,0,0)), point_c(vec3(0,1,0)), shader(std::make_shared<NormalShader>()) {}
    Triangle(const vec3& a, const vec3& b, const vec3& c) : point_a(a), point_b(b), point_c(c), shader(std::make_shared<NormalShader>()) {}
    Triangle(const vec3& a, const vec3& b, const vec3& c, std::shared_ptr<Shader> shader) : point_a(a), point_b(b), point_c(c), shader(shader) {}

    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) override;

    private:

    std::shared_ptr<Shader> shader;
    point3 point_a, point_b, point_c;
};