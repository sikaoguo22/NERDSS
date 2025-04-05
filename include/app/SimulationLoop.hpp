#pragma once

#include "classes/class_parameters.hpp"
#include "classes/class_molecule.hpp"
#include "classes/class_complex.hpp"
#include "classes/class_membrane.hpp"
#include "classes/class_copyCounters.hpp"
#include "mpi/mpi_function.hpp"
#include "system_setup/simul_volume.hpp"

class SimulationLoop {
public:
    SimulationLoop(
        Parameters& params,
        std::vector<Molecule>& molecules,
        std::vector<Complex>& complexes,
        Membrane& membrane,
        copyCounters& counters,
        MpiContext& mpi,
        SimulVolume& volume
    );

    void run(long long int startItr, long long int endItr);

private:
    Parameters& params_;
    std::vector<Molecule>& molecules_;
    std::vector<Complex>& complexes_;
    Membrane& membrane_;
    copyCounters& counters_;
    MpiContext& mpi_;
    SimulVolume& volume_;

    void step(long long int simItr);
};