#include "Arrow.h"

namespace stochastic {

/**
 * @brief Constructs a new Arrow object.
 *
 * The Arrow object represents a reaction in the system, with source molecules, target molecules, and a reaction rate.
 *
 * @param src A vector of source molecules' Graphviz tags, represented as strings.
 * @param tgt A vector of target molecules' Graphviz tags, represented as strings.
 * @param r The rate of the reaction, represented as a double.
 */
Arrow::Arrow(std::vector<std::string> src, std::vector<std::string> tgt, double r) {

    // Iterating over the source vector and adding each source to the Arrow's source vector
    for (auto &s: src) {
        this->source.push_back(s);
    }

    // Iterating over the target vector and adding each target to the Arrow's target vector
    for (auto &t: tgt) {
        this->target.push_back(t);
    }

    // Setting the rate of the Arrow (reaction)
    this->rate = r;
}

} // stochastic