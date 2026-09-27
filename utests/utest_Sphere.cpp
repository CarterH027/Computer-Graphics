#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "../renderlib/Sphere.h"
#include "../renderlib/ray.h"

TEST_CASE("Intersection Tests"){

    point3 ray_origin = point3(0.0,0.0,0.0);
    Sphere sphere = Sphere(point3(0.0,0.0,-5.0), 1.0);
    float tmin = 0.0;
    float tmax = float(INT_MAX);

    SECTION("Ray intersects"){
        ray r_hit = ray(ray_origin, vec3(0.0,0.0,-1.0));
        REQUIRE(sphere.intersect(r_hit, tmin, tmax) == true);
    }

    SECTION("Ray misses"){
        ray r_miss = ray(ray_origin, vec3(0.0,1.0,0.0));
        REQUIRE(sphere.intersect(r_miss, tmin, tmax) == false);
    }
}