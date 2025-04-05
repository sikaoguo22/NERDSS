#pragma once

#include "system_setup/system_setup.hpp"
#include "classes/class_parameters.hpp"
#include "classes/class_molecule.hpp"
#include "classes/class_complex.hpp"
#include "classes/class_membrane.hpp"
#include "classes/class_copyCounters.hpp"
#include "mpi/mpi_function.hpp"

class SimulationApp {
public:
    SimulationApp(int argc, char** argv);
    ~SimulationApp();

    void init();
    void run();
    void finalize();

private:
    int argc_;
    char** argv_;
    // Parameters params_;
    MpiContext mpi_context_;
    // std::vector<Molecule> molecules_;
    // std::vector<Complex> complexes_;
    // copyCounters counters_;
    // Membrane membrane_;
};