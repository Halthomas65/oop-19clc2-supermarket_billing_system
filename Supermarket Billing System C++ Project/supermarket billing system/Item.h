#ifndef _ITEM_H_
#define _ITEM_H_

#include "mainHeader.h"

class Item
{
    int itemno;
    char name[25];
    char Time[50];
public:
    char* getTime();
    void add();
    void show();
    void report();
    int retno();
    string getName();
    void getInfo(vector<int> no, vector<string> name);
};

#endif