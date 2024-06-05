//
// Created by krogh on 6/5/24.
//

#ifndef EXAM_PARALLELSIMULATION_H
#define EXAM_PARALLELSIMULATION_H

namespace stochastic {

    class ParallelSimulation {
    public:
        static void parallelize_simulations(std::vector<Vessel> vessels, double T) {
            std::vector<std::thread> threads;

            for (auto &v: vessels) {
                std::string path = Simulation::Simulation::assign_unique_filename(v.name);
                threads.push_back(std::thread(Simulation::simulate, path, std::ref(v), T));
            }

            for (auto &thread: threads) {
                thread.join();
            }
        }

    };


} // stochastic

#endif //EXAM_PARALLELSIMULATION_H
