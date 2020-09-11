#ifndef _TIME_H_
#define _TIME_H_

#include "mainHeader.h"

class Time {
private:
    int day, month, year, hour, min, sec;
public:
    Time();
    static void writeToFile(ofstream& out, int year); //ghi file year.txt
    static int readFromFile(ifstream& in); //doc file year.txt
    void setYear(int year) {
        this->year = year;
    }
    void setMonth(int month) {
        this->month = month;
    }
    void setDay(int day) {
        this->day = day;
    }
    int getYear() {
        return this->year;
    }
    int getMonth() {
        return this->month;
    }
    int getDay() {
        return this->day;
    }
    int getHour() {
        return this->hour;
    }
    int getMin() {
        return this->min;
    }
    int getSec() {
        return this->sec;
    }
};


#endif