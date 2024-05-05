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
            Molecule(std::string name, double quantity);
            ~Molecule();
    };

    class Catalyst {
    private:
        std::string name;
        double quantity;
    public:
        Catalyst(std::string name, double quantity);
        ~Catalyst();
    };

    class Reaction {
    private:
        std::string name;
        double rate;
        std::vector<Molecule> reactants;
        std::vector<Molecule> products;
    public:
        Reaction(std::string name, double rate, std::vector<Molecule> reactants, std::vector<Molecule> products);
        ~Reaction();
    };
}
#endif //EXAM_STOCHASTIC_SIMULATION_LIBRARY_H
