#include "Product.h"
#include "Tokenizer.h"

vector<Product> Product::readFromFile(ifstream& in, string filename) {
    vector<Product> res;
    in.open(filename);
    while (!in.eof()) {
        string temp;
        Product pro;
        getline(in, temp);
        if (temp.size() == 0)
            break;
        vector<string> tokens = Tokenizer::split(temp, " : ");
        pro.name = tokens[0];
        pro.point = stoi(tokens[1]);
        res.push_back(pro);
    }
    in.close();
    return res;
}

void Product::showList(vector<Product> pro) {
    for (int i = 0; i < pro.size(); i++)
        cout << i + 1 << "." << pro[i].name << " : " << pro[i].point << " point" << endl;
}

void Product::showList(vector<Product> pro, int max) {
    for (int i = 0; i < pro.size(); i++) {
        if (pro[i].point <= max)
            cout << "\n\t\t" << i + 1 << "." << pro[i].name << " : " << pro[i].point << " point" << endl;
    }
}

int Product::getPoint() {
    return this->point;
}

string Product::getName() {
    return this->name;
}
