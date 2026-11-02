#include "BoundingBox.h"
#include <algorithm>

bool BoundingBox::intersect(const ray& r, float tmin, float& tmax, HitRecord& hit) { 
    

    float invX = 1.0f / r.direction().x();
    float invY = 1.0f / r.direction().y();
    float invZ = 1.0f / r.direction().z();


    float tx_min = (x_min - r.origin().x()) * invX;
    float tx_max = (x_max - r.origin().x()) * invX;
    if (invX < 0.0f) std::swap(tx_min, tx_max);

    float ty_min = (y_min - r.origin().y()) * invY;
    float ty_max = (y_max - r.origin().y()) * invY;
    if (invY < 0.0f) std::swap(ty_min, ty_max);

    float t_enter = std::max(tx_min, ty_min);
    float t_leave = std::min(tx_max, ty_max);
    if (t_enter > t_leave) return false;

    float tz_min = (z_min - r.origin().z()) * invZ;
    float tz_max = (z_max - r.origin().z()) * invZ;
    if (invZ < 0.0f) std::swap(tz_min, tz_max);

    t_enter = std::max(t_enter, tz_min);
    t_leave = std::min(t_leave, tz_max);
    if (t_enter > t_leave) return false;

    float t_hit_start = std::max(t_enter, tmin);
    float t_hit_end = std::min(t_leave, tmax);

    if (t_hit_start > t_hit_end) {
        return false;
    }

    if (t_leave < tmin || t_enter > tmax) {return false;}

    

    return true;

}