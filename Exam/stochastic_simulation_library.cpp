#include "stochastic_simulation_library.h"

namespace stochastic_simulation_library {
    // Molecule
    Molecule::Molecule(const std::string &name, double quantity) {
        this->name = name;
        this->quantity = quantity;
    }

    std::string Molecule::get_name() const {
        return name;
    };
    void Molecule::set_name(const std::string &n) {
        Molecule::name = n;
    };


    double Molecule::get_quantity() const {
        return quantity;
    };
    void Molecule::set_quantity(double q) {
        Molecule::quantity = q;
    }

    void Molecule::operator-=(double q) {
        Molecule::quantity -= q;
    };

    void Molecule::operator+=(double q){
        Molecule::quantity += q;
    }

    Reaction Molecule::operator+(const Molecule &molecule) const {
        const auto r = new stochastic_simulation_library::Reaction();
        r->add_reactant({*this, molecule});
        return *r;
    }

    Reaction Molecule::operator+(const Reaction &reaction) {
        const auto r = new stochastic_simulation_library::Reaction();
        r->add_reactant({*this});
        r->add_reactant(reaction.reactants);
        return *r;
    }


    // Reaction
    Reaction::Reaction(const std::string &name, double rate, const std::vector<Molecule> &r, const std::vector<Molecule> &p) {
        this->name = name;
        this->rate = rate;
        this->reactants = r;
        this->products = p;
    }
    Reaction::Reaction() {
    }

    std::string Reaction::get_name() const {
        return name;
    };
    void Reaction::set_name(const std::string &n) {
        Reaction::name = n;
    };

    double Reaction::get_rate() const {
        return rate;
    };

    void Reaction::set_rate(double r) {
        Reaction::rate = r;
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

    Reaction Reaction::operator>>(double r) {
        Reaction::rate = r;
        return *this;
    }

    Reaction Reaction::operator>>=(const Molecule &p) {
        Reaction::side = right;
        Reaction::products.push_back(p);
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

    Reaction Reaction::operator>>=(const Environment &env) {
        return Reaction();
    }

    // Vessel
    Vessel::Vessel(const std::vector<Molecule> &molecules, const std::vector<Reaction> &reactions) {
        this->molecules = molecules;
        this->reactions = reactions;
    }

    void Vessel::add_molecule(const Molecule& m) {
        molecules.push_back(m);
    }

    void Vessel::add_reaction(const Reaction& r) {
        reactions.push_back(r);
    }

    Vessel::Vessel(const std::string &name) {
        this->name = name;
    }

    Environment Vessel::environment() {
        return Environment();
    }

    Molecule Vessel::add(std::string name, double quantity) {
        auto m = Molecule(name, quantity);
        molecules.push_back(m);
        return m;
    }

    void Vessel::add(const Reaction &reaction) {
        reactions.push_back(reaction);
    }


    Environment::Environment() {

    }
}
