#include "Molecule.h"

namespace stochastic {
    Molecule::Molecule(const std::string &name, double quantity) {
        this->name = name;
        this->quantity = quantity;
    }

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '-=' operator to decrease the quantity of the molecule.
     *
     * @param q The amount by which the quantity of the molecule should be decreased.
     */
    void Molecule::operator-=(double q) {
        Molecule::quantity -= q;
    };

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '+=' operator to increase the quantity of the molecule.
     *
     * @param q The amount by which the quantity of the molecule should be increased.
     */
    void Molecule::operator+=(double q) {
        Molecule::quantity += q;
    }

     /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '+' operator to create a reaction with two molecules as reactants.
     *
     * This function creates a new reaction and adds the current molecule.
     *
     * @param molecule The molecule that reacts with the current molecule.
     * @return The created reaction with the two molecules as reactants.
     */
    Reaction Molecule::operator+(const Molecule &molecule) const {
        auto r = Reaction();
        // dereference the current molecule and add it to the reactants of the reaction
        r.reactants.push_back(*this);
        r.reactants.push_back((molecule));
        return r;
    }

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '+' operator to create a reaction with the current molecule and the reactants of another reaction.
     *
     * This function creates a new reaction and adds the current molecule and the reactants of the reaction.
     *
     * @param reaction The reaction whose reactants will react with the current molecule.
     * @return The created reaction with the current molecule and the reactants of the passed reaction as reactants.
     */
    Reaction Molecule::operator+(const Reaction &reaction) {
        auto r = Reaction();
        r.reactants.push_back(*this);
        for (auto reactant: reaction.reactants) {
            r.reactants.push_back(reactant);
        }

        return r;
    }

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '>>' operator to create a reaction with the current molecule as a reactant and a specified rate.
     *
     * This function creates a new reaction and adds the current molecule as a reactant.
     *
     * @param rate The rate at which the current molecule reacts.
     * @return The created reaction with the current molecule as a reactant and the specified rate.
     */
    Reaction Molecule::operator>>(double rate) const {
        auto reaction = Reaction();
        reaction.reactants.push_back(*this);
        reaction.rate = rate;
        return reaction;
    }
} // stochastic