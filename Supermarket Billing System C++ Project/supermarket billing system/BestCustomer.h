#ifndef _BEST_CUSTOMER_H_
#define _BEST_CUSTOMER_H_

#include "Customer.h"

class BestCustomer : public Customer {
private:
    int year;
public:
    int getYear();
    static vector<BestCustomer> readFromFile(ifstream& in); //doc file best customer.txt
    static void writeToFile(ofstream& out, vector<BestCustomer> customer); //ghi file customer.txt
    static void showDetail(vector<BestCustomer> customer); // show thong tin 
    BestCustomer convert(Customer cus, int year); //chuyen tu customer sang best customer
};

#endif // !_BEST_CUSTOMER_H_

