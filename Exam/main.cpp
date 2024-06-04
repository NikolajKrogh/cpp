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

    auto sim = stochastic_simulation_library::Vessel{"Sim"};
    const auto X = sim.add("A", 100);
    const auto Y =sim.add("B", 0);
    const auto Z = sim.add("C", 1);

    // Create a Reaction object that represents the reaction A + C -> B
    stochastic_simulation_library::Reaction reaction;
    reaction.add_reactant({X, Z});
    reaction.add_product({Y,Z});
    reaction.set_rate(0.001); // Set the rate (lambda) of the reaction


    //std::cout << "Reaction running:" << reaction.get_name() << std::endl;

    // Create a Simulation object with the reaction, end time, and initial state
    std::vector<stochastic_simulation_library::Reaction> reactions = {reaction};
    std::vector<stochastic_simulation_library::Molecule> example1 = {X,Y,Z};
    stochastic_simulation_library::Simulation simulation(reactions, example1);

    std::vector<stochastic_simulation_library::Molecule> example2 = {DA, D_A, DR, D_R, MA, MR, A, R, C};
    // Run the simulation
    //simulation.simulate(2000, example1);
    simulation.simulate(50, example2);






    return 0;
}
