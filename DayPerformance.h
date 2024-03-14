#ifndef ALGO_P1_DAYPERFORMANCE_H
#define ALGO_P1_DAYPERFORMANCE_H


class DayPerformance {
public:
    DayPerformance(int day, int month, int year, double open, double high, double low, double close, int volume, double adjClose);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    double getOpen() const;
    double getHigh() const;
    double getLow() const;
    double getClose() const;
    int getVolume() const;
    double getAdjClose() const;


private:
    int day;
    int month;
    int year;
    double open;
    double high;
    double low;
    double close;
    int volume;
    double adjClose;
};


#endif //ALGO_P1_DAYPERFORMANCE_H
