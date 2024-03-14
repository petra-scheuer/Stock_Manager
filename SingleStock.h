#ifndef ALGO_P1_SINGLESTOCK_H
#define ALGO_P1_SINGLESTOCK_H
#include <iostream>
#include "DayPerformance.h"

using namespace std;

class SingleStock {
public:
    SingleStock(string name, string wkn, string abbreviation, const DayPerformance& performance);
    string getName() const;
    string getWkn() const;
    string getAbbreviation() const;
    vector<DayPerformance> getPerformance() const;
    unsigned long getHashValue() const;
    void addPerformance(const DayPerformance& performance);
    void importData();
    void printData() const;
    void printPerformance() const;
    unsigned long hashFunction() const;
    void printAsciiGraphLast30Days() const;


private:
    string name_;
    string wkn_;
    string abbreviation_;
    vector<DayPerformance> performance_;
    unsigned long hashValue_;

};


#endif //ALGO_P1_SINGLESTOCK_H
