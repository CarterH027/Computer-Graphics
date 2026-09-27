#pragma once

#include "Shape.h"

class Sphere : public Shape {

    public: 
    Sphere();
    Sphere(point3 center, float radius);

    bool intersect(const ray& r, float tmin, float& tmax) override;

    private:

    point3 center;
    float radius;
};