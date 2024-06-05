//
// Created by krogh on 6/5/24.
//

#include "Arrow.h"

namespace stochastic {

/**
 * The Arrow object represents a reaction in the system, with a source molecule, target molecules, and a reaction rate.
 *
 * @param src The source molecule's Graphviz tag, represented as a string.
 * @param tgt A vector of target molecules' Graphviz tags, represented as strings.
 * @param r The rate of the reaction, represented as a double.
 */
    Arrow::Arrow(std::vector<std::string> src, std::vector<std::string> tgt, double r) {

        // Using std::move to avoid copying the string
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