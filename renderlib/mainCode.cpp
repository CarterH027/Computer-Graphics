#include "vec3.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "hittable.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Shape.h"
#include "Scene.h"
#include "Shader.h"
#include "Lambertian.h"
#include "BlinnPhong.h"
#include "Light.h"
#include "PointLight.h"

#include <memory>
#include <limits>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {

    int fb_height = 500;
    int fb_width = 500;
    point3 cam_origin = point3(0.0, 2.0, 0.0);
    vec3 cam_viewdir = vec3(0.0, -0.3, -1.0);
    double camera_focalLength = 1.0;
    double imagePlane_width = 0.5;
    double imagePlane_height = 0.5;
    Framebuffer fb = Framebuffer(fb_height, fb_width);
    std::shared_ptr<Camera> cam = std::make_shared<PerspectiveCamera>(cam_origin, cam_viewdir, camera_focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height);

    //Colors for sky background gradient
    color bg1 = color(1.0,1.0,1.0);
    color bg2 = color(0.5,0.7,1.0);

    //textures
    auto lambertian = std::make_shared<Lambertian>();
    auto glossy = std::make_shared<BlinnPhong>(200);
    auto satin = std::make_shared<BlinnPhong>(16);


    Scene scene = Scene(bg1, bg2);
    //floor sphere?
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(0, -100.5, -1.0), 100, color(0.25, 0.25, 0.25), lambertian
        )
    );

    color sphereColor = color(0.1,0.67,.15);
    //shape definitions
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(0, 0, -7), 0.5, sphereColor, glossy
        )
    );
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(-1, 0, -7), 0.5, sphereColor, lambertian
        )
    );
    scene.addShape(
        std::make_shared<Sphere>(
            vec3(1, 0, -7), 0.5, sphereColor, satin
        )
    );
    
    //lights 
    scene.addLight(
        std::make_shared<PointLight>(vec3(-5, 3.0, -6), color(0.8,0.85,0.9))
    );
    scene.addLight(
        std::make_shared<PointLight>(vec3(5, 3.0, -6), color(0.25,0.25, 0.25))
    );

    //end of variables to play with

    float inf = std::numeric_limits<float>::max();

    for (int x = 0; x < fb_width; ++x){
        for(int y = 0; y < fb_height; ++y){
            ray r;
            cam->generateRay(x, y, r);
            color c = scene.computeRayColor(r, 1.0, inf);
            fb.setPixelColor(x, y ,c);
        }
    }

    fb.exportToPNG("Glossy_sphere.png");

    return 0;
}