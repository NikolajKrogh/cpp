#pragma once

namespace stochastic {

    class ParallelSimulation {
    public:

        template<class Observer>
        static void parallelize_simulations(std::vector<Vessel> vessels, Observer observer, double simulation_time, bool output_to_file = false) {
            std::vector<std::thread> threads;

            // For each vessel, assign a unique filename and start a simulation in a new thread.
            for (auto &v: vessels) {
                std::string path = Simulation::Simulation::assign_unique_filename(v.name);
                threads.push_back(std::thread(Simulation::simulate<Observer>, path, std::ref(v), observer, simulation_time, output_to_file));
            }

            // Wait for all simulations to finish.
            for (auto &thread: threads) {
                thread.join();
            }
        }
    };

} // stochastic
