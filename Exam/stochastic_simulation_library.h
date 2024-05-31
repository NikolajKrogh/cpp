#ifndef EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
#define EXAM_STOCHASTIC_SIMULATION_LIBRARY_H

#include <string>
#include <vector>
#include <map>

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
    private:
        std::string name;
        double quantity;
    public:
        std::string graphviz_tag;

        Molecule(const std::string &name, double quantity);

        ~Molecule() = default;

        std::string get_name() const;

        void set_name(const std::string &name);

        double get_quantity() const;

        void set_quantity(double quantity);

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
    private:
        std::string name;
        double rate;
        reaction_side side = left;
    public:
        std::vector<Molecule> products;

        Reaction(const std::string &name, double rate, const std::vector<Molecule> &reactants,
                 const std::vector<Molecule> &products);

        Reaction();

        ~Reaction() = default;

        std::vector<Molecule> reactants;

        std::string get_name() const;

        void set_name(const std::string &name);

        double get_rate() const;

        void set_rate(double rate);

        void add_reactant(std::initializer_list<Molecule> r);

        void add_product(std::initializer_list<Molecule> p);

        void add_reactant(const std::vector<Molecule> &r);

        void add_product(const std::vector<Molecule> &p);

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
        std::string source;
        std::vector<std::string> target;
        double rate;

        Arrow(std::string src, std::vector<std::string> tgt, double r);

        ~Arrow() = default;
    };

#pragma endregion Arrow

#pragma region Vessel

    class Vessel {
    private:
        std::vector<Molecule> molecules;
        std::vector<Reaction> reactions;
        std::string name;
    public:
        Vessel(const std::vector<Molecule> &molecules, const std::vector<Reaction> &reactions);

        Vessel(const std::string &name);

        ~Vessel() = default;

        void add_molecule(const Molecule &molecule);

        void add_reaction(const Reaction &reaction);

        Molecule add(std::string name, double quantity);

        void add(const Reaction &reaction);

        Environment environment();

        void pretty_print();

        std::vector<Arrow> create_arrows();

        void assign_tags_to_molecules();

        void write_to_file(const std::vector<Arrow> &arrows);

        void network_graph();
    };

#pragma endregion Vessel

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

        void testSymbolTable();
    };


#pragma endregion SymbolTable

}


#endif //EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
