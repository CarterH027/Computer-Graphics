#include "Sphere.h"

bool Sphere::intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) {
    vec3 oc = r.origin() - center;

    //my code
    float A = dot(r.direction(), r.direction());
    float B = 2.0 * dot(oc, r.direction());
    float C = dot((oc), (oc)) - (radius * radius);

    float discriminant = (B * B) - (4 * A * C);


    if (discriminant < 0) {
        return false;
    }
    float sqrt_disc = std::sqrt(discriminant);

    /*the rest of the quadratic (commented in because I didn't know what
    * this did when I first saw it) */
    float t1 = (-B - sqrt_disc) / (2.0f * A);
    float t2 = (-B + sqrt_disc) / (2.0f *A);

    if (t1 > tmin && t1 < tmax) {
        tmax = t1;
        hit.t = t1;
        hit.point = r.at(t1);
        hit.shape = this;
        hit.normal = (hit.point - center) / radius;
        hit.shader = shader.get();
        return true;
    }

    if (t2 > tmin && t2 < tmax) {
        tmax = t2;
        hit.t = t2;
        hit.point = r.at(t2);
        hit.shape = this;
        hit.normal = (hit.point - center) / radius;
        hit.shader = shader.get();
        return true;
    }

    return false;
}

vec3 Sphere::getColor() const {
    return color;
}