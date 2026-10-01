#pragma once

#include "ray.h"
#include "vec3.h"

struct HitRecord;
class Shape {

    public:
    Shape();
    
    virtual bool intersect(const ray&r, float tmin, float& tmax, HitRecord& hit) = 0;
    virtual vec3 getColor() const = 0;
};