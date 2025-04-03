#pragma once
#include <cmath>

inline bool areSameAngle(double ang1, double ang2) {
    return std::abs(ang1 - ang2) < 1E-8;
}