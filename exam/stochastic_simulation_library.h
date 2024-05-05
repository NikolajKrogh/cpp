#ifndef EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
#define EXAM_STOCHASTIC_SIMULATION_LIBRARY_H

#include <string>
#include <vector>


namespace stochastic_simulation_library {

    class Molecule {
    private:
        std::string name;
        double quantity;
    public:
        std::string get_name() const;

        void set_name(std::string name);

        double get_quantity() const;

        void set_quantity(double quantity);

        Molecule(std::string name, double quantity);

        ~Molecule() = default;
    };


    class Reaction {
    private:
        std::string name;
        double rate;
        std::vector <Molecule> reactants;
        std::vector <Molecule> products;
    public:
        std::string get_name() const;

        void set_name(std::string name);

        double get_rate() const;

        void set_rate(double rate);

        void add_reactant(std::initializer_list <Molecule> r);

        void add_product(std::initializer_list <Molecule> p);

        void add_reactant(const std::vector <Molecule> &r);

        void add_product(const std::vector <Molecule> &p);

        Reaction(std::string name, double rate, std::vector <Molecule> reactants, std::vector <Molecule> products);

        ~Reaction();
    };

    class Vessel {
    private:
        std::vector <Molecule> molecules;
        std::vector <Reaction> reactions;
    public:
        Vessel(std::vector <Molecule> molecules, std::vector <Reaction> reactions);

        ~Vessel();

        void add_molecule(Molecule molecule);

        void add_reaction(Reaction reaction);
    };
}
#endif //EXAM_STOCHASTIC_SIMULATION_LIBRARY_H