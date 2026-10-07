#pragma once

#include "Shader.h"
#include "Lambertian.h"

class BlinnPhong : public Shader {
    public:
    BlinnPhong(): phongExp(1.0), specCoefficient(color(1.0,1.0,1.0)) {}
    BlinnPhong(float pe): phongExp(pe), specCoefficient(color(1.0,1.0,1.0)) {}
    BlinnPhong(float pe, color sc): phongExp(pe), specCoefficient(sc) {}

    color rayColor(HitRecord& h, std::vector<std::shared_ptr<Light>> lights) const override;

    private:
    float phongExp;
    color specCoefficient;
    

};