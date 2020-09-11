#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "mainHeader.h"

class Customer {
protected:
    string name;
    string phone_number;
    int point;
    float money;
public:
    void setPoint(int point);
    int getPoint();
    float getMoney();
    string getName();
    string getPhone();
    string getRank();
    void showDetail(); //show thong tin
    void setMoney(float money);
    void updateMoney(float money); //cap nhat tien
    void regis(string name, string phone); //dang ky tai khoan
    bool operator==(const Customer& p);
    void setCustomer(string name, string phone);
    static void sortCustomerPoint(vector<Customer>& cus); //sap xep theo diem
    static void sortCustomerMoney(vector<Customer>& cus); //sap xep theo tien
    vector<Customer> readFromFile(ifstream& in); //doc file customer.txt
    Customer findBestCustomer(ifstream& in); //tim khach hang tot nhat
    void writeToFile(ofstream& out, vector<Customer> customer); //ghi file customer.txt
    void showDetail(vector<Customer> customer, bool flag); //show thong tin danh sach khach hang, flag = true thi show khong hien rank
    bool isAccount(ifstream& in, string name, string phone); //kiem tra tai khoan dang ky chua
    void accumulatePoint(float total); //cap nhat diem tich luy
};

#endif