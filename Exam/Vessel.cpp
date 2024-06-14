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

    /**
     * ------------------  Exercise 3 ------------------
     * @brief Adds a molecule to the vessel.
     *
     * This function creates a new molecule with the given name and quantity, adds it to the vessel's collection of molecules, and returns a reference to the molecule.
     *
     * @param name The name of the molecule to be added.
     * @param quantity The quantity of the molecule to be added.
     * @return A reference to the newly created molecule.
     */

    Molecule &Vessel::add(const std::string &name, double quantity) {
        auto m = new Molecule(name, quantity);
        molecules.insert(name, m);
        return *m;
    }

    /**
     * ------------------  Exercise 3 ------------------
     * @brief Adds a reaction to the vessel.
     * @param reaction The reaction to be added.
     */
    void Vessel::add(const Reaction &reaction) {
        reactions.push_back(reaction);
    }

    /**
     * ------------------  Exercise 2 ------------------
     * @brief Prints a formatted representation of the reactions in the vessel.
     *
     * For each reaction, it prints the names of the reactants, the reaction rate, and the names of the products.
     * If a reactant or product is not the last one in its list, a plus sign is printed after its name.
     * If there are no products for a reaction, it prints 'none'.
     */
    void Vessel::pretty_print() {

        // Iterate over each reaction
        for (const auto &reaction: reactions) {
            // Iterate over each reactant in the reaction
            for (auto &reactant: reaction.reactants) {

                std::cout << reactant.name;

                if (&reactant != &reaction.reactants.back()) {
                    std::cout << " + ";
                }
            }

            // Print the reaction rate
            std::cout << " -> " << reaction.rate << " -> ";

            // Check if there are any products in the reaction
            if (reaction.products.empty()) {
                std::cout << "none";
            } else {
                // If there are products, print each one
                for (size_t i = 0; i < reaction.products.size(); ++i) {
                    std::cout << reaction.products[i].name;
                    if (i != reaction.products.size() - 1) {
                        std::cout << " + ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }


    /**
     * ------------------  Exercise 2 ------------------
     * @brief Assigns unique tags to each molecule involved in the reactions.
     *
     * For each reactant and product in the reaction, it checks if the molecule's name is already in the symbol table.
     * If it's not, it inserts the molecule's name into the symbol table with a unique tag ("s" followed by a counter).
     * The counter is incremented after each insertion.
     *
     * @param table A reference to the symbol table where the molecule names and their corresponding tags are stored.
     * @param counter A reference to the counter used to generate unique tags for the molecules.
     */
    void Vessel::assign_tags(SymbolTable<std::string, std::string> &table, int &counter) {
        for (auto &r: reactions) {
            for (auto &m: r.reactants) {
                if (!table.contains(m.name)) {
                    table.insert(m.name, ("s" + std::to_string(counter++)));
                }
            }
            for (auto &m: r.products) {
                if (!table.contains(m.name)) {
                    table.insert(m.name, ("s" + std::to_string(counter++)));
                }
            }
        }
    }

    /**
     * ------------------  Exercise 2 ------------------
     * @brief Creates a vector of Arrows representing the reactions in the vessel.
     *
     * For each reaction, it creates an Arrow object.
     * For each reactant and product in the reaction, it adds their corresponding tags from the symbol table to the source and target of the Arrow, respectively.
     * It also sets the rate of the Arrow to the rate of the reaction.
     * The created Arrow is then added to a vector of Arrows, which is returned at the end.
     *
     * @param table A reference to the symbol table where the molecule names and their corresponding tags are stored.
     * @return A vector of Arrows representing the reactions in the vessel.
     */
    std::vector<Arrow> Vessel::create_arrows(const SymbolTable<std::string, std::string> &table) {
        std::vector<Arrow> arrows;
        for (const auto &r: reactions) {
            Arrow arrow = {};
            for (const auto &reactant: r.reactants) {
                arrow.source.push_back(table.get(reactant.name));
            }
            for (const auto &product: r.products) {
                arrow.target.push_back(table.get(product.name));
            }
            arrow.rate = r.rate;
            arrows.push_back(arrow);
        }
        return arrows;
    }

    /**
     * ------------------  Exercise 2 ------------------
     * @brief Writes the reactions represented by Arrows to a .dot file.
     *
     * The function opens a file with the name of the vessel and writes the .dot representation of the reactions to it.
     * For each molecule in the vessel, it writes a line in the .dot file with the molecule's tag, name, and color.
     * For each Arrow in the vector, it writes a line in the .dot file with the Arrow's tag, rate, source, and target.
     * The function then closes the file and generates a .png file from the .dot file using the 'dot' command.
     *
     * @param arrows A vector of Arrows representing the reactions in the vessel.
     * @param table A reference to the symbol table where the molecule names and their corresponding tags are stored.
     */
    void Vessel::write_to_file(const std::vector<Arrow> &arrows, const SymbolTable<std::string, std::string> &table) {
        std::ofstream file;
        std::string path = "/home/krogh/CLionProjects/cpp/Exam/" + name + ".dot";
        file.open(path);
        if (!file) {
            std::cerr << "Unable to open file for writing.\n";
            return;
        }

        file << "digraph {\n";
        int counter = 0;
        // Create a set to store unique tags
        std::set<std::string> u_sets;
        for (const auto &r: reactions) {
            for (const auto &reactant: r.reactants) {
                auto pair = u_sets.insert(table.get(reactant.name));
                if (pair.second) {
                    file << table.get(reactant.name) << "[label=\"" << reactant.name
                         << R"(",shape="box",style="filled",fillcolor="cyan"];)" << '\n';
                }
            }

            for (const auto &product: r.products) {
                auto pair = u_sets.insert(table.get(product.name));
                if (pair.second) {
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
                "dot -Tpng " + path + " -o /home/krogh/CLionProjects/cpp/Exam/images/" +
                name + "_tree" + ".png";
        system(command.c_str());
    }

    /**
     * ------------------  Exercise 2 ------------------
     * @brief Generates a directed graph representation of the reactions in the vessel.
     *
     * This function first creates a symbol table and a counter for assigning unique tags to the molecules.
     * It then calls the assign_tags function to assign unique tags to each molecule involved in the reactions.
     * After that, it calls the create_arrows function to create a vector of Arrows representing the reactions in the vessel.
     * Finally, it calls the write_to_file function to write the reactions represented by the Arrows to a .dot file.
     */
    void Vessel::get_digraph() {

        SymbolTable<std::string, std::string> table;
        int counter = 0;
        assign_tags(table, counter);
        std::vector<Arrow> arrows = create_arrows(table);
        write_to_file(arrows, table);
    }


} // stochastic