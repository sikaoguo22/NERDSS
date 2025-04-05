#pragma once
#include <gsl/gsl_rng.h>

inline gsl_rng* create_rng(unsigned seed) {
    const gsl_rng_type* T = gsl_rng_default;
    gsl_rng* r = gsl_rng_alloc(T);
    gsl_rng_set(r, seed);
    return r;
}