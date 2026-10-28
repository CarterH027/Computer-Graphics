#include "Functions.h"
#include <random>

float randomOffset() {
    
    thread_local std::mt19937 generator(std::random_device{}());

    thread_local std::uniform_real_distribution<float> distrib(0.0, 1.0);

    return distrib(generator);
}