//
// Created by krogh on 6/5/24.
//

#include "Reaction.h"

namespace stochastic {
    Reaction::Reaction(const std::string &name, double rate, const std::vector<Molecule> &r,
                       const std::vector<Molecule> &p) {
        this->name = name;
        this->rate = rate;
        this->reactants = r;
        this->products = p;
    }

    Reaction::Reaction() {
    }


    Reaction Reaction::operator>>(double r) {
        Reaction::rate = r;
        return *this;
    }


    Reaction Reaction::operator+(const Molecule &m) {
        if (Reaction::side == left) {
            Reaction::reactants.push_back(m);
        } else {
            Reaction::products.push_back(m);
        }
        return *this;
    }

    Reaction Reaction::operator>>=(const Molecule &p) {
        Reaction::side = right;
        Reaction::products.push_back(p);
        return *this;
    }

    Reaction Reaction::operator>>=(const Environment &env) {
        this->products.clear();
        return *this;
    }

    Reaction Reaction::operator>>=(const Reaction &reaction) {
        Reaction::products = reaction.reactants;
        return *this;
    }
} // stochastic