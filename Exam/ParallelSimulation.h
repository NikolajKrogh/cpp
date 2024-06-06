#pragma once

namespace stochastic {

    class ParallelSimulation {
    public:
/**
 * @brief Runs simulations in parallel for a given set of vessels.
 *
 * This function creates a separate thread for each vessel and runs the simulation in parallel.
 * Each simulation is assigned a unique filename based on the vessel's name.
 * After all simulations are started, the function waits for all of them to finish before returning.
 *
 * @param vessels A vector of vessels for which the simulations will be run.
 * @param simulation_time The total simulation time.
 */
        static void parallelize_simulations(std::vector<Vessel> vessels, double simulation_time) {
            std::vector<std::thread> threads;

            // For each vessel, assign a unique filename and start a simulation in a new thread.
            for (auto &v: vessels) {
                std::string path = Simulation::Simulation::assign_unique_filename(v.name);
                threads.push_back(std::thread(Simulation::simulate, path, std::ref(v), simulation_time));
            }

            // Wait for all simulations to finish.
            for (auto &thread: threads) {
                thread.join();
            }
        }

    };


} // stochastic
