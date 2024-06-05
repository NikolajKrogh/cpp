//
// Created by krogh on 6/5/24.
//

#pragma once

#include <string>
#include "Vessel.h"

namespace stochastic {

    class Simulation {
    public:
        static void simulate(const std::string &p,Vessel &vessel, double end_time);
        static std::string assign_unique_filename(const std::string &name);

    };
} // stochastic


