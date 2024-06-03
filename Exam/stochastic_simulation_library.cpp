#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <random>
#include <cmath>
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
        // Iterate over each molecule
        for (const auto &molecule: molecules) {
            // Iterate over each reaction
            for (const auto &reaction: reactions) {
                // If the molecule is a reactant in the reaction
                for (const auto &reactant: reaction.reactants) {
                    if (reactant.get_name() == molecule.get_name()) {

                        std::vector<std::string> vector_products = {};
                        for (const auto &product: reaction.products) {
                            vector_products.push_back(product.get_name());
                        }
                        std::vector<std::string> matching_molecule_tags = {};
                        for (const auto &m: molecules) {
                            for (const auto p: vector_products) {
                                // If the name of the current molecule matches the current product name. Add the graphviz tag to the vector
                                if (m.get_name() == p) {
                                    matching_molecule_tags.push_back(m.graphviz_tag);
                                }
                            }
                        }
                        auto arrow = Arrow(molecule.graphviz_tag, matching_molecule_tags, reaction.get_rate());
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

/**
 * The Arrow object represents a reaction in the system, with a source molecule, target molecules, and a reaction rate.
 *
 * @param src The source molecule's Graphviz tag, represented as a string.
 * @param tgt A vector of target molecules' Graphviz tags, represented as strings.
 * @param r The rate of the reaction, represented as a double.
 */
    Arrow::Arrow(std::string src, std::vector<std::string> tgt, double r) {

        // Using std::move to avoid copying the string
        source = std::move(src);

        // Iterating over the target vector and adding each target to the Arrow's target vector
        for (auto &t: tgt) {
            target.push_back(t);
        }

        // Setting the rate of the Arrow (reaction)
        rate = r;
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
            std::cout << "Symbol" << key << " inserted into the table" << std::endl;
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

    template<typename K, typename V>
    void SymbolTable<K, V>::update(K key, V value) {
        if (!contains(key)) {
            std::cout << "Key not found" << std::endl;
        }
        table[key] = value;
    }

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

    stochastic_simulation_library::Simulation::Simulation(const std::vector<Reaction> &reactions,
                                                          const std::vector<Molecule> &state) {
        this->reactions = reactions;
        this->state = state;
    }

/**
 * Finds the reaction with the minimum delay in the simulation.
 * @return A pointer to the Reaction object with the minimum delay. If no reactions are present, returns nullptr.
 */
    Reaction *Simulation::find_min_delay_reaction() {
        // Check if there are no reactions
        if (reactions.empty()) {
            std::cout << "No valid reaction found" << std::endl;
        }

        // Use std::min_element to find the reaction with the minimum delay
        // This = sign is to capture the value of the pointer returned by min_element
        auto min_reaction_iter = std::min_element(reactions.begin(), reactions.end(),
                                                  [this](const Reaction &r1, const Reaction &r2) {
                                                      return compute_delay(r1) < compute_delay(r2);
                                                  }
        );

        // Return a pointer to the reaction with the minimum delay
        return &(*min_reaction_iter);
    }


/**
 * @brief Simulates the reactions until a specified end time.

 * @param end_time The end time of the simulation.
 * @param state The initial state of the molecules.
 */
    void Simulation::simulate(double end_time, const std::vector<Molecule> &initial_state) {
        double t = 0; // Initialize the current time to 0
        state = initial_state; // Initialize the state with the initial state

        // Continue the simulation until the current time exceeds the end time
        while (t <= end_time) {
            // Find the reaction with the minimum delay
            Reaction *min_reaction = find_min_delay_reaction();

            // Update the current time
            t += compute_delay(*min_reaction);
            bool all_reactants_present = true;
            //Check if all the reactants are present
            for (auto &molecule: state) {
                for (const auto &reactant: min_reaction->reactants) {
                    if (molecule.get_name() == reactant.get_name()) {
                        if (molecule.get_quantity() == 0) {
                            all_reactants_present = false;
                        }
                        if (!all_reactants_present) {

                            // Update the state with the new quantities of the molecules
                            for (auto &molecule: state) {
                                for (const auto &reactant: min_reaction->reactants) {
                                    if (molecule.get_name() == reactant.get_name()) {
                                        molecule.set_quantity(molecule.get_quantity() - 1);
                                    }
                                }
                                // Update the quantity of the molecule if it is a product of the reaction
                                for (const auto &product: min_reaction->products) {
                                    if (molecule.get_name() == product.get_name()) {
                                        molecule.set_quantity(molecule.get_quantity() + 1);
                                    }
                                }
                            }
                        }
                        //Print the current state of the simulation
                        for (const auto &molecule: state) {
                            std::cout << "Molecule: " << molecule.get_name() << ", Quantity: "
                                      << molecule.get_quantity()
                                      << std::endl;
                        }
                    }
                }
            }
        }
    }

    /**
 * Computes the delay for a given reaction.
 * The delay is calculated as a random number from an exponential distribution with lambda as the parameter.
 * Lambda is calculated as the product of the rate of the reaction and the product of the quantities of all reactants.
 *
 * @param reaction The reaction for which the delay is to be calculated.
 * @return The calculated delay.
 */
    double Simulation::compute_delay(const Reaction &reaction) {
        double delay = 1;
        for (auto reactant: reaction.reactants) {
            for (auto molecule: state) {
                if (molecule.get_name() == reactant.get_name()) {
                    delay *= molecule.get_quantity();
                }
            }
        }
        delay *= reaction.get_rate();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::exponential_distribution<> d(delay);
        return d(gen);
    }

#pragma endregion Simulation

}

