#pragma once

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


       /**
        * ------------------  Exercise 3 ------------------
        * @brief Inserts a key-value pair into the symbol table.
        *
        * This function attempts to insert a given key-value pair into the symbol table.
        * If the key already exists in the table, it prints a message indicating that the symbol already exists.
        *
        * @param key The key to insert into the symbol table.
        * @param value The value to associate with the given key.
        */
        void insert(K key, V value) {
            // If it is pointing to the end of the table, the key does not exist in the table
            if (table.find(key) != table.end()) {
                std::cout << "Symbol already exists in the table" << std::endl;
            } else {
                table[key] = value;
            }
        }

        /**
         * ------------------  Exercise 3 ------------------
         * @brief Retrieves the value associated with the given key from the symbol table.
         *
         * This function attempts to find the given key in the symbol table.
         * If the key is found, it returns the associated value.
         * If the key is not found, it prints an error message .
         *
         * @param key The key to search for in the symbol table.
         * @return The value associated with the given key.
         */
        V get(const K &key) const {
            if (table.find(key) == table.end()) {
                std::cout << "Symbol not found in the table" << std::endl;
            }
            return table.find(key)->second;
        }

        /**
         * ------------------  Exercise 3 ------------------
         * @brief Checks if the symbol table contains the given key.
         *
         * @param key The key to check for in the symbol table.
         * @return True if the key exists in the table, false otherwise.
         */
        bool contains(K key) {
            return table.find(key) != table.end();
        }


       /**
        * ------------------  Exercise 3 ------------------
        * @brief Retrieves all the values in the symbol table.
        *
        * This function iterates over all the key-value pairs in the symbol table,
        * and collects all the values into a vector. The order of the values in the
        * vector is the same as the order of the key-value pairs in the symbol table.
        *
        * @return A vector containing all the values in the symbol table.
        */
        std::vector<V> values() {
            std::vector<V> values;
            for (const auto &pair: table) {
                values.push_back(pair.second);
            }
            return values;
        }


        /**
         * ------------------  Exercise 3 ------------------
         * @brief Updates the value associated with a given key in the symbol table.
         *
         * If the key already exists in the table, it updates the value.
         * If the key does not exist, it prints a message indicating that the key was not found.
         *
         * @param key The key for which to update the value.
         * @param value The new value to associate with the given key.
         */
        void update(K key, V value) {
            if (table.find(key) != table.end()) {
                table[key] = value;
            } else {
                std::cout << ("Key not found in SymbolTable") << std::endl;
            }
        }


    };

} // stochastic
