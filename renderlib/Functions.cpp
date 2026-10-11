#include "Functions.h"
#include <random>

float randomOffset() {
    
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distrib(0.0, 1.0);

    return distrib(gen);
}