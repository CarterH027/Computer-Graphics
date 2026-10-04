#pragma once


#include "hittable.h"
#include "Shape.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"


#include <vector>
#include <limits>
#include <memory>

class Scene {

    public: 

    Scene();
    Scene(color bgColor): bgColor(bgColor), solidbg(true) {}
    Scene(color g1, color g2): bgGradient1(g1), bgGradient2(g2), solidbg(false) {}

    void addShape(std::shared_ptr<Shape>);
    //void addLight()

    color computeRayColor(const ray& r, float tmin, float tmax);

    private:
    std::vector<std::shared_ptr<Shape>> shapes;
    //std::vector<lights> lights
    color bgColor;
    color bgGradient1;
    color bgGradient2;
    bool solidbg;
};