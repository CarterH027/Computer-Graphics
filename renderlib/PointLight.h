#pragma once

#include "Light.h"

class PointLight: public Light {
    public:
    PointLight(): c(color(1,1,1)), pos(vec3(0,10,5)), dir(vec3(0,-1,0)) {}
    PointLight(vec3 pos): c(color(1,1,1)), pos(pos), dir(vec3(0,-1,0)) {}
    PointLight(vec3 pos, color c): c(c), pos(pos), dir(vec3(0,-1,0)) {}
    PointLight(vec3 pos, vec3 dir, color c): c(c), pos(pos), dir(dir) {}

    vec3 direction(const vec3& hit_point) const override {
        return unit_vector(pos - hit_point);
    }
    vec3 position() const override {return this->pos;}
    color getColor() const override {return this->c;}

    private:
    vec3 pos;
    vec3 dir;
    color c;
};