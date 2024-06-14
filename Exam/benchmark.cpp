#include <iostream>
#include <iomanip>
#include "benchmark.h"

namespace stochastic {
    /**
 * ------------------  Exercise 10 ------------------
 * @brief Starts a new benchmark.
 *
 * This function starts a new benchmark with the given name. It records the current time as the start time of the benchmark.
 * The benchmark is represented as a `time_point` object, which is added to the `time_points` vector.
 *
 * @param name The name of the benchmark. This name is used to identify the benchmark when stopping it and reporting its duration.
 */
    void Benchmark::start(const std::string &name) {
        time_point tp;
        tp.name = name;
        tp.start = std::chrono::high_resolution_clock::now();
        time_points.push_back(tp);
    }

    /**
 * ------------------  Exercise 10 ------------------
 * @brief Stops a running benchmark.
 *
 * This function stops a running benchmark with the given name. It records the current time as the stop time of the benchmark.
 * The benchmark is represented as a `time_point` object, which is updated in the `time_points` vector.
 *
 * @param name The name of the benchmark. This name is used to identify the benchmark when stopping it and reporting its duration.
 */
    void Benchmark::stop(const std::string &name) {
        for (auto &tp: time_points) {
            if (tp.name == name) {
                tp.stop = std::chrono::high_resolution_clock::now();
                return;
            }
        }
    }

/**
 * ------------------  Exercise 10 ------------------
 * @brief Reports the duration of all benchmarks.
 *
 * This function iterates over all the `time_point` objects in the `time_points` vector, calculates the duration of each benchmark,
 * and prints the name of the benchmark and its duration in milliseconds and seconds to the standard output.
 */
    void Benchmark::report() {
        for (const auto &tp: time_points) {
            std::chrono::duration<double, std::milli> duration = tp.stop - tp.start;
            std::cout << tp.name << " took " << duration.count() << " ms ("
                      << std::fixed << std::setprecision(1) << duration.count()/1000 << " seconds)" << std::endl;

        }
    }
}