#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <random>
#include <cmath>
#include <set>
#include <filesystem>
#include "stochastic_simulation_library.h"

namespace stochastic_simulation_library {
#pragma region Molecule

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

#pragma endregion Vessel

#pragma region Environment

    Environment::Environment() {

    }

#pragma endregion Environment

#pragma region Arrow

/**
 * The Arrow object represents a reaction in the system, with a source molecule, target molecules, and a reaction rate.
 *
 * @param src The source molecule's Graphviz tag, represented as a string.
 * @param tgt A vector of target molecules' Graphviz tags, represented as strings.
 * @param r The rate of the reaction, represented as a double.
 */
    Arrow::Arrow(std::vector<std::string> src, std::vector<std::string> tgt, double r) {

        // Using std::move to avoid copying the string
        for (auto &s: src) {
            this->source.push_back(s);
        }

        // Iterating over the target vector and adding each target to the Arrow's target vector
        for (auto &t: tgt) {
            this->target.push_back(t);
        }

        // Setting the rate of the Arrow (reaction)
        this->rate = r;
    }

#pragma endregion Arrow

#pragma region Symbol Table

    template<typename K, typename V>
    SymbolTable<K, V>::SymbolTable() = default;

    template<typename K, typename V>
    SymbolTable<K, V>::~SymbolTable() = default;

/**
 * Inserts a new key-value pair into the symbol table.
 * If the key already exists in the table, it throws a runtime error.
 *
 * @tparam K The type of the key.
 * @tparam V The type of the value.
 * @param key The key of the new element.
 * @param value The value of the new element.
 * @throws std::runtime_error if the key already exists in the table.
 */
    template<typename K, typename V>
    void SymbolTable<K, V>::insert(K key, V value) {
        // If it is pointing to the end of the table, the key does not exist in the table
        if (table.find(key) != table.end()) {
            std::cout << "Symbol already exists in the table" << std::endl;
        } else {
            std::cout << "Symbol: " << key << " inserted into the table" << std::endl;
        }
        table[key] = value;
    }

/**
 * Gets the value associated with the given key.
 */
    template<typename K, typename V>
    V SymbolTable<K, V>::get(K key) {
        if (table.find(key) == table.end()) {
            std::cout << "Symbol not found in the table" << std::endl;
        }
        return table[key];
    }

/**
 * Checks if the symbol table contains the given key.
 */
    template<typename K, typename V>
    bool SymbolTable<K, V>::contains(K key) {
        return table.find(key) != table.end();
    }


    // Explicit instantiation of the SymbolTable class to avoid linker errors
    template
    class stochastic_simulation_library::SymbolTable<std::string, double>;

#pragma region Test Symbol Table

    template<typename K, typename V>
    void SymbolTable<K, V>::testSymbolTable() {
        // Create a SymbolTable instance
        stochastic_simulation_library::SymbolTable<std::string, double> symbolTable;

        // Insert some key-value pairs
        symbolTable.insert("DA", 1);
        symbolTable.insert("D_A", 0);
        symbolTable.insert("DR", 1);
        symbolTable.insert("D_R", 0);
        symbolTable.insert("MA", 0);
        symbolTable.insert("MR", 0);
        symbolTable.insert("A", 1);
        symbolTable.insert("R", 0);
        symbolTable.insert("C", 0);

        // Check if a key exists
        if (symbolTable.contains("DA")) {
            std::cout << "DA exists in the symbol table." << std::endl;
        } else {
            std::cout << "DA does not exist in the symbol table." << std::endl;
        }

        // Get the value associated with a key
        double value = symbolTable.get("DR");
        std::cout << "The value of DR is: " << value << std::endl;

        // Try to insert a key that already exists
        symbolTable.insert("DA", 1);

    }

#pragma endregion Test Symbol Table

#pragma endregion Symbol Table

#pragma region Simulation

    double
    compute_delay(stochastic_simulation_library::Vessel &vessel, stochastic_simulation_library::Reaction &reaction) {
        double product = 1;
        for (const auto &reactant: reaction.reactants) {
            if (vessel.molecules.get(reactant.name)->quantity <= 0) {
                return std::numeric_limits<double>::infinity();
            }
            product *= vessel.molecules.get(reactant.name)->quantity;
        }
        double rate = reaction.rate * product;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::exponential_distribution<> d(rate);
        return d(gen);
    }

    void Simulation::simulate(const std::string &p,Vessel &vessel, double end_time) {
        double time = 0;
        // Open the file in write mode
        std::ofstream file(p);
        file << "Time";
        for (const auto molecule : vessel.molecules.values()) {
            file << "," << molecule->name;
        }
        file << std::endl;

        while (time <= end_time) {
            for (auto &reaction: vessel.reactions) {
                reaction.delay = compute_delay(vessel, reaction);
            }
            double min_delay = std::numeric_limits<double>::infinity();
            stochastic_simulation_library::Reaction min_delay_reaction = Reaction();
            for (auto &reaction: vessel.reactions) {
                if (reaction.delay < min_delay) {
                    min_delay = reaction.delay;
                    min_delay_reaction = reaction;
                }
            }
            time += min_delay;
            bool is_present = true;
            for (const auto &reactant: min_delay_reaction.reactants) {
                if (vessel.molecules.get(reactant.name)->quantity <= 0) {
                    is_present = false;
                    break;
                }
            }
            if (!is_present) {
                continue;
            }
            for (const auto &reactant: min_delay_reaction.reactants) {
                vessel.molecules.get(reactant.name)->quantity -= 1;
            }
            for (const auto &product: min_delay_reaction.products) {
                vessel.molecules.get(product.name)->quantity += 1;
            }
            file << time;
            for (const auto molecule: vessel.molecules.values()) {
                file << "," << molecule->quantity;
            }
            file << std::endl;
        }
        file.close();
    }

    std::string Simulation::assign_unique_filename(const std::string &name) {
        int counter = 1;
        std::string originalPath = "/home/krogh/CLionProjects/cpp/Exam/CsvFiles/" + name + ".csv";
        while (std::filesystem::exists(originalPath)) {
            originalPath = "/home/krogh/CLionProjects/cpp/Exam/CsvFiles/" + name + "_" + std::to_string(counter) + ".csv";
            counter++;
        }
        std::ofstream file;
        file.open(originalPath);
        file.close();
        return originalPath;
    }

#pragma endregion Simulation


}

