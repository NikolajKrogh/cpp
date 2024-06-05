//
// Created by krogh on 6/5/24.
//

#ifndef EXAM_SYMBOLTABLE_H
#define EXAM_SYMBOLTABLE_H

#include <map>
#include <vector>

namespace stochastic {

    template<typename K, typename V>
    class SymbolTable {
    private:
        std::map<K, V> table;
    public:
        SymbolTable() = default;

        ~SymbolTable() = default;




        void insert(K key, V value) {
            // If it is pointing to the end of the table, the key does not exist in the table
            if (table.find(key) != table.end()) {
                std::cout << "Symbol already exists in the table" << std::endl;
            } else {
                std::cout << "Symbol: " << key << " inserted into the table" << std::endl;
            }
            table[key] = value;
        }

/**
 * Gets the value associated with the given key.
 */

        V get(const K& key) const {
    auto it = table.find(key);
    if (it == table.end()) {
        std::cout << "Symbol not found in the table" << std::endl;
        throw std::out_of_range("Key not found in SymbolTable");
    }
    return it->second;
}

/**
 * Checks if the symbol table contains the given key.
 */

        bool contains(K key) {
            return table.find(key) != table.end();
        }



#pragma region Test Symbol Table


        void testSymbolTable() {
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
        std::vector<V> values() {
            std::vector<V> values;
            for (const auto &pair: table) {
                values.push_back(pair.second);
            }
            return values;
        }


    };

} // stochastic

#endif //EXAM_SYMBOLTABLE_H