#pragma once

#include "ray.h"
#include "vec3.h"

struct HitRecord {
    point3 p;
    vec3 normal;
    double t;
}; 

#pragma once

#include "ray.h"
#include "vec3.h"

class Shape {

    public:
    Shape();
    
    virtual bool intersect(const ray&r, float tmin, float& tmax) = 0;
};


