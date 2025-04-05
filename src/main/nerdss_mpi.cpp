#include "app/SimulationApp.hpp"

// TODO: Remove the following global variables
#include "math/rand_gsl.hpp"
gsl_rng* r;
/**
 * @var randNum
 * @brief Global variable to store a random number.
 */
long long randNum = 0;

/**
 * @var totMatches
 * @brief Global variable to store the total number of matches.
 */
unsigned long totMatches = 0;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    SimulationApp app(argc, argv);
    app.init();
    app.run();
    app.finalize();

    MPI_Finalize();
    return 0;
}