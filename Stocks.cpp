#include "Stocks.h"

Stocks::Stocks() :  tableSize_(1334), stocks_(tableSize_) {
}

SingleStock* Stocks::findStock(const string& name) {
    unsigned long hashValue = hashFunction(name);
    int index = hashValue % tableSize_;

    for (SingleStock& stock : stocks_[index]) {
        if (stock.getName() == name) {
            return &stock;
        }
    }
    return nullptr;
}

void Stocks::deleteStock(const string& name){
    unsigned long hashValue = hashFunction(name);
    int index = hashValue % tableSize_;

    list<SingleStock>& bucket = stocks_[index];
    for (list<SingleStock>::iterator it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->getName() == name) {
            bucket.erase(it);
            return;
        }
    }

    cout << "Stock not found!" << endl;
}

int Stocks::quadraticProbing(int hash, int i, int tableSize) {
        return (hash + i * i) % tableSize_;
}

// djb2-Hashfunktion
unsigned long Stocks::hashFunction(string name) const{
    unsigned long hash = 5381;
    for (char c : name) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void Stocks::addToHashTable(SingleStock newStock){
    int hashValue = newStock.getHashValue() % tableSize_;
    int i = 0;
    int index = quadraticProbing(hashValue, i, tableSize_);
    while (!stocks_[index].empty() && i < tableSize_) {
        i++;
        index = quadraticProbing(hashValue, i, tableSize_);
    }
    stocks_[index].push_back(newStock);
};

void Stocks::printAll() const {
    for (const auto& bucket : stocks_) {  // Iterate over each bucket in the hash table
        for (const auto& item : bucket) {  // Iterate over each item in the list
            item.printData();  // Print the item's data
        }
    }
}
