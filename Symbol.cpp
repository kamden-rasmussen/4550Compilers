#include "Symbol.h"


SymbolTableClass::SymbolTableClass(){
    this->symbolTable = std::vector<Variable>();
}

SymbolTableClass::~SymbolTableClass(){
}

bool SymbolTableClass::Exists(const std::string &s){
    for (Variable v : symbolTable)
    {
        if (v.mLabel == s)
            return true;
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string &s){
    if (!Exists(s))
    {
        Variable v = {s, 0};
        symbolTable.push_back(v);
    }
    else {
        std::cout << "variable already exists: " << s << std::endl;
        exit(EXIT_FAILURE);
    }
}

int SymbolTableClass::GetValue(const std::string &s){
    int index = GetIndex(s);
    if (index != -1)
        return symbolTable[index].mValue;
    else
    {
        std::cout << "variable does not exist: " << s << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SymbolTableClass::SetValue(const std::string &s, int v){
    int index = GetIndex(s);
    if (index != -1)
        symbolTable[index].mValue = v;
    else
    {
        std::cout << "variable does not exist: " << s << std::endl;
        exit(EXIT_FAILURE);
    }
}

int SymbolTableClass::GetIndex(const std::string &s){
    for (int i = 0; i < symbolTable.size(); i++)
    {
        if (symbolTable[i].mLabel == s)
            return i;
    }
    return -1;
}

size_t SymbolTableClass::GetCount(){
    return this->symbolTable.size();
}