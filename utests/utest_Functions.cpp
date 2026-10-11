#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../renderlib/Functions.h"
#include <iostream>

TEST_CASE("Random number generator") {
    float rand = randomOffset();

    std::cout << rand << std::endl;

}