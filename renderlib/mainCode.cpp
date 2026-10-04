#include "vec3.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "hittable.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Shape.h"
#include "Scene.h"

#include <memory>
#include <limits>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {

    //variables to play with

    //Framebuffer variables
    int fb_height = 500;
    int fb_width = 500;

    //Camera Variables
    point3 cam_origin = point3(0.0, 0.0, 0.0);
    vec3 cam_viewdir = vec3(0.0, 0.0, -1.0);
    double camera_focalLength = 1.0;

    //Image Plane variables
    double imagePlane_width = 0.5;
    double imagePlane_height = 0.5;

    //Colors for sky background gradient
    color bg1 = color(1.0,1.0,1.0);
    color bg2 = color(0.5,0.7,1.0);


    Framebuffer fb = Framebuffer(fb_height, fb_width);
    std::shared_ptr<Camera> cam = std::make_shared<PerspectiveCamera>(cam_origin, cam_viewdir, camera_focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height);

    Scene scene = Scene(bg1, bg2);

    //shape definitions
    scene.addShape(
        std::make_shared<Triangle>(
             vec3(-1.2, -0.2, -7), vec3(0.8, -0.5, -5), vec3(0.9, 0, -5), vec3(1.0, 0.0, 0.0)
        )
    );
    scene.addShape(
        std::make_shared<Triangle>(
            vec3(0.773205, -0.93923, -7), vec3(0.0330127, 0.94282, -5), vec3(-0.45, 0.779423, -5), vec3(0.0, 1.0, 0.0)
        )
    );
    scene.addShape(
        std::make_shared<Triangle>(
            vec3(0.426795, 1.13923, -7), vec3(-0.833013, -0.44282, -5), vec3(-0.45, -0.779423, -5), vec3(0.0, 0.0, 1.0)
        )
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

    fb.exportToPNG("Scene_refactor.png");

    return 0;
}