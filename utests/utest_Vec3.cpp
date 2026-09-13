#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../renderlib/vec3.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Dot product computes correctly") {

    vec3 v = vec3(.5, .25, .3);
    vec3 u = vec3(.75, .6, .9);
    
    REQUIRE_THAT( dot(v, u), WithinAbs(.795, 0.001));
    REQUIRE_THAT( dot(u, v), WithinAbs(.795, 0.001));

}

TEST_CASE("Cross product computes correctly") {

    vec3 v = vec3(0.5, 0.25, 0.3);
    vec3 u = vec3(0.75, 0.6, 0.9);

    vec3 result_1 = cross(v,u);
    vec3 result_2 = cross(u,v);
    

    
    SECTION("v to u computation") {
        INFO("v to u. Actual x: " << result_1[0]);
        REQUIRE_THAT(result_1[0], WithinAbs(.045, .000001));
        INFO("v to u. Actual y: " << result_1[1]);
        REQUIRE_THAT(result_1[1], WithinAbs(-0.225, .000001));
        INFO("v to u. Actual z: " << result_1[2]);
        REQUIRE_THAT(result_1[2], WithinAbs(0.1125, .000001));
    }

    SECTION("u to v computation") {
        INFO("u to v. Actual x: " << result_2[0]);
        REQUIRE_THAT(result_2[0], WithinAbs(-0.045, .000001));
        INFO("u to v. Actual y: " << result_2[1]);
        REQUIRE_THAT(result_2[1], WithinAbs(0.225, .000001));
        INFO("u to v. Actual z: " << result_2[2]);
        REQUIRE_THAT(result_2[2], WithinAbs(-0.1125, .000001));
    }
}

TEST_CASE("Basic vec3 function") {
    vec3 v = vec3(0.5, 0.25, 0.3);
    vec3 u = vec3(0.75, 0.6, 0.9);

    SECTION("Length"){
        REQUIRE_THAT(v.length(), WithinAbs(.6344, .0001));
    }

    SECTION("Index"){
        REQUIRE_THAT(v[0], WithinAbs(.5, .0001));
        REQUIRE_THAT(v[1], WithinAbs(.25, .0001));
        REQUIRE_THAT(v[2], WithinAbs(.3, .0001));
    }
 
}

TEST_CASE("Basic Operations") {
    vec3 v = vec3(0.5, 0.25, 0.3);
    vec3 u = vec3(0.75, 0.6, 0.9);

    SECTION("Addition"){
        vec3 t = v + u;

        REQUIRE_THAT(t[0], WithinAbs(1.25, 0.0001));
        REQUIRE_THAT(t[1], WithinAbs(0.85, 0.0001));
        REQUIRE_THAT(t[2], WithinAbs(1.2, 0.0001));
    }
    SECTION("Subtraction"){
        vec3 t = v - u;

        REQUIRE_THAT(t[0], WithinAbs(-0.25, 0.0001));
        REQUIRE_THAT(t[1], WithinAbs(-0.35, 0.0001));
        REQUIRE_THAT(t[2], WithinAbs(-0.6, 0.0001));
    }
    SECTION("Multiplication"){
        vec3 t = v * 2;

        REQUIRE_THAT(t[0], WithinAbs(1.0, 0.0001));
        REQUIRE_THAT(t[1], WithinAbs(0.5, 0.0001));
        REQUIRE_THAT(t[2], WithinAbs(0.6, 0.0001));
    }
    SECTION("Division"){
        vec3 t = v/2;

        REQUIRE_THAT(t[0], WithinAbs(.25, 0.0001));
        REQUIRE_THAT(t[1], WithinAbs(0.125, 0.0001));
        REQUIRE_THAT(t[2], WithinAbs(.15, 0.0001));
    }

}

TEST_CASE("Unit Vector"){
    vec3 v = vec3(0.5, 0.25, 0.3);

    vec3 v_unit = unit_vector(v);
    
    REQUIRE_THAT(v_unit.length(), WithinAbs(1, 0.001));
    
}
