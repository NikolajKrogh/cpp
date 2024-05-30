#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
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

    void Molecule::operator+=(double q) {
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

    Reaction Molecule::operator>>(double rate) const {
        auto reaction = new Reaction();
        reaction->add_reactant({*this});
        reaction->set_rate(rate);
        return *reaction;
    }


    // Reaction
    Reaction::Reaction(const std::string &name, double rate, const std::vector<Molecule> &r,
                       const std::vector<Molecule> &p) {
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
        for (auto &molecule: r) {
            reactants.push_back(molecule);
        }
    }

    void Reaction::add_product(std::initializer_list<Molecule> p) {
        for (auto &molecule: p) {
            products.push_back(molecule);
        }
    }

    void Reaction::add_reactant(const std::vector<Molecule> &r) {
        for (auto &molecule: r) {
            reactants.push_back(molecule);
        }
    }

    void Reaction::add_product(const std::vector<Molecule> &p) {
        for (auto &molecule: p) {
            products.push_back(molecule);
        }
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
        return Reaction();
    }

    Reaction Reaction::operator>>=(const Reaction &reaction) {
        Reaction::products = reaction.reactants;
        return *this;
    }

    // Vessel
    Vessel::Vessel(const std::vector<Molecule> &molecules, const std::vector<Reaction> &reactions) {
        this->molecules = molecules;
        this->reactions = reactions;
    }

    void Vessel::add_molecule(const Molecule &m) {
        molecules.push_back(m);
    }

    void Vessel::add_reaction(const Reaction &r) {
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

    void Vessel::pretty_print() {


    }


void Vessel::network_graph() {
    std::vector<Arrow> arrows;
    int count = 0;
    for (auto &molecule: molecules) {
        molecule.graphviz_tag = "s" + std::to_string(count);
        count++;
    }
    // Check if molecule is in the reaction
    for (const auto &molecule: molecules) {
        for (const auto &reaction: reactions) {
            for (const auto &reactant: reaction.reactants) {
                if (reactant.get_name() == molecule.get_name()) {
                    std::vector<std::string> v_products = {};
                    for (const auto &product: reaction.products) {
                        v_products.push_back(product.get_name());
                    }
                    std::vector<std::string> v = {};
                    for (const auto &m: molecules) {
                        for (const auto p: v_products) {
                            if (m.get_name() == p) {
                                v.push_back(m.graphviz_tag);
                            }
                        }
                    }
                    auto arrow = Arrow(molecule.graphviz_tag, v, reaction.get_rate());
                    arrows.push_back(arrow);
                }
            }
        }
    }

    std::ofstream file("/home/krogh/CLionProjects/cpp/Exam/output.dot");
    file << "digraph {" << std::endl;
    int count2 = 0;
    for (const auto &molecule: molecules) {
        file << molecule.graphviz_tag << "[label=\"" << molecule.get_name()
             << "\",shape=\"box\",style=\"filled\",fillcolor=\"cyan\"];" << std::endl;
    }
    for (const auto &arrow: arrows) {
        file << "r" << count2 << "[label=\"" << arrow.rate
             << "\",shape=\"oval\",style=\"filled\",fillcolor=\"yellow\"];" << std::endl;
        file << arrow.source << "->" << "r" << count2 << std::endl;

        for (const auto &target : arrow.target){
            file << "r" << count2 << "->" << target << std::endl;
        }
        count2++;
    }
    file << "}" << std::endl;
    file.close();
}


    Environment::Environment() {

    }

    Arrow::Arrow(std::string src, std::vector<std::string> tgt, double r) {

        // Using move to avoid copying the string
        source = std::move(src);
        for (auto &t: tgt) {
            target.push_back(t);
        }
        rate = r;
    }
}
