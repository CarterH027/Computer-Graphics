#include "Triangle.h"

Triangle::Triangle(point3 point_a, point3 point_b, point3 point_c) : 
        point_a(point_a), point_b(point_b), point_c(point_c){}

bool Triangle::intersect(const ray& r, float tmin, float& tmax) {
    //math
    double a = point_a.x() - point_b.x();
    double b = point_a.y() - point_b.y();
    double c = point_a.z() - point_b.z();

    double d = point_a.x() - point_c.x(); 
    double e = point_a.y() - point_c.y();
    double f = point_a.z() - point_c.z();

    double g = -r.direction().x();
    double h = -r.direction().y();
    double i = -r.direction().z();

    double j = point_a.x() - r.origin().x();
    double k = point_a.y() - r.origin().y();
    double l = point_a.z() - r.origin().z();

    //more math to simplify later equations
    double ei_minus_hf = e * i - h * f;
    double gf_minus_di = g * f - d * i;
    double dh_minus_eg = d * h - e * g;
    double ak_minus_jb = a * k - j * b;
    double jc_minus_al = j * c - a * l;
    double bl_minus_kc = b * l - k * c;

    //the actual "stuff"
    auto M = (a * ei_minus_hf) + (b * gf_minus_di) + (c * dh_minus_eg);

    auto t = ((f * ak_minus_jb) + (e * jc_minus_al) + (d * bl_minus_kc)) / M;

    if (t < tmin || t > tmax) {
        return false;
    } 

    auto gamma = ((i * ak_minus_jb) + (h * jc_minus_al) + (g * bl_minus_kc)) / M;

    if (gamma < 0 || gamma > 1) {
        return false;
    }

    auto beta = ((j * ei_minus_hf) + (k * gf_minus_di) + (l * dh_minus_eg)) / M;

    if (beta < 0 || beta > (1 - gamma)) {
        return false;
    } else {
        return true;
    }
}