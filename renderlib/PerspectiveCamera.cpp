#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(point3 origin, vec3 view_dir, double focalLength,
                                        double imagePlane_width, double imagePlane_height, int fb_width, int fb_height)
    : Camera(origin, view_dir, focalLength, imagePlane_width, imagePlane_height, fb_width, fb_height) 
{
    l = -imagePlane_width/2;
    r = imagePlane_width/2;
    b = -imagePlane_height/2;
    t = imagePlane_height/2;

    W = -view_dir/view_dir.length();
    vec3 temp_up = vec3(0,1,0);
    U = (cross(temp_up, W))/(temp_up.length() * W.length());
    V = cross(W,U);
}

void PerspectiveCamera::generateRay(int i, int j, ray& ray) {
    double u = l + (r - l)*(i + 0.5)/fb_width;
    double v = b + (t - b)*(j + 0.5)/fb_height;

    vec3 direction = (-focalLength * W) + (u * U) + (v * V);
    ray.setDir(direction);
    ray.setOrig(origin);
}