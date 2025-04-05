#include <gtest/gtest.h>
#include "utils/rng_utils.hpp"

TEST(RNGUtilsTest, CreatesSeededRNG) {
    auto rng = create_rng(42);
    ASSERT_NE(rng, nullptr);
    auto val = gsl_rng_uniform(rng);
    EXPECT_GE(val, 0.0);
    EXPECT_LT(val, 1.0);
    gsl_rng_free(rng);
}