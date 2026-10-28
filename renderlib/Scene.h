#pragma once


#include "hittable.h"
#include "Shape.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "Light.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "Lambertian.h"
#include "BlinnPhong.h"
#include "Mirror.h"
#include "NormalShader.h"
#include "Sphere.h"
#include "Triangle.h"


#include <vector>
#include <limits>
#include <memory>

class Scene {
    friend class SceneLoader;

    public: 

    Scene(): bgColor(color(0.5,0.7,1.0)), solidbg(true) {}
    Scene(color bgColor): bgColor(bgColor), solidbg(true) {}
    Scene(color g1, color g2): bgGradient1(g1), bgGradient2(g2), solidbg(false) {}


    void addCamera(std::shared_ptr<Camera>);
    void addShape(std::shared_ptr<Shape>);
    void addLight(std::shared_ptr<Light> light);

    color computeRayColor(const ray& r, float tmin, float tmax, int depth) const;
    bool isShadowed(const ray& r, float tmax) const;

    std::shared_ptr<Camera> cam;

    private:
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<Light>> lights;
    color bgColor;
    color bgGradient1;
    color bgGradient2;
    bool solidbg;
};