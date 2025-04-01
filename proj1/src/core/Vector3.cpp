#include "Vector3.h"
#include <random>

Vector3 Vector3::random(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return Vector3(distribution(generator), distribution(generator), distribution(generator));
} 