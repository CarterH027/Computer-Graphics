#pragma once

#include "ray.h"
#include "vec3.h"

class Shader;
class Shape; 

struct HitRecord {
    ray r;
    point3 point;
    vec3 normal;
    double t;
    const Shape* shape = nullptr;
    const Shader* shader = nullptr;
}; 

