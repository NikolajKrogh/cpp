#include <gtest/gtest.h>
#include "../SymbolTable.h"

TEST(SymbolTableTest, InsertAndRetrieveValue) {
    stochastic::SymbolTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_EQ(table.get(1), "one");
}

TEST(SymbolTableTest, InsertDuplicateKey) {
    stochastic::SymbolTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(1, "duplicate");
    EXPECT_EQ(table.get(1), "one");
}

TEST(SymbolTableTest, RetrieveNonExistentKey) {
    stochastic::SymbolTable<int, std::string> table;
    std::string default_value;
    EXPECT_EQ(table.get(1), default_value);

}

TEST(SymbolTableTest, CheckKeyExists) {
    stochastic::SymbolTable<int, std::string> table;
    table.insert(1, "one");
    EXPECT_TRUE(table.contains(1));
    EXPECT_FALSE(table.contains(2));
}

TEST(SymbolTableTest, RetrieveAllValues) {
    stochastic::SymbolTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    std::vector<std::string> values = table.values();
    EXPECT_EQ(values.size(), 2);
    EXPECT_EQ(values[0], "one");
    EXPECT_EQ(values[1], "two");
}

TEST(SymbolTableTest, UpdateValue) {
    stochastic::SymbolTable<int, std::string> table;
    table.insert(1, "one");
    table.update(1, "updated");
    EXPECT_EQ(table.get(1), "updated");
}

TEST(SymbolTableTest, UpdateNonExistentKey) {
    stochastic::SymbolTable<int, std::string> table;
    table.update(1, "updated");
    std::string defaultValue;
    EXPECT_EQ(table.get(1), defaultValue);
}