//
// Created by krogh on 6/5/24.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>
#include "Simulation.h"

namespace stochastic {
    double
    compute_delay(stochastic::Vessel &vessel, stochastic::Reaction &reaction) {
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
            stochastic::Reaction min_delay_reaction = Reaction();
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

} // stochastic