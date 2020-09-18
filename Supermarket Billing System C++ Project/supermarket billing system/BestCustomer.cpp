#include "BestCustomer.h"
#include "Tokenizer.h"

vector<BestCustomer> BestCustomer::readFromFile(ifstream& in) {
    vector<BestCustomer> customer;
    in.open("best customer.txt");
    while (!in.eof()) {
        string buffer;
        getline(in, buffer);
        if (buffer.size() == 0)
            break;
        BestCustomer temp;
        vector<string> tokens = Tokenizer::split(buffer, " - ");
        temp.year = stoi(tokens[0]);
        temp.name = tokens[1];
        temp.phone_number = tokens[2];
        temp.money = stof(tokens[3]);
        customer.push_back(temp);
    }
    in.close();
    return customer;
}

void BestCustomer::writeToFile(ofstream& out, vector<BestCustomer> customer) {
    out.open("best customer.txt");
    for (int i = 0; i < customer.size(); i++)
        out << customer[i].year << " - " << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].money << endl;
    out.close();
}

void BestCustomer::showDetail(vector<BestCustomer> customer) {
    for (int i = 0; i < customer.size(); i++)
        cout << customer[i].year << ". " << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].money << endl;
}

BestCustomer BestCustomer::convert(Customer cus, int year) {
    BestCustomer best;
    best.name = cus.getName();
    best.phone_number = cus.getPhone();
    best.point = cus.getPoint();
    best.money = cus.getMoney();
    best.year = year;
    return best;
}

int BestCustomer::getYear() {
    return this->year;
}
