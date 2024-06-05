//
// Created by krogh on 6/5/24.
//

#pragma once

#include <string>
#include "Vessel.h"

namespace stochastic {

    class Simulation {
    public:
        static void simulate(const std::string &path, Vessel &vessel, double end_time);
        static std::string assign_unique_filename(const std::string &name);

        static bool canReact(Vessel &vessel, Reaction &reaction);

        static void performReaction(Vessel &vessel, Reaction &reaction);
    };
} // stochastic


