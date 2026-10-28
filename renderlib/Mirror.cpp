#include "Mirror.h"

color Mirror::rayColor(HitRecord& hit, const std::vector<std::shared_ptr<Light>>& lights, const Scene& scene, int depth) const {
    vec3 rdir = hit.r.direction();
    vec3 normal = hit.normal;

    vec3 reflection_rayDir = rdir + -(2 * dot(rdir,normal) * normal);
    vec3 reflection_rayOrig = hit.point;

    ray reflection_ray = ray(reflection_rayOrig, reflection_rayDir);

    color reflected_color = scene.computeRayColor(reflection_ray, 0.001, inf, depth - 1);

    return reflected_color;
}