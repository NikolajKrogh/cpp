#include "Reaction.h"

namespace stochastic {
    Reaction::Reaction(const std::string &name, double rate, const std::vector<Molecule> &r,
                       const std::vector<Molecule> &p) {
        this->name = name;
        this->rate = rate;
        this->reactants = r;
        this->products = p;
    }

    Reaction::Reaction() = default;


    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '>>' operator to set the rate of the reaction.
     *
     * The rate of a reaction is a measure of how quickly the reactants turn into products.
     *
     * @param r The new rate of the reaction.
     * @return The modified reaction with the updated rate.
     */
    Reaction Reaction::operator>>(double r) {
        Reaction::rate = r;
        return *this;
    }


    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '+' operator to add a molecule to the reaction.
     *
     * This function adds a molecule to either the reactants or the products of the reaction,
     * depending on the current side. If the current side is 'left', the molecule is added to the reactants.
     * If the current side is 'right', the molecule is added to the products.
     *
     * @param m The molecule to be added to the reaction.
     * @return The modified reaction with the added molecule.
     */
    Reaction Reaction::operator+(const Molecule &m) {
        if (Reaction::side == left) {
            Reaction::reactants.push_back(m);
        } else {
            Reaction::products.push_back(m);
        }
        return *this;
    }

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '>>=' operator to add a product molecule to the reaction.
     *
     * This function sets the current side to 'right' and adds a molecule to the products of the reaction.
     *
     * @param p The product molecule to be added to the reaction.
     * @return The modified reaction with the added product molecule.
     */
    Reaction Reaction::operator>>=(const Molecule &p) {
        Reaction::side = right;
        Reaction::products.push_back(p);
        return *this;
    }

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '>>=' operator to clear the products of the reaction.
     *
     * This function clears all the product molecules from the reaction when an environment is passed.
     *
     * @param env The environment, which when passed, triggers the clearing of the products.
     * @return The modified reaction with the cleared products.
     */
    Reaction Reaction::operator>>=(const Environment &env) {
        this->products.clear();
        return *this;
    }

    /**
     * ------------------  Exercise 1 ------------------
     * @brief Overloads the '>>=' operator to replace the products of the current reaction with the reactants of another reaction.
     *
     * This function replaces the products of the current reaction with the reactants of the passed reaction.
     *
     * @param reaction The reaction whose reactants will replace the products of the current reaction.
     * @return The modified reaction with the replaced products.
     */
    Reaction Reaction::operator>>=(const Reaction &reaction) {
        Reaction::products = reaction.reactants;
        return *this;
    }
} // stochastic