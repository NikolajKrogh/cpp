#include "stochastic_simulation_library.h"

namespace stochastic_simulation_library {
    // Molecule
    Molecule::Molecule(std::string name, double quantity) {
        this->name = name;
        this->quantity = quantity;
    }

    std::string Molecule::get_name() const {
        return name;
    };
    void Molecule::set_name(std::string name) {
        Molecule::name = name;
    };


    double Molecule::get_quantity() const {
        return quantity;
    };
    void Molecule::set_quantity(double quantity) {
        Molecule::quantity = quantity;
    };

    // Reaction
    Reaction::Reaction(std::string name, double rate, std::vector<Molecule> reactants, std::vector<Molecule> products) {
        this->name = name;
        this->rate = rate;
        this->reactants = reactants;
        this->products = products;
    }

    std::string Reaction::get_name() const {
        return name;
    };
    void Reaction::set_name(std::string name) {
        Reaction::name = name;
    };

    double Reaction::get_rate() const {
        return rate;
    };

    void Reaction::set_rate(double rate) {
        Reaction::rate = rate;
    };

    void Reaction::add_reactant(std::initializer_list<Molecule> r) {
        for (auto &molecule : r) {
            reactants.push_back(molecule);
        }
    }

    void Reaction::add_product(std::initializer_list<Molecule> p) {
        for (auto &molecule : p) {
            products.push_back(molecule);
        }
    }

    void Reaction::add_reactant(const std::vector<Molecule> &r) {
        for (auto &molecule : r) {
            reactants.push_back(molecule);
        }
    }

    void Reaction::add_product(const std::vector<Molecule> &p) {
        for (auto &molecule : p) {
            products.push_back(molecule);
        }
    }

    // Vessel
    Vessel::Vessel(std::vector<Molecule> molecules, std::vector<Reaction> reactions) {
        this->molecules = molecules;
        this->reactions = reactions;
    }

    void Vessel::add_molecule(Molecule molecule) {
        molecules.push_back(molecule);
    }

    void Vessel::add_reaction(Reaction reaction) {
        reactions.push_back(reaction);
    }

}
