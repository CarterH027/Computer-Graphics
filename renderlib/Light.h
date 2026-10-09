#pragma once

#include "color.h"
#include "vec3.h"

class Light {
    public: 
    virtual vec3 direction(const vec3& hit_point) const =0;
    virtual vec3 position() const = 0;
    virtual color getColor() const = 0;
    virtual float distance(const vec3& hit_point) const = 0;
}; 