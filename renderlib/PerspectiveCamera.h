#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera {
    public:

    PerspectiveCamera();
    PerspectiveCamera(point3 origin, vec3 view_dir, double focalLength, 
        double imagePlane_width, double imagePlane_height, int fb_width, int fb_height);

    void generateRay(double i, double j, ray& ray) override;


};