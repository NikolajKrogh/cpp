#pragma once


#include <vector>
#include <chrono>
#include <string>

namespace stochastic {

    class Benchmark {
    public:
        void start(const std::string &name);

        void stop(const std::string &name);

        void report();

    private:
        struct time_point {
            std::string name;
            std::chrono::high_resolution_clock::time_point start;
            std::chrono::high_resolution_clock::time_point stop;
        };
        std::vector<time_point> time_points;
    };

}
