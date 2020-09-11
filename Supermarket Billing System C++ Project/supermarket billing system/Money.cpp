#include "Money.h"
#include "Tokenizer.h"

void Money::readFromFile(ifstream& in, int year) {
    string filename = to_string(year) + ".txt";
    in.open(filename);
    while (!in.eof()) {
        string line;
        getline(in, line);
        if (line.size() == 0)
            break;
        vector<string> tokens = Tokenizer::split(line, " ");
        if (tokens.size() == 3) {
            Time p;
            p.setDay(stoi(tokens[0]));
            p.setMonth(stoi(tokens[1]));
            p.setYear(stoi(tokens[2]));
            time.push_back(p);
            quantity.push_back(0);
        }
        else {
            money.push_back(stof(tokens[0]));
            quantity[quantity.size() - 1]++;
        }
    }
    in.close();
}

void Money::writeToFile(ofstream& out, int year, float price, ifstream& in, Time cur) {
    readFromFile(in, year);
    if (cur.getYear() == year) {
        if (cur.getDay() == time[time.size() - 1].getDay() && cur.getMonth() == time[time.size() - 1].getMonth()) {
            quantity[quantity.size() - 1]++;
            money.push_back(price);
        }
        else {
            time.push_back(cur);
            quantity.push_back(1);
            money.push_back(price);
        }
    }
    else {
        year = cur.getYear();
        time.clear();
        time.push_back(cur);
        quantity.clear();
        quantity.push_back(1);
        money.clear();
        money.push_back(price);
    }
    string filename = to_string(year) + ".txt";
    out.open(filename);
    int index = 0;
    for (int i = 0; i < time.size(); i++) {
        out << time[i].getDay() << " " << time[i].getMonth() << " " << time[i].getYear() << endl;
        for (int j = 0; j < quantity[i]; j++) {
            out << money[index] << endl;
            index++;
        }
    }
    out.close();
}

float Money::calcOneDay(Time cur) {
    float sum = 0;
    int index = 0;
    for (int i = 0; i < time.size(); i++) {
        if (time[i].getDay() == cur.getDay() && time[i].getMonth() == cur.getMonth() && time[i].getYear() == cur.getYear()) {
            for (int j = 0; j < quantity[i]; j++) {
                sum += money[index];
                index++;
            }
        }
        else {
            index += quantity[i];
        }
    }
    return sum;
}

float Money::calcOneMonth(Time cur) {
    float sum = 0;
    int index = 0;
    for (int i = 0; i < time.size(); i++) {
        if (time[i].getMonth() == cur.getMonth() && time[i].getYear() == cur.getYear()) {
            for (int j = 0; j < quantity[i]; j++) {
                sum += money[index];
                index++;
            }
        }
        else {
            index += quantity[i];
        }
    }
    return sum;
}

float Money::calcOneYear(Time cur) {
    float sum = 0;
    for (int i = 0; i < money.size(); i++)
        sum += money[i];
    return sum;
}

int Money::countOneDay(Time cur) {
    for (int i = 0; i < time.size(); i++) {
        if (cur.getDay() == time[i].getDay() && cur.getMonth() == time[i].getMonth()) {
            return quantity[i];
        }
    }
    return 0;
}

int Money::countOneMonth(Time cur) {
    int count = 0;
    for (int i = 0; i < time.size(); i++) {
        if (cur.getMonth() == time[i].getMonth())
            count += quantity[i];
    }
    return count;
}

int Money::countOneYear(Time cur) {
    int count = 0;
    for (int i = 0; i < time.size(); i++)
        count += quantity[i];
    return count;
}
