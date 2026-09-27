#pragma once

#include "ray.h"
#include "vec3.h"

class Shape {

    public:
    Shape();
    
    virtual bool intersect(const ray&r, float tmin, float& tmax) = 0;
};