#include "Camera.h"

Camera::Camera() :
    imagePlane_width(0),
    imagePlane_height(0),
    focalLength(1.0),
    origin(point3(0, 0, 0)),
    view_dir(vec3(0, 0, -1)),
    U(vec3(0, 0, 0)),
    V(vec3(0, 0, 0)),
    W(vec3(0, 0, 0)),
    l(0.0f), r(0.0f), b(0.0f), t(0.0f)
{}

Camera:: Camera(point3 origin, vec3 view_dir, double focalLength,
                double imagePlane_width, double imagePlane_height) :
    origin(origin),
    view_dir(view_dir),
    focalLength(focalLength),
    imagePlane_width(imagePlane_width),
    imagePlane_height(imagePlane_height)
{
    U = vec3(0.0,0.0,0.0);
    V = vec3(0.0,0.0,0.0);
    W = vec3(0.0,0.0,0.0);
    l = r = b = t = 0.0;
}