#pragma once

#include "ray.h"
#include "vec3.h"

class Shape; 

struct HitRecord {
    point3 point;
    vec3 normal;
    double t;
    const Shape* shape = nullptr;
}; 

