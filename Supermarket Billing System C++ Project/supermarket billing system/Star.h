#ifndef _STAR_H_
#define _STAR_H_

#include "Time.h"

class Star {
private:
    vector<int> stars; //chua so luong sao
    vector<Time> time; //chua thoi gian vote
    vector<int> quantity; //so luong sao vote trong ngay
public:
    float calcAvg(); //tinh trung binh
    void setValue(int x);
    static int convertStar(string s); //chuyen tu string sang int
    void writeToFile(ofstream& out, string s, ifstream& in); //ghi file star.txt
    void readFromFile(ifstream& in); //doc file star.txt
    void printScreen(); //in ra man hinh
};

#endif