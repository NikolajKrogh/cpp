#include <iostream>
#include <thread>
#include <cmath>
#include "Vessel.h"
#include "Simulation.h"
#include "ParallelSimulation.h"

stochastic::Vessel simulation_circadian_rhythm() {
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


    auto v = stochastic::Vessel{"Circadian Rhythm"};
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


    return v;
};

stochastic::Vessel simulation_covid19(uint32_t N) {
    auto v = stochastic::Vessel{"COVID19 SEIHR: " + std::to_string(N)};
    const auto eps = 0.0009; // initial fraction of infectious
    const auto I0 = size_t(std::round(eps * N)); // initial infectious
    const auto E0 = size_t(std::round(eps * N * 15)); // initial exposed
    const auto S0 = N - I0 - E0; // initial susceptible
    const auto R0 = 2.4; // initial basic reproductive number
    const auto alpha = 1.0 / 5.1; // incubation rate (E -> I) ~5.1 days
    const auto gamma = 1.0 / 3.1; // recovery rate (I -> R) ~3.1 days
    const auto beta = R0 * gamma; // infection/generation rate (S+I -> E+I)
    const auto P_H = 0.9e-3; // probability of hospitalization
    const auto kappa = gamma * P_H * (1.0 - P_H); // hospitalization rate (I -> H)
    const auto tau = 1.0 / 10.12; // removal rate in hospital (H -> R) ~10.12 days
    const auto S = v.add("S", S0); // susceptible
    const auto E = v.add("E", E0); // exposed
    const auto I = v.add("I", I0); // infectious
    const auto H = v.add("H", 0); // hospitalized
    const auto R = v.add("R", 0); // removed/immune (recovered + dead)
    v.add((S + I) >> beta / N >>= E + I); // susceptible becomes exposed by infectious
    v.add(E >> alpha >>= I); // exposed becomes infectious
    v.add(I >> gamma >>= R); // infectious becomes removed
    v.add(I >> kappa >>= H); // infectious becomes hospitalized
    v.add(H >> tau >>= R); // hospitalized becomes removed

    return v;

}

stochastic::Vessel simulation_example1() {
    auto v = stochastic::Vessel{"Example 1"};
    const auto env = v.environment();
    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 0);
    v.add(A >> 0.001 >>= B);
    v.add(B >> 0.001 >>= C);
    v.add(C >> 0.001 >>= env);

    return v;
}

stochastic::Vessel simulation_example2() {
    auto v = stochastic::Vessel{"Example 2"};
    const auto env = v.environment();
    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 2);
    v.add(A >> 0.001 >>= B);
    v.add(B >> 0.001 >>= C);
    v.add(C >> 0.001 >>= env);


    return v;
}

stochastic::Vessel simulation_example3() {
    auto v = stochastic::Vessel{"Example 3"};
    const auto env = v.environment();
    const auto A = v.add("A", 50);
    const auto B = v.add("B", 50);
    const auto C = v.add("C", 1);
    v.add(A >> 0.001 >>= B);
    v.add(B >> 0.001 >>= C);
    v.add(C >> 0.001 >>= env);


    return v;
}

void parallelize_simulations() {
    std::vector<std::thread> threads;
    threads.push_back(std::thread(simulation_circadian_rhythm));
    threads.push_back(std::thread(simulation_covid19, 10000));
    threads.push_back(std::thread(simulation_example1));
    threads.push_back(std::thread(simulation_example2));
    threads.push_back(std::thread(simulation_example3));
    for (auto &t: threads) {
        t.join();
    }
}

void pretty_print_circadian_rhythm() {
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


    auto v = stochastic::Vessel{"Circadian_Rhythm"};
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

    v.pretty_print();
    v.get_digraph();
}

void symbol_table_test() {
    // Create a SymbolTable instance
    stochastic::SymbolTable<std::string, double> symbolTable;

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

int main() {

    symbol_table_test();

//    pretty_print_circadian_rhythm();

//    simulation_circadian_rhythm();
//    simulation_covid19(10000);
//    simulation_example1();
//    simulation_example2();
//    simulation_example3();
//    auto vessel1 = simulation_covid19(10000);
//    auto vessel2 = simulation_circadian_rhythm();
//    auto vessel3 = simulation_example1();
//    auto vessel4 = simulation_example2();
//    auto vessel5 = simulation_example3();
//    std::string path = stochastic::Simulation::assign_unique_filename(vessel1.name);
//
//    //stochastic::Simulation::simulate(path, vessel, 1000);
//    stochastic::ParallelSimulation::parallelize_simulations(
//            {vessel1, vessel2, vessel3, vessel4, vessel5}, 100);

    return 0;
}
