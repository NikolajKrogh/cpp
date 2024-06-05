//
// Created by krogh on 6/5/24.
//

#include "Molecule.h"

namespace stochastic {
    Molecule::Molecule(const std::string &name, double quantity) {
        this->name = name;
        this->quantity = quantity;
    }

    void Molecule::operator-=(double q) {
        Molecule::quantity -= q;
    };

    void Molecule::operator+=(double q) {
        Molecule::quantity += q;
    }

    Reaction Molecule::operator+(const Molecule &molecule) const {
        auto r = Reaction();
        // Add the current molecule and the molecule passed as an argument as reactants
        r.reactants.push_back(*this);
        r.reactants.push_back((molecule));
        return r;
    }

    Reaction Molecule::operator+(const Reaction &reaction) {
        auto r = Reaction();
        // Add the current molecule and the reactants of the reaction passed as an argument as reactants
        r.reactants.push_back(*this);
        for (auto reactant: reaction.reactants) {
            r.reactants.push_back(reactant);
        }


        return r;
    }

    Reaction Molecule::operator>>(double rate) const {
        auto reaction = Reaction();
        // Add the current molecule as a reactant
        reaction.reactants.push_back(*this);
        reaction.rate = rate;
        return reaction;
    }
} // stochastic