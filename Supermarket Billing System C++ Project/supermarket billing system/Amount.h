#ifndef _AMOUNT_H_
#define _AMOUNT_H_

#include "Item.h"

class Amount : public Item
{
    float price, qty, tax, gross, dis, netamt;
public:
    void add();
    void input();
    void edit();
    void remove();
    void removeAll();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

#endif