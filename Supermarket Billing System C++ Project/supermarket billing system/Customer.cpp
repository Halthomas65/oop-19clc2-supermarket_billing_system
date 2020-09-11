#include "Customer.h"
#include "Tokenizer.h"

bool Customer::operator==(const Customer& p) {
    if (this->name == p.name && this->phone_number == p.phone_number)
        return true;
    return false;
}

vector<Customer> Customer::readFromFile(ifstream& in) {
    vector<Customer> customer;
    in.open("customer.txt");
    while (!in.eof()) {
        string buffer;
        getline(in, buffer);
        if (buffer.size() == 0)
            break;
        Customer temp;
        vector<string> tokens = Tokenizer::split(buffer, " - ");
        temp.name = tokens[0];
        temp.phone_number = tokens[1];
        temp.point = stoi(tokens[2]);
        temp.money = stof(tokens[3]);
        customer.push_back(temp);
    }
    in.close();
    return customer;
}

void Customer::setPoint(int point) {
    this->point = point;
}

void Customer::setMoney(float money) {
    this->money = money;
}

int Customer::getPoint() {
    return this->point;
}

float Customer::getMoney() {
    return this->money;
}

string Customer::getName() {
    return this->name;
}

string Customer::getPhone() {
    return this->phone_number;
}

string Customer::getRank() {
    if (this->money < 1000000)
        return "Bronze";
    if (this->money < 3000000)
        return "Silver";
    if (this->money < 5000000)
        return "Gold";
    return "Diamond";
}

void Customer::updateMoney(float money) {
    this->money += money;
}

void Customer::regis(string name, string phone) {
    Customer temp;
    temp.name = name;
    temp.phone_number = phone;
    ifstream in;
    ofstream out;
    vector<Customer> customer = readFromFile(in);
    for (int i = 0; i < customer.size(); i++) {
        if (customer[i].phone_number == temp.phone_number) {
            gotoxy(25, 3);
            cout << "Your account was registered" << endl;
            return;
        }
    }
    temp.point = 0;
    temp.money = 0;
    customer.push_back(temp);
    gotoxy(25, 3);
    cout << "You registered successfully" << endl;
    writeToFile(out, customer);
}

void Customer::writeToFile(ofstream& out, vector<Customer> customer) {
    out.open("customer.txt");
    for (int i = 0; i < customer.size(); i++)
        out << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].point << " - " << customer[i].money << endl;
    out.close();
}

Customer Customer::findBestCustomer(ifstream& in) {
    vector<Customer> temp = readFromFile(in);
    Customer res = temp[0];
    int max = 0;
    for (int i = 1; i < temp.size(); i++) {
        if (res.money < temp[i].money)
            res = temp[i];
    }
    return res;
}

void Customer::sortCustomerPoint(vector<Customer>& cus) {
    for (int i = 0; i < cus.size() - 1; i++) {
        for (int j = i + 1; j < cus.size(); j++) {
            if (cus[i].point < cus[j].point)
                swap(cus[i], cus[j]);
        }
    }
}

void Customer::sortCustomerMoney(vector<Customer>& cus) {
    for (int i = 0; i < cus.size() - 1; i++) {
        for (int j = i + 1; j < cus.size(); j++) {
            if (cus[i].money < cus[j].money)
                swap(cus[i], cus[j]);
        }
    }
}

void Customer::showDetail(vector<Customer> customer, bool flag) {
    if (flag == true) {
        for (int i = 0; i < customer.size(); i++)
            cout << i + 1 << "." << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].point << " - " << customer[i].money << endl;
    }
    else {
        for (int i = 0; i < customer.size(); i++)
            cout << i + 1 << "." << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].point << " - " << customer[i].money << " - " << customer[i].getRank() << endl;
    }
}

bool Customer::isAccount(ifstream& in, string name, string phone) {
    vector<Customer> customer = readFromFile(in);
    for (int i = 0; i < customer.size(); i++) {
        if (name == customer[i].name && phone == customer[i].phone_number)
            return true;
    }
    return false;
}

void Customer::setCustomer(string name, string phone) {
    this->name = name;
    this->phone_number = phone;
}

void Customer::showDetail() {
    cout << "\n\t\tCongratulation " << this->name << " - " << this->phone_number << " - " << this->point << " - " << this->money << endl;
}

void Customer::accumulatePoint(float total) {
    if (total >= 1000000)
        this->point += 3;
    else if (total >= 500000)
        this->point += 2;
    else if (total >= 100000)
        this->point++;
    else
        this->point;
}
