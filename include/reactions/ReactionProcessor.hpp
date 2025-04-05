#pragma once
#include "classes/class_parameters.hpp"
#include "classes/class_molecule.hpp"
#include "classes/class_complex.hpp"
#include "classes/class_copyCounters.hpp"
#include "classes/class_membrane.hpp"
#include "classes/class_moltemplate.hpp"
#include "reactions/association/association.hpp"
#include "mpi/mpi_function.hpp"
#include <vector>
#include <map>
#include <string>
#include <fstream>

class ReactionProcessor {
public:
    static void performZerothFirstOrder(
        long long int simItr,
        Parameters& params,
        std::vector<Molecule>& molecules,
        std::vector<Complex>& complexes,
        const std::vector<ForwardRxn>& forwardRxns,
        const std::vector<BackRxn>& backRxns,
        const std::vector<CreateDestructRxn>& createDestructRxns,
        const std::vector<MolTemplate>& molTemplates,
        std::map<std::string, int>& observables,
        copyCounters& counters,
        Membrane& membrane,
        std::vector<double>& IL2DbindingVec,
        std::vector<double>& IL2DUnbindingVec,
        std::vector<double>& ILTableIDs,
        MpiContext& mpi,
        std::ofstream& debugOut
    );
};