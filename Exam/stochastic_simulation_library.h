#ifndef EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
#define EXAM_STOCHASTIC_SIMULATION_LIBRARY_H

#include <string>
#include <vector>
#include <map>
#include <thread>


namespace stochastic_simulation_library {

#pragma region Prototypes

    // Required to avoid circular dependencies
    class Reaction;

#pragma endregion Prototypes

    // Use enum to check if we should add the reactants to the left or right side of the reaction
    typedef enum {
        left,
        right
    } reaction_side;

#pragma region Molecule

    class Molecule {
    public:
        std::string name;
        double quantity;
        std::string graphviz_tag;

        Molecule(const std::string &name, double quantity);

        ~Molecule() = default;

        void operator-=(double quantity);

        void operator+=(double quantity);

        Reaction operator+(const Molecule &molecule) const;

        Reaction operator+(const Reaction &reaction);

        Reaction operator>>(double reaction_rate) const;
    };

#pragma endregion Molecule

#pragma region Environment

    class Environment {
    private:

    public:
        Environment();

        ~Environment() = default;
    };

#pragma endregion Environment

#pragma region Reaction

    class Reaction {
    public:
        std::string name;
        double rate;
        reaction_side side = left;
        std::vector<Molecule> products;
        std::vector<Molecule> reactants;
        double delay;

        Reaction(const std::string &name, double rate, const std::vector<Molecule> &reactants,
                 const std::vector<Molecule> &products);

        Reaction();

        ~Reaction() = default;

        Reaction operator>>(double reaction_rate);

        Reaction operator+(const Molecule &molecule);

        Reaction operator>>=(const Molecule &products);

        Reaction operator>>=(const Environment &env);

        Reaction operator>>=(const Reaction &reaction);

    };

#pragma endregion Reaction

#pragma region Arrow

    class Arrow {
    public:
        std::vector<std::string> source;
        std::vector<std::string> target;
        double rate;

        Arrow(std::vector<std::string> src, std::vector<std::string> tgt, double r);

        Arrow() = default;

        ~Arrow() = default;
    };

#pragma endregion Arrow

#pragma region SymbolTable

    template<typename K, typename V>
    class SymbolTable {
    private:
        std::map<K, V> table;
    public:
        SymbolTable();

        ~SymbolTable();

        void insert(K key, V value);

        V get(K key);

        bool contains(K key);

        std::vector<V> values() {
            std::vector<V> values;
            for (const auto &pair: table) {
                values.push_back(pair.second);
            }
            return values;
        }

        void testSymbolTable();
    };


#pragma endregion SymbolTable

#pragma region Vessel

    class Vessel {
    public:
        stochastic_simulation_library::SymbolTable<std::string, Molecule *> molecules;
        std::vector<Reaction> reactions;
        std::string name;

        Vessel(const std::string &name);

        ~Vessel() = default;


        Molecule &add(const std::string &name, double quantity);

        void add(const Reaction &reaction);

        Environment environment();

        void pretty_print();

        void get_digraph();

        std::string get_symbol_table_representation() {
            std::string s = "";
            for (const auto &m: molecules.values()) {
                s += ", " + m->name + ": " + std::to_string(m->quantity);

            }
            return s;
        }
    };

#pragma endregion Vessel


#pragma region Simulation

    class Simulation {
    public:
        static void simulate(const std::string &p,Vessel &vessel, double end_time);
        static std::string assign_unique_filename(const std::string &name);

    };



#pragma endregion Simulation

#pragma region Parallelize

    class ParallelSimulation {
    public:
        static void parallalize_simulations(std::vector<Vessel> vessels, double T) {
            std::vector<std::thread> threads;

            for (auto &v: vessels) {
                std::string path = stochastic_simulation_library::Simulation::assign_unique_filename(v.name);
                threads.push_back(std::thread(stochastic_simulation_library::Simulation::simulate, path, std::ref(v), T));
            }

            for (auto &thread: threads) {
                thread.join();
            }
        }

    };

}


#endif //EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
