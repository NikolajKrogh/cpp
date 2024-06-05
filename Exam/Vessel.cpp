//
// Created by krogh on 6/5/24.
//

#include <iostream>
#include <set>
#include <fstream>
#include "Vessel.h"
#include "Arrow.h"

namespace stochastic {
    Vessel::Vessel(const std::string &name) {
        this->name = name;
    }

    Environment Vessel::environment() {
        return Environment();
    }

    Molecule &Vessel::add(const std::string &name, double quantity) {
        auto m = new Molecule(name, quantity);
        molecules.insert(name, m);
        return *m;
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
                std::cout << reactant.name;

                // If the reactant is not the last one, print a plus sign
                if (&reactant != &reaction.reactants.back()) {
                    std::cout << " + ";
                }
            }

            // Print the reaction rate
            std::cout << " -> " << reaction.rate << " -> ";

            // Print products
            if (reaction.products.empty()) {
                std::cout << "∅";
            } else {
                // If there are products, print each one
                for (size_t i = 0; i < reaction.products.size(); ++i) {
                    std::cout << reaction.products[i].name;
                    // If the product is not the last one, print a plus sign
                    if (i != reaction.products.size() - 1) {
                        std::cout << " + ";
                    }
                }
            }

            std::cout << std::endl;
        }
    }


    void Vessel::get_digraph() {

        std::vector<Arrow> arrows;

        int counter2 = 0;
        //Assign Graphiz tags to molecules

        SymbolTable<std::string, std::string> table;
        for (auto &r: reactions) {
            for (auto &m: r.reactants) {
                if (!table.contains(m.name)) {
                    table.insert(m.name, ("s" + std::to_string(counter2++)));
                }
            }
            for (auto &m: r.products) {
                if (!table.contains(m.name)) {
                    table.insert(m.name, ("s" + std::to_string(counter2++)));
                }
            }
        }
        //loop over all reactions
        for (const auto &r: reactions) {
            Arrow arrow = {};
            std::vector<std::string> reactant_names = {};
            for (const auto &reactant: r.reactants) {
                reactant_names.push_back(table.get(reactant.name));
            }
            std::vector<std::string> product_names = {};

            for (const auto &product: r.products) {
                product_names.push_back(table.get(product.name));
            }
            arrow.rate = r.rate;
            arrow.source = reactant_names;
            arrow.target = product_names;
            arrows.push_back(arrow);
        }

        std::ofstream file;
        std::string path = "/home/krogh/CLionProjects/cpp/Exam/" + name + ".dot";
        file.open(path);
        if (!file) {
            std::cerr << "Unable to open file for writing.\n";
            return;
        }

        file << "digraph {\n";
        int counter = 0;
        std::set<std::string> u_sets;
        for (const auto &r: reactions) {
            for (const auto &reactant: r.reactants) {
                auto p = u_sets.insert(table.get(reactant.name));
                if (p.second) {
                    file << table.get(reactant.name) << "[label=\"" << reactant.name
                         << R"(",shape="box",style="filled",fillcolor="cyan"];)" << '\n';
                }
            }

            for (const auto &product: r.products) {
                auto p = u_sets.insert(table.get(product.name));
                if (p.second) {
                    file << table.get(product.name) << "[label=\"" << product.name
                         << R"(",shape="box",style="filled",fillcolor="cyan"];)" << '\n';
                }
            }

        }


        for (const auto &arrow: arrows) {
            file << "r" << counter << "[label=\"" << arrow.rate
                 << R"(",shape="oval",style="filled",fillcolor="yellow"];)"
                 << '\n';
            for (const auto &src: arrow.source) {
                file << src << " -> " << "r" << counter << ";\n";
            }

            for (const auto &target: arrow.target) {
                file << "r" << counter << " -> " << target << ";\n";
            }
            counter++;
        }

        file << "}\n";
        file.close();

        std::string command =
                "dot -Tpng " + path + " -o /home/krogh/CLionProjects/cpp/Exam/" +
                name + ".png";
        system(command.c_str());
    }

} // stochastic