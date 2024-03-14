#include "SingleStock.h"

SingleStock::SingleStock(string name, string wkn, string abbreviation, const DayPerformance& performance)
: name_(name), wkn_(wkn), abbreviation_(abbreviation){
    hashValue_ = hashFunction();
    performance_.push_back(performance);
}

string SingleStock::getName() const {
    return name_;}

string SingleStock::getWkn() const {
    return wkn_; }

string SingleStock::getAbbreviation() const {
    return abbreviation_; }

vector<DayPerformance> SingleStock::getPerformance() const {
    return performance_; }

unsigned long SingleStock::getHashValue() const {
    return hashValue_; }

void SingleStock::addPerformance(const DayPerformance& performance) {
    performance_.push_back(performance);
}
void SingleStock::importData(){
    cout << "You are adding a new stock" << endl;
    cout << "Name: " << endl;
    cin >> name_;
    cout << "WKN: " << endl;
    cin >> wkn_;
    cout << "Abbreviation: " << endl;
    cin >> abbreviation_;
    hashValue_ = hashFunction();
}

void SingleStock::printData() const {
    cout << "Name: " << name_ << endl;
    cout << "WKN: " << wkn_ << endl;
    cout << "Abbreviation: " << abbreviation_ << endl;
    cout << "Hash Value: " << hashValue_ << endl;
    cout << "-------------------------" << endl;
}

void SingleStock::printPerformance() const{

    for (const DayPerformance& performance : performance_){
        cout << "Name: " << name_ << endl;
        cout << "  Date: " << performance.getDay() << "." << performance.getMonth() << "." << performance.getYear() << endl;
        cout << "  Open: " << performance.getOpen() << endl;
        cout << "  High: " << performance.getHigh() << endl;
        cout << "  Low: " << performance.getLow() << endl;
        cout << "  Close: " << performance.getClose() << endl;
        cout << "  Adj Close: " << performance.getAdjClose() << endl;
        cout << "  Volume: " << performance.getVolume() << endl;
        cout << " " << endl;
    }
}

// djb2-Hashfunktion
unsigned long SingleStock::hashFunction() const{
    unsigned long hash = 5381;
    char current = ' ';
    for (char c : name_) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}


void SingleStock::printAsciiGraphLast30Days() const {
    if (performance_.size() < 30) {
        std::cout << "Nicht genügend Daten vorhanden." << std::endl;
        return;
    }

    auto last30Days = std::vector<DayPerformance>(performance_.end() - 30, performance_.end());

    // Ermitteln des Maximal- und Minimalwerts der Schlusskurse
    double maxClose = (*std::max_element(last30Days.begin(), last30Days.end(), [](const DayPerformance& a, const DayPerformance& b) {
        return a.getClose() < b.getClose();
    })).getClose();

    double minClose = (*std::min_element(last30Days.begin(), last30Days.end(), [](const DayPerformance& a, const DayPerformance& b) {
        return a.getClose() < b.getClose();
    })).getClose();

    // Skalieren und Ausgeben der Daten
    for (const auto& day : last30Days) {
        double normalized = (day.getClose() - minClose) / (maxClose - minClose) * 20; // Skalieren auf einen Bereich von 0 bis 20
        std::cout << day.getDay() << "." << day.getMonth() << ": " << std::string(static_cast<size_t>(normalized), '*') << std::endl;
    }
}

