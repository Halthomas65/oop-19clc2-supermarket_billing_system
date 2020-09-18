#ifndef MONEY_H
#define MONEY_H

#include "Time.h"

class Money {
private:
    vector<Time> time;
    vector<int> quantity;
    vector<float> money;
public:
    void readFromFile(ifstream& in, int year); //doc file (nam).txt
    void writeToFile(ofstream& out, int year, float price, ifstream& in, Time cur); //ghi file (nam).txt
    float calcOneDay(Time cur); //tinh tien trong 1 ngay
    float calcOneMonth(Time cur); //tinh tien trong 1 thang
    float calcOneYear(Time cur); //tinh tien trong 1 nam
    int countOneDay(Time cur); //dem so luot khach hang 1 ngay
    int countOneMonth(Time cur); //dem so luot khach hang 1 thang
    int countOneYear(Time cur); //dem so luot khach hang 1 nam
};

#endif // !MONEY_H

