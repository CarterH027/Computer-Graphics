#include "vec3.h"
#include "Framebuffer.h"
#include "PerspectiveCamera.h"
#include "ray.h"

#include <iostream>

int main(int argc, char** argv) {

    //variables to play with

    //Framebuffer variables
    int fb_height = 200;
    int fb_width = 200;

    //Camera Variables
    point3 cam_origin = point3(1.0, 3.0, 6.0);
    vec3 cam_viewdir = vec3(-2.0, -1.5, -4.0);
    double camera_focalLength = 0.5;

    //Image Plane variables
    double imagePlane_width = 2.0;
    double imagePlane_height = 2.0;

    //end of variables to play with


    //Where the magic happens :)
    Framebuffer fb = Framebuffer(fb_height, fb_width);

    PerspectiveCamera p(cam_origin, cam_viewdir, camera_focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height);

    for (int x = 0; x < fb_width; ++x){
        for(int y = 0; y < fb_height; ++y){
            ray r;
            p.generateRay(x, y, r);

            color ray_dir_color= 0.5 * (unit_vector(r.direction()) + vec3(1.0,1.0,1.0));

            fb.setPixelColor(x, y, ray_dir_color);

        }
    }

    fb.exportToPNG( "CamRayColors.png");
}