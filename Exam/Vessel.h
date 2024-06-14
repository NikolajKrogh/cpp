#pragma once

#include "Reaction.h"
#include "SymbolTable.h"
#include "Arrow.h"

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

        void assign_tags(SymbolTable <std::string, std::string> &table, int &counter);

        std::vector<Arrow> create_arrows(const SymbolTable <std::string, std::string> &table);

        void write_to_file(const std::vector<Arrow> &arrows, const SymbolTable <std::string, std::string> &table);
    };
} // stochastic

