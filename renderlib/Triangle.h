#pragma once

#include "hittable.h"

class Triangle : public Shape {

    public:
    Triangle();
    Triangle(point3 point_a, point3 point_b, point3 point_c);

    bool intersect(const ray& r, float tmin, float& tmax) override;

    private:

    point3 point_a, point_b, point_c;
};