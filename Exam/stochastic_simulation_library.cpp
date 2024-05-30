#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "stochastic_simulation_library.h"

namespace stochastic_simulation_library {
#pragma region Molecule

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
        // Add the current molecule and the molecule passed as an argument as reactants
        r->add_reactant({*this, molecule});
        return *r;
    }

    Reaction Molecule::operator+(const Reaction &reaction) {
        const auto r = new stochastic_simulation_library::Reaction();
        // Add the current molecule and the reactants of the reaction passed as an argument as reactants
        r->add_reactant({*this});
        r->add_reactant(reaction.reactants);
        return *r;
    }

    Reaction Molecule::operator>>(double rate) const {
        auto reaction = new Reaction();
        // Add the current molecule as a reactant
        reaction->add_reactant({*this});
        reaction->set_rate(rate);
        return *reaction;
    }

#pragma endregion Molecule

#pragma region Reaction

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
        this->products.clear();
        return *this;
    }

    Reaction Reaction::operator>>=(const Reaction &reaction) {
        Reaction::products = reaction.reactants;
        return *this;
    }

#pragma endregion Reaction

#pragma region Vessel

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

    /**
 * First prints the total number of reactions.
 * Then for each reaction, it prints the names of the reactants, the reaction rate, and the names of the products.
 * If a reactant or product is not the last one in its list, a plus sign is printed after its name.
 * If there are no products for a reaction, it prints '∅'.
 */
    void Vessel::pretty_print() {

        // Iterate over each reaction
        for (const auto &reaction: reactions) {
            for (auto &reactant: reaction.reactants) {
                std::cout << reactant.get_name();

                // If the reactant is not the last one, print a plus sign
                if (&reactant != &reaction.reactants.back()) {
                    std::cout << " + ";
                }
            }

            // Print the reaction rate
            std::cout << " -> " << reaction.get_rate() << " -> ";

            // Print products
            if (reaction.products.empty()) {
                std::cout << "∅";
            } else {
                // If there are products, print each one
                for (size_t i = 0; i < reaction.products.size(); ++i) {
                    std::cout << reaction.products[i].get_name();
                    // If the product is not the last one, print a plus sign
                    if (i != reaction.products.size() - 1) {
                        std::cout << " + ";
                    }
                }
            }

            std::cout << std::endl;
        }
    }

/**
 * Assigns a unique tag to each molecule in the vessel
 */
    void Vessel::assign_tags_to_molecules() {
        int count = 0;
        for (auto &molecule: molecules) {
            molecule.graphviz_tag = "s" + std::to_string(count);
            count++;
        }
    }

/**
 * iterates over each molecule and each reaction in the vessel.
 * If a molecule is a reactant in a reaction, it creates an Arrow object representing the reaction,
 * with the source being the reactant's Graphviz tag, the target being the Graphviz tags of the products, and the rate being the reaction rate.
 * These Arrow objects are stored in a vector which is returned by the method.
 * @return A vector of Arrow objects representing the reactions in the vessel.
 */
    std::vector<Arrow> Vessel::create_arrows() {
        std::vector<Arrow> arrows;
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
        return arrows;
    }

/**
 * Writes the graph to a file in the DOT language.
 * The file is named output.dot and is written to the root of the project.
 */
    void Vessel::write_to_file(const std::vector<Arrow> &arrows) {
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

            for (const auto &target: arrow.target) {
                file << "r" << count2 << "->" << target << std::endl;
            }
            count2++;
        }
        file << "}" << std::endl;
        file.close();
    }

    void Vessel::network_graph() {
        assign_tags_to_molecules();
        std::vector<Arrow> arrows = create_arrows();
        write_to_file(arrows);
    }

#pragma endregion Vessel

#pragma region Environment

    Environment::Environment() {

    }

#pragma endregion Environment

#pragma region Arrow

    Arrow::Arrow(std::string src, std::vector<std::string> tgt, double r) {

        // Using move to avoid copying the string
        source = std::move(src);
        for (auto &t: tgt) {
            target.push_back(t);
        }
        rate = r;
    }

#pragma endregion Arrow

    SymbolTable::SymbolTable() {

    }
}


