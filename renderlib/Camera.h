#pragma once

#include "vec3.h"
#include "ray.h"


class Camera {
    public: 

    Camera();
    Camera(point3 origin, vec3 view_dir, double focalLength,
         double imagePlane_width, double imagePlane_height);
    virtual void generateRay(double i, double j, ray& ray, int fb_width, int fb_height) = 0;
    

    protected:

    double imagePlane_width;
    double imagePlane_height;
    double focalLength;
    point3 origin;
    vec3 view_dir;
    vec3 U, V, W;
    float l, r, b, t;
};