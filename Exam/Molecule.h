#pragma once

#include <string>
#include "Reaction.h"

namespace stochastic {

    class Reaction;

    class Molecule {
    public:
        std::string name;
        double quantity;
        std::string graphviz_tag;

        Molecule(const std::string &name, double quantity);

        ~Molecule() = default;

        void operator-=(double quantity);

        void operator+=(double quantity);

        Reaction operator+(const Molecule &molecule) const;

        Reaction operator+(const Reaction &reaction);

        Reaction operator>>(double reaction_rate) const;
    };

} // stochastic


