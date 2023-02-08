#pragma once

#include <string>
#include <vector>
#include "Debug.h"


class SymbolTableClass {

    struct Variable
    {
        std::string mLabel;
        int mValue;
    };

    public:
        SymbolTableClass();
        ~SymbolTableClass();
        bool Exists(const std::string & s);
        void AddEntry(const std::string & s);
        int GetValue(const std::string & s);
        void SetValue(const std::string & s, int v);
        int GetIndex(const std::string & s);
        size_t GetCount();
    private:
        std::vector<Variable> symbolTable;
};