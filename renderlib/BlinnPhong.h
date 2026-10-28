#pragma once

#include "Shader.h"
#include "Lambertian.h"
#include "color.h"

class BlinnPhong : public Shader {
    public:
    BlinnPhong(): phongExp(1.0), specCoefficient(color(1.0,1.0,1.0)), shader_color(color(1.0,0.2,0.2)) {}
    BlinnPhong(float pe): phongExp(pe), specCoefficient(color(1.0,1.0,1.0)), shader_color(color(1.0,0.2,0.2)) {}
    BlinnPhong(float pe, color sc): phongExp(pe), specCoefficient(sc), shader_color(color(1.0,0.2,0.2)) {}
    BlinnPhong(float pe, color sc, color col): phongExp(pe), specCoefficient(sc), shader_color(col) {}


    color rayColor(HitRecord& h, const std::vector<std::shared_ptr<Light>>& lights, const Scene& scene, int depth) const override;

    private:
    float phongExp;
    color specCoefficient;
    color shader_color;
    

};