#include <gtest/gtest.h>
#include <filesystem>
#include "../Vessel.h"

using namespace stochastic;

TEST(VesselTest, AddMolecule) {
    Vessel vessel("TestVessel");
    Molecule &molecule = vessel.add("H2O", 10.0);
    ASSERT_EQ(molecule.name, "H2O");
    ASSERT_EQ(molecule.quantity, 10.0);
}

TEST(VesselTest, AddReaction) {
    Vessel vessel("TestVessel");
    Reaction reaction;
    reaction.reactants.push_back(Molecule("H2O", 10.0));
    reaction.products.push_back(Molecule("H2", 5.0));
    reaction.products.push_back(Molecule("O2", 5.0));
    vessel.add(reaction);
    ASSERT_EQ(vessel.reactions.size(), 1);
}

TEST(VesselTest, PrettyPrintEmptyVessel) {
    stochastic::Vessel vessel("TestVessel");
    testing::internal::CaptureStdout();
    vessel.pretty_print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(VesselTest, PrettyPrintVesselWithSingleReactionNoProducts) {
    stochastic::Vessel vessel("TestVessel");
    stochastic::Reaction reaction;
    reaction.reactants.push_back(stochastic::Molecule("H2O", 2));
    reaction.rate = 1.0;
    vessel.add(reaction);
    testing::internal::CaptureStdout();
    vessel.pretty_print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "H2O -> 1 -> ∅\n");
}

TEST(VesselTest, PrettyPrintVesselWithSingleReactionWithProducts) {
    stochastic::Vessel vessel("TestVessel");
    stochastic::Reaction reaction;
    reaction.reactants.push_back(stochastic::Molecule("H2O", 2));
    reaction.products.push_back(stochastic::Molecule("H2", 1));
    reaction.products.push_back(stochastic::Molecule("O2", 1));
    reaction.rate = 1.0;
    vessel.add(reaction);
    testing::internal::CaptureStdout();
    vessel.pretty_print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "H2O -> 1 -> H2 + O2\n");
}

TEST(VesselTest, PrettyPrintVesselWithMultipleReactions) {
    stochastic::Vessel vessel("TestVessel");
    stochastic::Reaction reaction1;
    reaction1.reactants.push_back(stochastic::Molecule("H2O", 2));
    reaction1.products.push_back(stochastic::Molecule("H2", 1));
    reaction1.products.push_back(stochastic::Molecule("O2", 1));
    reaction1.rate = 1.0;
    vessel.add(reaction1);
    stochastic::Reaction reaction2;
    reaction2.reactants.push_back(stochastic::Molecule("H2", 1));
    reaction2.reactants.push_back(stochastic::Molecule("O2", 1));
    reaction2.products.push_back(stochastic::Molecule("H2O", 2));
    reaction2.rate = 2.0;
    vessel.add(reaction2);
    testing::internal::CaptureStdout();
    vessel.pretty_print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "H2O -> 1 -> H2 + O2\nH2 + O2 -> 2 -> H2O\n");
}

TEST(VesselTest, AssignTagsAssignsUniqueTags) {
    Vessel vessel("TestVessel");
    Reaction reaction;
    reaction.reactants.push_back(Molecule("H2O", 10.0));
    reaction.products.push_back(Molecule("H2", 5.0));
    reaction.products.push_back(Molecule("O2", 5.0));
    vessel.add(reaction);
    SymbolTable<std::string, std::string> table;
    int counter = 0;
    vessel.assign_tags(table, counter);
    ASSERT_EQ(table.get("H2O"), "s0");
    ASSERT_EQ(table.get("H2"), "s1");
    ASSERT_EQ(table.get("O2"), "s2");
}

TEST(VesselTest, CreateArrowsCreatesCorrectNumberOfArrows) {
    Vessel vessel("TestVessel");
    Reaction reaction;
    reaction.reactants.push_back(Molecule("H2O", 10.0));
    reaction.products.push_back(Molecule("H2", 5.0));
    reaction.products.push_back(Molecule("O2", 5.0));
    vessel.add(reaction);
    SymbolTable<std::string, std::string> table;
    int counter = 0;
    vessel.assign_tags(table, counter);
    std::vector<Arrow> arrows = vessel.create_arrows(table);
    ASSERT_EQ(arrows.size(), 1);
}

TEST(VesselTest, WriteToFileCreatesFile) {
    Vessel vessel("TestVessel");
    Reaction reaction;
    reaction.reactants.push_back(Molecule("H2O", 10.0));
    reaction.products.push_back(Molecule("H2", 5.0));
    reaction.products.push_back(Molecule("O2", 5.0));
    vessel.add(reaction);
    SymbolTable<std::string, std::string> table;
    int counter = 0;
    vessel.assign_tags(table, counter);
    std::vector<Arrow> arrows = vessel.create_arrows(table);
    vessel.write_to_file(arrows, table);
    ASSERT_TRUE(std::filesystem::exists("/home/krogh/CLionProjects/cpp/Exam/TestVessel.dot"));
}