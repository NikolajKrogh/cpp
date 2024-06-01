#include <iostream>
#include "stochastic_simulation_library.h"

int main() {
#pragma region Constants

    const auto alphaA = 50;
    const auto alpha_A = 500;
    const auto alphaR = 0.01;
    const auto alpha_R = 50;
    const auto betaA = 50;
    const auto betaR = 5;
    const auto gammaA = 1;
    const auto gammaR = 1;
    const auto gammaC = 2;
    const auto deltaA = 1;
    const auto deltaR = 0.2;
    const auto deltaMA = 10;
    const auto deltaMR = 0.5;
    const auto thetaA = 50;
    const auto thetaR = 100;
#pragma endregion Constants

    auto v = stochastic_simulation_library::Vessel{"Circadian Rhythm"};
    const auto env = v.environment();
    const auto DA = v.add("DA", 1);
    const auto D_A = v.add("D_A", 0);
    const auto DR = v.add("DR", 1);
    const auto D_R = v.add("D_R", 0);
    const auto MA = v.add("MA", 0);
    const auto MR = v.add("MR", 0);
    const auto A = v.add("A", 1);
    const auto R = v.add("R", 0);
    const auto C = v.add("C", 0);
    v.add((A + DA) >> gammaA >>= D_A);
    v.add(D_A >> thetaA >>= DA + A);
    v.add((A + DR) >> gammaR >>= D_R);
    v.add(D_R >> thetaR >>= DR + A);
    v.add(D_A >> alpha_A >>= MA + D_A);
    v.add(DA >> alphaA >>= MA + DA);
    v.add(D_R >> alpha_R >>= MR + D_R);
    v.add(DR >> alphaR >>= MR + DR);
    v.add(MA >> betaA >>= MA + A);
    v.add(MR >> betaR >>= MR + R);
    v.add((A + R) >> gammaC >>= C);
    v.add(C >> deltaA >>= R);
    v.add(A >> deltaA >>= env);
    v.add(R >> deltaR >>= env);
    v.add(MA >> deltaMA >>= env);
    v.add(MR >> deltaMR >>= env);

    v.network_graph();
    v.pretty_print();

    stochastic_simulation_library::SymbolTable<std::string, double> symbolTable;

    symbolTable.testSymbolTable();



    // Create Molecule objects for A, B, and C with the given initial quantities
    stochastic_simulation_library::Molecule X("A", 100);
    stochastic_simulation_library::Molecule Y("B", 0);
    stochastic_simulation_library::Molecule Z("C", 1);

    // Create a Reaction object that represents the reaction A + C -> B
    stochastic_simulation_library::Reaction reaction;
    reaction.add_reactant({X, Z});
    reaction.add_product({Y});
    reaction.set_rate(0.001); // Set the rate (lambda) of the reaction
    reaction.set_name("A + C -> B");

    // Create a Simulation object with the reaction, end time, and initial state
    std::vector<stochastic_simulation_library::Reaction> reactions = {reaction};
    std::vector<stochastic_simulation_library::Molecule> state = {X,Y,Z};
    stochastic_simulation_library::Simulation simulation(reactions, 2000, state);
//std::cout << "Number of reactions: " << reactions.size() << std::endl;
//    for (const auto& reaction : reactions) {
//        std::cout << "Reaction: " << reaction.get_name() << ", Rate: " << reaction.get_rate() << std::endl;
//        std::cout << "Reactants: ";
//        for (const auto& reactant : reaction.reactants) {
//            std::cout << reactant.get_name() << " ";
//        }
//        std::cout << "\nProducts: ";
//        for (const auto& product : reaction.products) {
//            std::cout << product.get_name() << " ";
//        }
//        std::cout << "\n";
//    }
    // Run the simulation
    simulation.simulate(2000, state);


    return 0;
}
