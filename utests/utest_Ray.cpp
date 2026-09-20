#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../renderlib/ray.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Ray Initialization") {

    point3 origin = point3(1.0,2.0,3.0);
    vec3 direction = vec3(3.0,2.0,1.0);
    ray r = ray(origin, direction);

    REQUIRE_THAT(r.origin().x(), WithinAbs(1.0, 0.001));
    REQUIRE_THAT(r.origin().y(), WithinAbs(2.0, 0.001));
    REQUIRE_THAT(r.origin().z(), WithinAbs(3.0, 0.001));

    REQUIRE_THAT(r.direction().x(), WithinAbs(3.0, 0.001));
    REQUIRE_THAT(r.direction().y(), WithinAbs(2.0, 0.001));
    REQUIRE_THAT(r.direction().z(), WithinAbs(1.0, 0.001));

}

TEST_CASE("Parametric line calculation"){

    point3 origin = point3(1.0,2.0,3.0);
    vec3 direction = vec3(3.0,2.0,1.0);
    ray r = ray(origin, direction);
    
    double t = 1.5;

    point3 point_on_ray = r.at(t);

    REQUIRE_THAT(point_on_ray.x(), WithinAbs(5.5, 0.001));
    REQUIRE_THAT(point_on_ray.y(), WithinAbs(5.0, 0.001));
    REQUIRE_THAT(point_on_ray.z(), WithinAbs(4.5, 0.001));
    
}