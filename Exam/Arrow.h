#pragma once

#include <vector>
#include <string>

namespace stochastic {

    class Arrow {
    public:
        std::vector<std::string> source;
        std::vector<std::string> target;
        double rate;

        Arrow(std::vector<std::string> src, std::vector<std::string> tgt, double r);

        Arrow() = default;

        ~Arrow() = default;
    };

} // stochastic


