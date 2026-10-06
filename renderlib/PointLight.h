#pragma once

#include "vec3.h"
#include "color.h"

class PointLight {
    public:
    PointLight(): c(color(1,1,1)), pos(vec3(0,10,5)), dir(vec3(0,-1,0)) {}
    PointLight(vec3 pos): c(color(1,1,1)), pos(pos), dir(vec3(0,-1,0)) {}
    PointLight(vec3 pos, color c): c(c), pos(pos), dir(vec3(0,-1,0)) {}
    PointLight(vec3 pos, vec3 dir, color c): c(c), pos(pos), dir(dir) {}

    vec3 direction(const vec3& hit_point) const {
        return unit_vector(pos - hit_point);
    }
    vec3 position() const {return this->pos;}
    color getColor() const {return this->c;}

    private:
    vec3 pos;
    vec3 dir;
    color c;
};