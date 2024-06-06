#pragma once

#include <string>
#include "Vessel.h"

namespace stochastic {

    class Simulation {
    public:
        static void simulate(const std::string &path, Vessel &vessel, double end_time);
        static std::string assign_unique_filename(const std::string &name);

        static bool can_react(Vessel &vessel, Reaction &reaction);

        static void perform_reaction(Vessel &vessel, Reaction &reaction);
    };
} // stochastic


