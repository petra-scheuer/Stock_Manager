#ifndef ALGO_P1_STOCKS_H
#define ALGO_P1_STOCKS_H
#import "SingleStock.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Stocks {
public:
    Stocks();
    int quadraticProbing(int hash, int i, int tableSize);
    SingleStock* findStock(const string& name);
    void addToHashTable(SingleStock newStock);
    unsigned long hashFunction(string name) const;
    void deleteStock(const string& name);
    void printAll() const;

private:
    int tableSize_;
    vector<list<SingleStock>> stocks_;
};


#endif //ALGO_P1_STOCKS_H
