#include "vec3.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"
#include "Shape.h"
#include "Sphere.h"

#include <iostream>

int main(int argc, char** argv) {

    //variables to play with

    //Framebuffer variables
    int fb_height = 200;
    int fb_width = 200;

    //Camera Variables
    point3 cam_origin = point3(0.0, 0.0, 0.0);
    vec3 cam_viewdir = vec3(0.0, 0.0, -1.0);
    double camera_focalLength = 1.0;

    //Image Plane variables
    double imagePlane_width = 0.5;
    double imagePlane_height = 0.5;

    //Colors
    color bgColor = color(1.0,1.0,1.0);

    //Shapes 
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(point3(0,0,-5), 0.5);

    //Tvals
    float tmin = 0.0;
    float tmax = float(INT_MAX);
    //end of variables to playwith


    //Where the magic happens :)
    Framebuffer fb = Framebuffer(fb_height, fb_width);

    PerspectiveCamera p(cam_origin, cam_viewdir, camera_focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height);

    for (int x = 0; x < fb_width; ++x){
        for(int y = 0; y < fb_height; ++y){
            ray r;
            p.generateRay(x, y, r);

            if (s->intersect( r, tmin, tmax)) {
                fb.setPixelColor(x, y, color(1.0, 0.0, 0.0));
            } else {
                fb.setPixelColor(x, y, bgColor);
            }

        }
    }

    fb.exportToPNG( "JapaneseFlag.png");
}