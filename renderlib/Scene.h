#pragma once


#include "hittable.h"
#include "Shape.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "Light.h"
#include "Shader.h"


#include <vector>
#include <limits>
#include <memory>

class Scene {

    public: 

    Scene();
    Scene(color bgColor): bgColor(bgColor), solidbg(true) {}
    Scene(color g1, color g2): bgGradient1(g1), bgGradient2(g2), solidbg(false) {}

    void addShape(std::shared_ptr<Shape>);
    void addLight(std::shared_ptr<Light> light);

    color computeRayColor(const ray& r, float tmin, float tmax);
    bool isShadowed(const ray& r, float tmax, const Shape* currentShape);

    private:
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Light>> lights;
    color bgColor;
    color bgGradient1;
    color bgGradient2;
    bool solidbg;
};