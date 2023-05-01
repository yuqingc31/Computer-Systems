#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <cstdint>  // this contains uint16_t
#include <map>      // indexable dictionary
#include <string>   // process c++ string
#include <stdexcept>

using namespace std;

class SymbolTable {
    private:
    map<string,uint16_t> table;
    // int LabelCounter;

   public:
    SymbolTable();
    ~SymbolTable();

    void addSymbol(string symbol, uint16_t value);
    int getSymbol(string symbol);
    int addressCounter;
};

#endif /* SYMBOL_TABLE_H */