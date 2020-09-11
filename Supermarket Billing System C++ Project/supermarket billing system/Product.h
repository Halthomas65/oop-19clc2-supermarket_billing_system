#ifndef PRODUCT_H
#define PRODUCT_H

#include "mainHeader.h"

class Product {
private:
    string name;
    int point;
public:
    static vector<Product> readFromFile(ifstream& in, string filename); //doc file product.txt
    static void showList(vector<Product> pro); //show danh sach
    static void showList(vector<Product> pro, int max);//show danh sach voi dieu kien la so diem cac san pham nho hon so diem cua khach hang
    int getPoint();
    string getName();
};

#endif // !PRODUCT_H

