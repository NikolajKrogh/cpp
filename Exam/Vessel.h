//
// Created by krogh on 6/5/24.
//

#ifndef EXAM_VESSEL_H
#define EXAM_VESSEL_H

#include "Reaction.h"
#include "SymbolTable.h"

namespace stochastic {

    class Vessel {
    public:
        stochastic::SymbolTable<std::string, Molecule *> molecules;
        std::vector<Reaction> reactions;
        std::string name;

        Vessel(const std::string &name);

        ~Vessel() = default;


        Molecule &add(const std::string &name, double quantity);

        void add(const Reaction &reaction);

        Environment environment();

        void pretty_print();

        void get_digraph();

        std::string get_symbol_table_representation() {
            std::string s = "";
            for (const auto &m: molecules.values()) {
                s += ", " + m->name + ": " + std::to_string(m->quantity);

            }
            return s;
        }
    };
} // stochastic

#endif //EXAM_VESSEL_H