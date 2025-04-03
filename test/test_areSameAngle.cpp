#include <gtest/gtest.h>
#include "utils/angle_utils.hpp"

TEST(AreSameAngleTest, IdenticalAngles) {
    EXPECT_TRUE(areSameAngle(1.0, 1.0));
    EXPECT_TRUE(areSameAngle(0.0, 0.0));
    EXPECT_TRUE(areSameAngle(-3.14159, -3.14159));
}

TEST(AreSameAngleTest, NearlyIdenticalAngles) {
    EXPECT_TRUE(areSameAngle(2.0, 2.0 + 1e-9));
    EXPECT_TRUE(areSameAngle(-2.5, -2.5 - 1e-9));
}

TEST(AreSameAngleTest, DifferentAngles) {
    EXPECT_FALSE(areSameAngle(1.0, 1.0001));
    EXPECT_FALSE(areSameAngle(0.0, 1e-6));
    EXPECT_FALSE(areSameAngle(-1.0, 1.0));
}
