#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "DayPerformance.h"
#include "SingleStock.h"
#include "Stocks.h"

using namespace std;

int main() {
    Stocks allStocks;
    DayPerformance dummyPerformance(0, 0, 0, 0, 0, 0, 0, 0, 0);
    int input = 0;

    // file import
    std::ifstream file("ALGO.csv");
    if (!file.is_open()) {
        std::cerr << "Konnte die Datei nicht öffnen!" << std::endl;
        return 1;
    } else {
        std::cout << "Datei erfolgreich geöffnet!" << std::endl;
    }

    std::string line;
    std::getline(file, line);  // Ignoriere die erste Zeile (Überschrift)

    std::vector<SingleStock> stocks;
    int lineNumber = 0;  // Startet mit 0, da die erste Datenzeile als Zeile 1 zählt

    while (std::getline(file, line)) {
        lineNumber++;  // Aktualisiere die Zeilennummer für jede gelesene Zeile

        // Zeilennummer-basierte Abkürzungs(Zeichencode)-Zuweisung
        std::string abbreviation;
        std::string name;
        std::string WKN;

        if (lineNumber >= 1 && lineNumber <= 250) {
            abbreviation = "MSFT";
            name = "Microsoft Corporation";
            WKN = "870747";
        } else if (lineNumber >= 251 && lineNumber <= 504) {
            abbreviation = "RY4C";
            name = "Ryanair Holding";
            WKN = "A1401Z";
        } else if (lineNumber >= 505 && lineNumber <= 755) {
            abbreviation = "TSLA";
            name = "Tesla, Inc.";
            WKN ="A1CX3T";
        } else if (lineNumber >= 756 && lineNumber <= 1008) {
            abbreviation = "PKTM";
            name = "PIERER Mobility AG";
            WKN ="A2JKHY";
        }

        std::replace(line.begin(), line.end(), ',', '.');
        std::replace(line.begin(), line.end(), ';', ',');

        std::vector<std::string> tokens;
        std::istringstream tokenStream(line);
        std::string token;

        while (std::getline(tokenStream, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 8) {
            int day, month, year;
            sscanf(tokens[0].c_str(), "%d.%d.%d", &day, &month, &year);

            DayPerformance dayPerformance(day, month, year,
                                          std::stod(tokens[1]), std::stod(tokens[2]), std::stod(tokens[3]),
                                          std::stod(tokens[4]), std::stoi(tokens[6]), std::stod(tokens[5]));

            SingleStock stock(name, WKN, abbreviation, dayPerformance);  // Verwende abbreviation für die Abkürzung, has Value == HASH VALUE

            SingleStock* existingStock = allStocks.findStock(stock.getName());
            if (existingStock) {
                existingStock->addPerformance(dayPerformance);

            } else {
                allStocks.addToHashTable(stock);
            }
        }
    }

    file.close();


    cout << "Welcome to our Stock Manager!" << endl;

    do{
        cout << "What do you want to do? Print collection (1), add Stock (2), search for Stock (3), delete Stock(4), print Plot (5)" << endl;
        cin >> input;
        if (input != 1 && input != 2 && input != 3 && input != 4 && input != 0 && input !=5){
            cout << "Input was not valid. Try again! Print collection (1), add Stock (2), search for Stock (3), delete Stock(4), print Plot (5)";
            cin >> input;
        }
        if(input == 1){
            allStocks.printAll();
        } else if(input == 2){
            SingleStock newStock("", "", "", dummyPerformance);
            newStock.importData();
            allStocks.addToHashTable(newStock);
            cout << "This stock has been added to your Stock Collection: " << endl;
            newStock.printData();
        } else if(input == 3){
            string toSearch;
            cout << "Type in the name of the stock you are searching for!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline
            getline(cin, toSearch);
            SingleStock* searchedStock = allStocks.findStock(toSearch);
            if(searchedStock){
                searchedStock->printData();
            } else {
                cout << "Stock not found!" << endl;
            }
        } else if(input == 4){
            cout << "Your current list of stocks: " << endl;
            allStocks.printAll();
            string toDelete;
            cout << "Type in the name of the stock you want to delete!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline
            getline(cin, toDelete);
            allStocks.deleteStock(toDelete);
            cout << " " << endl;
            cout << "New List of Stocks: " << endl;
            allStocks.printAll();
        }
        else if( input == 5){
                string toSearch;
                cout << "Geben Sie den Namen der Aktie ein, für die Sie die letzten 30 Tage als ASCII-Grafik anzeigen möchten: "<<endl;
                allStocks.printAll();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline
                getline(cin, toSearch);
                SingleStock* searchedStock = allStocks.findStock(toSearch);
                if(searchedStock) {
                    searchedStock->printAsciiGraphLast30Days();
                }
                else {
                    cout << "Aktie nicht gefunden." << endl;
                }
        }

        } while (input != 0);

    return 0;
}

