#include "DayPerformance.h"

DayPerformance::DayPerformance(int day, int month, int year, double open, double high, double low, double close, int volume, double adjClose)
        : day(day), month(month), year(year), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose) {}


int DayPerformance::getDay() const { return day; }
int DayPerformance::getMonth() const { return month; }
int DayPerformance::getYear() const { return year; }
double DayPerformance::getOpen() const { return open; }
double DayPerformance::getHigh() const { return high; }
double DayPerformance::getLow() const { return low; }
double DayPerformance::getClose() const { return close; }
int DayPerformance::getVolume() const { return volume; }
double DayPerformance::getAdjClose() const { return adjClose; }