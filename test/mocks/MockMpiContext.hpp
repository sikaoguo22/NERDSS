#pragma once
#include "mpi/mpi_function.hpp"

class MockMpiContext : public MpiContext {
public:
    MockMpiContext() : MpiContext(1, 1000) {
        rank = 0;
        nprocs = 1;
        simItr = 0;
    }
};