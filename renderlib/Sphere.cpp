#include "Sphere.h"

Sphere::Sphere(point3 center, float radius) : center(center), radius(radius) {}

bool Sphere::intersect(const ray& r, float tmin, float& tmax) {
    vec3 e_minus_c = r.origin() - center;

    double A = dot(r.direction(), r.direction());
    double B = dot((r.direction() * 2),(e_minus_c));
    double C = dot((e_minus_c), (e_minus_c)) - (radius * radius);

    float discriminant = (B * B) - (4 * A * C);

    if (discriminant < 0) {
        return false;
    } else {
        return true;
    }
}