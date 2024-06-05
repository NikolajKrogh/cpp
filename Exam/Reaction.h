//
// Created by krogh on 6/5/24.
//

#ifndef EXAM_REACTION_H
#define EXAM_REACTION_H

#include <string>
#include <vector>
#include "Molecule.h"
#include "Environment.h"

namespace stochastic {

    // Required to avoid circular dependencies
    class Molecule;

    // Use enum to check if we should add the reactants to the left or right side of the reaction
    typedef enum {
        left,
        right
    } reaction_side;

    class Reaction {
    public:
        std::string name;
        double rate;
        reaction_side side = left;
        std::vector<Molecule> products;
        std::vector<Molecule> reactants;
        double delay;

        Reaction(const std::string &name, double rate, const std::vector<Molecule> &reactants,
                 const std::vector<Molecule> &products);

        Reaction();

        ~Reaction() = default;

        Reaction operator>>(double reaction_rate);

        Reaction operator+(const Molecule &molecule);

        Reaction operator>>=(const Molecule &products);

        Reaction operator>>=(const Environment &env);

        Reaction operator>>=(const Reaction &reaction);

    };


} // stochastic

#endif //EXAM_REACTION_H
