#include "Sphere.h"

Sphere::Sphere(point3 center, float radius) : center(center), radius(radius) {}

bool Sphere::intersect(const ray& r, float tmin, float& tmax) {
    vec3 oc = center - r.origin();

    //my code
    //auto A = dot(r.direction(), r.direction());
    //auto B = -2.0 * dot(r.direction(), oc);
    //auto C = dot((oc), (oc)) - (radius * radius);

    //auto discriminant = (B * B) - (4 * A * C);

    //simplified code from ray tracing in one weekend
    auto A = r.direction().length_squared();
    auto H = dot(r.direction(), oc);
    auto C = oc.length_squared() - radius * radius;

    auto discriminant = H*H - A*C;

    if (discriminant < 0) {
        return false;
    } else {
        return true;
    }
}