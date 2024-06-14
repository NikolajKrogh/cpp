#pragma once

namespace stochastic {

    class ParallelSimulation {
    public:
        /**
         * ------------------  Exercise 8 ------------------
         * @brief Runs simulations in parallel for multiple vessels.
         *
         * This function runs simulations for multiple vessels in parallel. Each simulation is run in a separate thread.
         * If the `output_to_file` parameter is `true`, a unique filename is assigned to each vessel and the results of the simulation are written to a file.
         * The function waits for all simulations to finish before returning.
         *
         * @tparam Observer The type of the observer function that is called at each time step in the simulation.
         * @param vessels A vector of vessels for which simulations will be run.
         * @param observer The observer function that is called at each time step in the simulation.
         * @param simulation_time The total time for which the simulation will be run.
         * @param output_to_file A boolean value indicating whether the results of the simulation should be written to a file.
         */
        template<class Observer>
        static void parallelize_simulations(std::vector<Vessel> vessels, Observer observer, double simulation_time, bool output_to_file = false) {
            std::vector<std::thread> threads;
            std::string path;
            // For each vessel, assign a unique filename and start a simulation in a new thread.
            for (auto &v: vessels) {
                if (output_to_file) {
                    path = Simulation::Simulation::assign_unique_filename(v.name);
                }
                threads.push_back(std::thread(Simulation::simulate<Observer>, path, std::ref(v), observer, simulation_time, output_to_file));
            }

            // Wait for all simulations to finish.
            for (auto &thread: threads) {
                thread.join();
            }
        }
    };

} // stochastic
