#include "Stocks.h"
#include <fstream>

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
void Stocks::saveToFile(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Konnte die Datei nicht zum Speichern öffnen." << endl;
        return;
    }

    // Write the header
    file << "Date,Open,High,Low,Close,Adj Close,Volume,Aktie\n";

    for (const auto& bucket : stocks_) {
        for (const auto& stock : bucket) {
            // Get the performances for the stock
            const auto& performances = stock.getPerformance();
            for (const auto& performance : performances) {
                // Write data in the desired format with commas as delimiters
                // Ensure numeric values use period as the decimal separator
                // Convert date to desired format with periods
                file << performance.getDay() << "."
                     << performance.getMonth() << "."
                     << performance.getYear() << ","
                     << performance.getOpen() << ","
                     << performance.getHigh() << ","
                     << performance.getLow() << ","
                     << performance.getClose() << ","
                     << performance.getAdjClose() << ","
                     << performance.getVolume() << ","
                     << stock.getAbbreviation() << "\n"; // Use abbreviation for "Aktie"
            }
        }
    }

    file.close();
    cout << "Daten erfolgreich in " << filename << " gespeichert." << endl;
}
