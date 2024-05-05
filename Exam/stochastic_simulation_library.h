#ifndef EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
#define EXAM_STOCHASTIC_SIMULATION_LIBRARY_H

#include <string>
#include <vector>

namespace stochastic_simulation_library {
typedef enum {
    left,
    right
}reaction_side;

    class Molecule {
    private:
        std::string name;
        double quantity;
    public:
        Molecule(const std::string &name, double quantity);

        ~Molecule() = default;

        std::string get_name() const;
        void set_name(const std::string &name);

        double get_quantity() const;
        void set_quantity(double quantity);

        void operator -=(double quantity);
        void operator +=(double quantity);
    };


    class Environment {
    private:

    public:
        Environment();
        ~Environment() = default;
    };

    class Reaction {
    private:
        std::string name;
        double rate;
        std::vector <Molecule> reactants;
        std::vector <Molecule> products;
        reaction_side side = left;
    public:

        Reaction(const std::string &name, double rate, const std::vector <Molecule> &reactants, const std::vector <Molecule> &products);
        Reaction();
        ~Reaction() = default;

        std::string get_name() const;

        void set_name(const std::string &name);

        double get_rate() const;

        void set_rate(double rate);

        void add_reactant(std::initializer_list <Molecule> r);

        void add_product(std::initializer_list <Molecule> p);

        void add_reactant(const std::vector <Molecule> &r);

        void add_product(const std::vector <Molecule> &p);

        Reaction operator >> (double reaction_rate);

        Reaction operator >>= (const Molecule &products);

        Reaction operator + (const Molecule &molecule);

        Reaction operator >>= (const Environment &env);
    };


    class Vessel {
    private:
        std::vector <Molecule> molecules;
        std::vector <Reaction> reactions;
    public:
        Vessel(const std::vector <Molecule> &molecules, const std::vector <Reaction> &reactions);

        ~Vessel() = default;

        void add_molecule(const Molecule &molecule);

        void add_reaction(const Reaction &reaction);

    };
}
#endif //EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
