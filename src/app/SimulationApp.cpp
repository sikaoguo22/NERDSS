#include "app/SimulationApp.hpp"
#include <iostream>

SimulationApp::SimulationApp(int argc, char** argv)
    : argc_(argc), argv_(argv), mpi_context_(0, 50000000) {}

SimulationApp::~SimulationApp() {
    // Free memory, write final state, etc.
}

void SimulationApp::init() {
    // Parse input, initialize RNG, prepare data structures
    std::cout << "[Init] Simulation setup.\n";
}

void SimulationApp::run() {
    std::cout << "[Run] Simulation loop.\n";
}

void SimulationApp::finalize() {
    std::cout << "[Finalize] Cleaning up.\n";
}