#include "app/SimulationLoop.hpp"
#include <iostream>

SimulationLoop::SimulationLoop(
    Parameters& params,
    std::vector<Molecule>& molecules,
    std::vector<Complex>& complexes,
    Membrane& membrane,
    copyCounters& counters,
    MpiContext& mpi,
    SimulVolume& volume
) : params_(params), molecules_(molecules), complexes_(complexes),
    membrane_(membrane), counters_(counters), mpi_(mpi), volume_(volume) {}

void SimulationLoop::run(long long int startItr, long long int endItr) {
    for (long long int simItr = startItr; simItr <= endItr; ++simItr) {
        step(simItr);
    }
}

void SimulationLoop::step(long long int simItr) {
    std::cout << "[SimulationLoop] Iteration: " << simItr << std::endl;
    // Hook: insert zeroth/first order reactions, communication, etc.
}