#include "Time.h"

Time::Time() {//lay time hien tai
    time_t now = time(0);
    tm* t = localtime(&now);
    this->year = 1900 + t->tm_year;
    this->month = 1 + t->tm_mon;
    this->day = t->tm_mday;
    this->hour = t->tm_hour;
    this->min = t->tm_min;
    this->sec = t->tm_sec;
}

int Time::readFromFile(ifstream& in) {
    in.open("year.txt");
    int x;
    in >> x;
    in.close();
    return x;
}

void Time::writeToFile(ofstream& out, int x) {
    out.open("year.txt");
    out << x;
    out.close();
}
