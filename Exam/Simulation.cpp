#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>
#include "Simulation.h"

namespace stochastic {
    /**
 * @brief Computes the delay for a given reaction in a vessel.
 *
 * If any reactant quantity is zero, the function returns infinity, i.e. reaction cannot occur.
 * Otherwise, it calculates the product of the quantities of all reactants, multiplies it by the reaction rate,
 * and uses this to generate a random delay time from an exponential distribution.
 *
 * @param vessel The vessel in which the reaction is occurring.
 * @param reaction The reaction for which the delay is being computed.
 * @return The computed delay time for the reaction.
 */
double compute_delay(stochastic::Vessel &vessel, stochastic::Reaction &reaction) {
    double product = 1;
    // Iterate over all reactants in the reaction
    for (const auto &reactant: reaction.reactants) {
        // If any reactant quantity is zero, return infinity
        if (vessel.molecules.get(reactant.name)->quantity <= 0) {
            return std::numeric_limits<double>::infinity();
        }
        // Multiply the product by the quantity of the current reactant
        product *= vessel.molecules.get(reactant.name)->quantity;
    }
    // Calculate the rate of the reaction
    double rate = reaction.rate * product;
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // Initialize an exponential distribution with the calculated rate
    std::exponential_distribution<> d(rate);
    // Return a random delay time from the exponential distribution
    return d(gen);
}

/**
 * @brief Simulates the reactions in a vessel over a given period of time.
 *
 * The CSV file includes the time and the quantity of each molecule at each time step.
 * At each time step, it finds the reaction with the smallest delay and performs that reaction.
 * The function continues until the total time has reached the end time specified by the user.
 *
 * @param path The path to the CSV file where the results will be written.
 * @param vessel The vessel in which the reactions are occurring.
 * @param end_time The end time for the simulation.
 */
void Simulation::simulate(const std::string &path, Vessel &vessel, double end_time) {
    std::ofstream file(path);
    file << "Time"; // Write the header for the time column
    for (const auto &molecule: vessel.molecules.values()) {
        file << "," << molecule->name; // Write the headers for the molecule columns
    }
    file << std::endl;

    double time = 0;
    while (time <= end_time) {
        Reaction min_delay_reaction;
        double min_delay = std::numeric_limits<double>::infinity();

        // Find the reaction with the smallest delay
        for (auto &reaction: vessel.reactions) {
            reaction.delay = compute_delay(vessel, reaction);
            if (reaction.delay < min_delay) {
                // Update the minimum delay and the corresponding reaction
                min_delay = reaction.delay;
                min_delay_reaction = reaction;
            }
        }

        time += min_delay;
        if (canReact(vessel, min_delay_reaction)) {
            performReaction(vessel, min_delay_reaction);
        }

        file << time;
        for (const auto &molecule: vessel.molecules.values()) {
            file << "," << molecule->quantity; // Write the quantity of each molecule to the file
        }
        file << std::endl;
    }
    file.close(); // Close the file
}

/**
 * @brief Checks if a reaction can occur in a given vessel.
 *
 * @param vessel The vessel in which the reaction is supposed to occur.
 * @param reaction The reaction that is supposed to occur.
 * @return A boolean value indicating whether the reaction can occur (true) or not (false).
 */
bool Simulation::canReact(Vessel &vessel, Reaction &reaction) {
    for (const auto &reactant: reaction.reactants) {
        if (vessel.molecules.get(reactant.name)->quantity <= 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Performs a reaction in a given vessel.
 *
 * It iterates over the reactants of the reaction, decreasing their quantity in the vessel by one.
 * Then, it iterates over the products of the reaction, increasing their quantity in the vessel by one.
 *
 * @param vessel The vessel in which the reaction is occurring.
 * @param reaction The reaction that is being performed.
 */
    void Simulation::performReaction(Vessel &vessel, Reaction &reaction) {
        for (const auto &reactant: reaction.reactants) {
            vessel.molecules.get(reactant.name)->quantity -= 1;
        }
        for (const auto &product: reaction.products) {
            vessel.molecules.get(product.name)->quantity += 1;
        }
    }

/**
 * @brief Assigns a unique filename for a given name.
 *
 * It appends the name to a predefined path and checks if a file with that name already exists.
 * If a file with that name exists, it appends a counter to the name and increments the counter until it finds a filename that does not exist.
 * Once a unique filename is found, it creates an empty file with that name and returns the full path to the file.
 *
 * @param name The base name for the file.
 * @return The full path to the newly created file.
 */
std::string Simulation::assign_unique_filename(const std::string &name) {
    int counter = 1;
    std::string originalPath = "/home/krogh/CLionProjects/cpp/Exam/CsvFiles/" + name + ".csv";
    while (std::filesystem::exists(originalPath)) {
        originalPath =
                "/home/krogh/CLionProjects/cpp/Exam/CsvFiles/" + name + "_" + std::to_string(counter) + ".csv";
        counter++;
    }
    std::ofstream file;
    file.open(originalPath);
    file.close();
    return originalPath;
}

} // stochastic