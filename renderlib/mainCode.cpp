#include "vec3.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "hittable.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Shape.h"

#include <memory>
#include <limits>
#include <vector>
#include <iostream>


vec3 computeRayColor(const ray& r, const std::vector<std::shared_ptr<Shape>> &shapes) {
    float tmin = 0.001f;
    float tmax = std::numeric_limits<float>::max();

    HitRecord closestHit;
    closestHit.t = tmax;
    bool hitAnything = false;

    for (const auto &shape: shapes) {
        HitRecord tempHit;
        if (shape->intersect(r, tmin, tmax, tempHit)) {
            if (tempHit.t < closestHit.t) {
                closestHit = tempHit;
                hitAnything = true;
                tmax = tempHit.t;
            }
        }
    }

    //normal loop color get
    //if (hitAnything) {
    //    return closestHit.shape->getColor();
    //}

    //normal shaded shapes
    if (hitAnything) {
        return (unit_vector(closestHit.normal) + vec3(1.0,1.0,1.0)) * 0.5;
    }

    //background color
    //Can play with this too!!
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * vec3(1.0,1.0,1.0) + a * vec3(0.5,0.7,1.0);
}

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

    //Shapes 
    std::vector<std::shared_ptr<Shape>> shapes;

    //shape definitions
    shapes.push_back(std::make_shared<Sphere>(
        vec3(0.0, 0.0, -11.0), 1.0f, vec3(0.1,0.9,0.1)));

    // Red Triangle 1
    shapes.push_back(std::make_shared<Triangle>(
    vec3(-1.2, -0.2, -7), vec3(0.8, -0.5, -5), vec3(0.9, 0, -5),
    vec3(1.0, 0.0, 0.0)));

    // Green Triangle 2
    shapes.push_back(std::make_shared<Triangle>(
    vec3(0.773205, -0.93923, -7), vec3(0.0330127, 0.94282, -5), vec3(-0.45, 0.779423, -5),
    vec3(0.0, 1.0, 0.0)));

    // Blue Triangle 3
    shapes.push_back(std::make_shared<Triangle>(
    vec3(0.426795, 1.13923, -7), vec3(-0.833013, -0.44282, -5), vec3(-0.45, -0.779423, -5),
    vec3(0.0, 0.0, 1.0)));

    //end of variables to play with


    //Where the magic happens :)
    Framebuffer fb = Framebuffer(fb_height, fb_width);

    PerspectiveCamera p(cam_origin, cam_viewdir, camera_focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height);

    for (int x = 0; x < fb_width; ++x){
        for(int y = 0; y < fb_height; ++y){
            ray r;
            p.generateRay(x, y, r);
            vec3 pixelColor = computeRayColor(r, shapes);
            fb.setPixelColor(x,y, pixelColor);


        }
    }

    fb.exportToPNG("normal_shadingCrazy.png");

    return 0;
}