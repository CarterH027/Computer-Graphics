#pragma once

#include "Shape.h"
#include "hittable.h"
#include <limits>

class BoundingBox{
    public:
    BoundingBox() {
        float inf = std::numeric_limits<float>::infinity();
        x_min = inf; y_min = inf; z_min = inf;
        x_max = -inf; y_max = -inf; z_max = -inf;
    } 
    BoundingBox(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) : x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax), z_min(zmin), z_max(zmax) {}
    bool intersect(const ray& r, float tmin, float& tmax, HitRecord& hit);


    float x_min, x_max;
    float y_min, y_max;
    float z_min, z_max;
};