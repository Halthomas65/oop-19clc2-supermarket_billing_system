#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
#include <vector>
#include <ctime>
#include <string>
using namespace std;
//global variable declaration
int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

ofstream fout;
ifstream fin;

class Time {
private:
    int day, month, year, hour, min, sec;
public:
    Time();
    void setYear(int year) {
        this->year = year;
    }
    void setMonth(int month) {
        this->month = month;
    }
    void setDay(int day) {
        this->day = day;
    }
    int getYear() {
        return this->year;
    }
    int getMonth() {
        return this->month;
    }
    int getDay() {
        return this->day;
    }
    int getHour() {
        return this->hour;
    }
    int getMin() {
        return this->min;
    }
    int getSec() {
        return this->sec;
    }
};

class Random {
public:
    Random() {
        srand(time(NULL));
    }
    int next(int a, int b) {
        int delta = b - a + 1;
        return a + rand() % delta;
    }
};

class Tokenizer
{
public:
    static vector<string> split(string haystack, string needle);
};

class feedback {
private:
    char phone[11];
    char name[26];
    char Feedback[101];
public:
    void addFeedback()
    {
        cin.ignore();
        fout.open("Storefeedback1.dat", ios::binary | ios::app);
        if (!fout.is_open())
        {
            cout << "\n\n\tCant create file !!!";
            return;
        }
        cout << "\n\n\tPhone: ";
        cin.getline(phone, 10);

        cout << "\n\n\tCustomer Name: ";
        cin.ignore();
        cin.getline(name, 25);

        cout << "\n\n\tContent: ";
        cin.ignore();
        cin.getline(Feedback, 100);
        cout << "\n\n\n\tThank your feed back, We will try our best to solve this problem. ";
        fout.write((char*)&fbk, sizeof(fbk));
        fout.close();
        _getch();
    }
    void showFeedback()
    {
        fin.open("Storefeedback1.dat", ios::binary);
        if (!fin.is_open())
        {
            cout << "\n\nFile Not Found...";
            return;
        }
        while (fin.read((char*)&fbk, sizeof(fbk)))
        {
            cout << "\n\tCustom Name: ";
            cout << name;
            cout << "\n\n\tPhone: ";
            cout << phone;
            cout << "\n\n\tFeedback: " << Feedback;
            cout << "\n\t\n--------------------------";
        }
        fin.close();
        _getch();
    }
    void removeFeedback()
    {
        char phone[11];
        flag = 0;
        vector<feedback> tmp_fbk;
        cout << "\n\n\tEnter Phone Number of customer :";
        cin.ignore();
        cin.getline(phone, 10);
        fin.open("Storefeedback1.dat", ios::binary);

        if (!fin.is_open())
        {
            cout << "\n\nFile Not Found...";
            return;
        }
        fin.seekg(0, ios::beg);
        //r = 0;
        while (fin.read((char*)&fbk, sizeof(fbk)))
        {


            if (strcmp(phone, fbk.returnPhone()) != 0)
                tmp_fbk.push_back(fbk);
            else
                flag = 1;

        }
        fin.close();


        if (flag == 1)
        {
            fout.open("Storefeedback1.dat", ios::binary);
            fout.seekp(0, ios::beg);
            cout << "\n\t\tItem Succesfully Deleted";
            for (int i = 0; i < tmp_fbk.size(); i++)
                fout.write((char*)&tmp_fbk[i], sizeof(fbk));
            fout.close();
        }
        if (flag == 0)
        {
            cout << "\n\t\tPhone No does not exist...Please Retry!";
            _getch();
            return;
        }
        _getch();


    }
    char* returnPhone()
    {
        return fbk.phone;
    }
} fbk;

class item
{
    int itemno;
    char name[25];
    char Time[50];
public:
    char* getTime()
    {
        // tra ve date/time hien tai dua tren system hien tai
        time_t hientai = time(0);

        // chuyen doi hientai thanh dang chuoi
        char* dt = ctime(&hientai);


        strcpy(Time, dt);
        cout << "Time of Bill: " << dt << endl;

        return dt;
    }
    void add()
    {
        cout << "\n\n\tItem No: ";
        cin >> itemno;
        cin.ignore();
        cout << "\n\n\tName of the item: ";
        cin.getline(name, 25);
        cout << "\n\n\t";
        //gets(name);
        char* Time = getTime();
        strcpy(this->Time, Time);
    }
    void show()
    {
        cout << "\n\tItem No: ";
        cout << itemno;
        cout << "\n\n\tName of the item: ";
        cout << name;
        cout << "\n\n\tTime: " << Time << endl;
    }
    void report()
    {
        gotoxy(3, k);
        cout << itemno;
        gotoxy(13, k);
        puts(name);
    }
    int retno()
    {
        return(itemno);
    }
    string getName() {
        string temp(name);
        return temp;
    }
    void getInfo(vector<int> no, vector<string> name) {
        for (int i = 0; i < no.size() - 1; i++) {
            for (int j = i + 1; j < no.size(); j++) {
                if (no[i] > no[j]) {
                    swap(no[i], no[j]);
                    swap(name[i], name[j]);
                }
            }
        }
        for (int i = 0; i < no.size(); i++)
            cout << "\n\t\t\t" << no[i] << ". " << name[i];
    }
};

class amount : public item
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

void amount::add()
{
    item::add();
    cout << "\n\n\tPrice: ";
    cin >> price;
    cout << "\n\n\tQuantity: ";
    cin >> qty;
    cout << "\n\n\tTax percent: ";
    cin >> tax;
    cout << "\n\n\tDiscount percent: ";
    cin >> dis;
    calculate();
    fout.write((char*)&amt, sizeof(amt));
    fout.close();
}

void amount::input()
{
    item::add();
    cout << "\n\n\tPrice: ";
    cin >> price;
    cout << "\n\n\tQuantity: ";
    cin >> qty;
    cout << "\n\n\tTax percent: ";
    cin >> tax;
    cout << "\n\n\tDiscount percent: ";
    cin >> dis;
    calculate();
}

void amount::edit()
{
    int ino;
    flag = 0;
    vector<amount> tmp_amt;
    cout << "\n\n\tEnter Item Number to be Edited :";
    cin >> ino;
    fin.open("itemstore.dat", ios::binary);

    if (!fin.is_open())
    {
        cout << "\n\nFile Not Found...";
        return;
    }
    fin.seekg(0, ios::beg);
    r = 0;
    // int count = 0;
    while (fin.read((char*)&amt, sizeof(amt)))
    {

        int x = amt.item::retno();
        if (x == ino)
        {
            flag = 1;
            // fout.seekp(r * sizeof(amt));
            system("cls");
            /*cout << "\n\t\tCurrent Details are\n";
            amt.show();*/
            //fin.open("itemstore.dat", ios::binary);
            //fin.seekg(r * sizeof(amt), ios::beg);
            cout << "\n\n\t\tEnter New Details\n";
            amt.input();
            cout << "\n\t\tItem Details editted";
        }
        tmp_amt.push_back(amt);
        r++;

    }
    // cout << endl << count << endl;
    fin.close();

    fout.open("itemstore.dat", ios::binary);
    fout.seekp(0, ios::beg);
    if (flag == 1)
    {
        cout << endl << tmp_amt.size() << endl;
        for (int i = 0; i < tmp_amt.size(); i++)
            fout.write((char*)&tmp_amt[i], sizeof(amt));
    }
    if (flag == 0)
    {
        cout << "\n\t\tItem No does not exist...Please Retry!";
        _getch();
        return;
    }
    _getch();
    fout.close();
}

void amount::remove()
{
    int ino;
    flag = 0;
    vector<amount> tmp_amt;
    cout << "\n\n\tEnter Item Number to be Edited :";
    cin >> ino;
    fin.open("itemstore.dat", ios::binary);

    if (!fin.is_open())
    {
        cout << "\n\nFile Not Found...";
        return;
    }
    fin.seekg(0, ios::beg);
    //r = 0;
    while (fin.read((char*)&amt, sizeof(amt)))
    {

        int x = amt.item::retno();
        if (x != ino)
            tmp_amt.push_back(amt);
        else
            flag = 1;

    }
    fin.close();


    if (flag == 1)
    {
        fout.open("itemstore.dat", ios::binary);
        fout.seekp(0, ios::beg);
        cout << "\n\t\tItem Succesfully Deleted";
        for (int i = 0; i < tmp_amt.size(); i++)
            fout.write((char*)&tmp_amt[i], sizeof(amt));
        fout.close();
    }
    if (flag == 0)
    {
        cout << "\n\t\tItem No does not exist...Please Retry!";
        _getch();
        return;
    }
    _getch();


}

void amount::removeAll()
{
    fout.open("itemstore.dat", ios::binary);
    fout.close();
}

void amount::calculate()
{
    gross = price + (price * (tax / 100));
    netamt = qty * (gross - (gross * (dis / 100)));
}

void amount::show()
{
    fin.open("itemstore.dat", ios::binary);
    fin.read((char*)&amt, sizeof(amt));
    item::show();
    cout << "\n\n\tNet amount: ";
    cout << netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23, k);
    cout << price;
    gotoxy(33, k);
    cout << qty;
    gotoxy(44, k);
    cout << tax;
    gotoxy(52, k);
    cout << dis;
    gotoxy(64, k);
    cout << netamt;
    k = k + 1;
    if (k == 50)
    {
        gotoxy(25, 50);
        cout << "PRESS ANY KEY TO CONTINUE...";
        _getch();
        k = 7;
        system("cls");
        gotoxy(30, 3);
        cout << " ITEM DETAILS ";
        gotoxy(3, 5);
        cout << "NUMBER";
        gotoxy(13, 5);
        cout << "NAME";
        gotoxy(23, 5);
        cout << "PRICE";
        gotoxy(33, 5);
        cout << "QUANTITY";
        gotoxy(44, 5);
        cout << "TAX";
        gotoxy(52, 5);
        cout << "DEDUCTION";
        gotoxy(64, 5);
        cout << "NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout << "\n\n\n\t\t*********************************************";
    cout << "\n\t\t                 DETAILS                  ";
    cout << "\n\t\t*********************************************";
    cout << "\n\n\t\tPRICE                     :" << price;
    cout << "\n\n\t\tQUANTITY                  :" << qty;
    cout << "\n\t\tTAX PERCENTAGE              :" << tax;
    cout << "\n\t\tDISCOUNT PERCENTAGE         :" << dis;
    cout << "\n\n\n\t\tNET AMOUNT              :Rs." << netamt;
    cout << "\n\t\t*********************************************";
}

class Star {
private:
    vector<int> stars;
    vector<Time> time;
    vector<int> quantity;
public:
    float calcAvg();
    void setValue(int x);
    static int convertStar(string s);
    void writeToFile(ofstream& out, string s, ifstream& in);
    void readFromFile(ifstream& in);
    void printScreen();
};

class Customer {
private:
    string name;
    string phone_number;
    int point;
public:
    int getPoint();
    void regis(string name, string phone);
    bool operator==(const Customer& p);
    void setCustomer(string name, string phone);
    vector<Customer> readFromFile(ifstream& in);
    void writeToFile(ofstream& out, vector<Customer> customer);
    void showDetail(vector<Customer> customer);
    bool isAccount(ifstream& in, string name, string phone);
    void accumulatePoint(float total);
};

class Game {
private:
    vector<int> value;
    int num;
    Random rng;
public:
    void setNum(float total);
    int getNum();
    Game();
    void show();
    bool isSame();
    int getValue(int x);
};

Time::Time() {
    time_t now = time(0);
    tm* t = localtime(&now);
    this->year = 1900 + t->tm_year;
    this->month = 1 + t->tm_mon;
    this->day = t->tm_mday;
    this->hour = t->tm_hour;
    this->min = t->tm_min;
    this->sec = t->tm_sec;
}

vector<string> Tokenizer::split(string haystack, string needle) {
    vector<string> tokens;
    int startPosition = 0;
    while (true) {
        size_t position = haystack.find(needle, startPosition);
        if (position != string::npos) {
            string token = haystack.substr(startPosition, position - startPosition);
            startPosition = position + needle.length();
            tokens.push_back(token);
        }
        else {
            string token = haystack.substr(startPosition, haystack.length());
            tokens.push_back(token);
            break;
        }
    }
    return tokens;
}

void Star::setValue(int x) {
    this->stars.push_back(x);
}

float Star::calcAvg() {
    int sum = 0;
    for (int i = 0; i < this->stars.size(); i++)
        sum = sum + this->stars[i];
    return sum * 1.0 / this->stars.size();
}

int Star::convertStar(string s) {
    if (s == "*")
        return 1;
    if (s == "**")
        return 2;
    if (s == "***")
        return 3;
    if (s == "****")
        return 4;
    if (s == "*****")
        return 5;
    return -1;
}

void Star::printScreen() {
    int index = 0;
    for (int i = 0; i < this->time.size(); i++) {
        cout << this->time[i].getDay() << "/" << this->time[i].getMonth() << "/" << this->time[i].getYear() << endl;
        for (int j = 0; j < this->quantity[i]; j++) {
            cout << this->stars[index] << " ";
            index++;
        }
        cout << endl;
    }
}

void Star::writeToFile(ofstream& out, string s, ifstream& in) {
    this->readFromFile(in);
    Time cur;
    if (this->time.size() == 0) {
        this->time.push_back(cur);
        this->stars.push_back(this->convertStar(s));
        this->quantity.push_back(1);
    }
    else {
        if (cur.getDay() == this->time[this->time.size() - 1].getDay() && cur.getMonth() == this->time[this->time.size() - 1].getMonth() && cur.getYear() == this->time[this->time.size() - 1].getYear()) {
            this->stars.push_back(this->convertStar(s));
            this->quantity[this->quantity.size() - 1]++;
        }
        else {
            this->time.push_back(cur);
            this->stars.push_back(this->convertStar(s));
            this->quantity.push_back(1);
        }
    }
    out.open("star.txt");
    int index = 0;
    for (int i = 0; i < this->time.size(); i++) {
        out << this->time[i].getDay() << " " << this->time[i].getMonth() << " " << this->time[i].getYear() << endl;
        for (int j = 0; j < this->quantity[i]; j++) {
            out << this->stars[index] << " ";
            index++;
        }
        out << endl;
    }
    out.close();
}

void Star::readFromFile(ifstream& in) {
    in.open("star.txt");
    int count = 1;
    string res;
    while (!in.eof()) {
        getline(in, res);
        if (res.size() == 0)
            break;
        vector<string> tokens = Tokenizer::split(res, " ");
        vector<int> nums;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].size() == 0)
                break;
            int x = stoi(tokens[i]);
            nums.push_back(x);
        }
        if (count % 2 == 1) {
            Time cur;
            cur.setDay(nums[0]);
            cur.setMonth(nums[1]);
            cur.setYear(nums[2]);
            this->time.push_back(cur);
        }
        else {
            this->quantity.push_back(nums.size());
            for (int i = 0; i < nums.size(); i++)
                this->stars.push_back(nums[i]);
        }
        count++;
    }
    in.close();
}

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
        customer.push_back(temp);
    }
    in.close();
    return customer;
}

int Customer::getPoint() {
    return this->point;
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
    customer.push_back(temp);
    gotoxy(25, 3);
    cout << "You registered successfully" << endl;
    writeToFile(out, customer);
}

void Customer::writeToFile(ofstream& out, vector<Customer> customer) {
    out.open("customer.txt");
    for (int i = 0; i < customer.size(); i++)
        out << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].point << endl;
    out.close();
}

void Customer::showDetail(vector<Customer> customer) {
    for (int i = 0; i < customer.size(); i++)
        cout << i + 1 << "." << customer[i].name << " - " << customer[i].phone_number << " - " << customer[i].point << endl;
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

void Customer::accumulatePoint(float total) {
    if (total >= 1000000)
        this->point += 3;
    else if (total >= 500000)
        this->point += 2;
    else
        this->point++;
}

Game::Game() {
    vector<int> percent = { 10,10,10,10,20,20,20,30,30,50 };
    int size = 9;
    while (percent.size() != 0) {
        int i = this->rng.next(0, size);
        this->value.push_back(percent[i]);
        percent.erase(percent.begin() + i);
        size--;
    }
}

void Game::setNum(float total) {
    int t = int(total);
    while (t != 0) {
        this->num = t % 10;
        if (this->num != 0)
            break;
        t = t / 10;
    }
}

bool Game::isSame() {
    int x = this->rng.next(0, 9);
    if (this->num == x)
        return true;
    gotoxy(25, 3);
    cout << "\n\t\tRandom number: " << x << endl;
    return false;
}

int Game::getNum() {
    return this->num;
}

int Game::getValue(int x) {
    return this->value[x - 1];
}

void Game::show() {
    for (int i = 0; i < this->value.size(); i++)
        cout << this->value[i] << "%  ";
}

#include "Header.h"

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat", ios::binary | ios::out);
menu:
    system("cls");
    gotoxy(25, 2);
    cout << "Super Market Billing ";
    gotoxy(25, 3);
    cout << "===========================\n\n";
    cout << "\n\t\t1.Bill Report\n\n";
    cout << "\t\t2.Add/Remove/Edit Item\n\n";
    cout << "\t\t3.Show Item Details\n\n";
    cout << "\t\t4.Feed back\n\n";
    cout << "\t\t5.Register\n\n";
    cout << "\t\t6.Service Customer\n\n";
    cout << "\t\t7.Exit\n\n";
    cout << "\t\tPlease Enter Required Option: ";
    int ch, ff;
    float gtotal = 0, total = 0;
    bool flag = true;
    Customer cus;
    cin >> ch;
    switch (ch)
    {
    case 1:
    ss:
        system("cls");
        gotoxy(25, 2);
        cout << "Bill Details";
        gotoxy(25, 3);
        cout << "================\n\n";
        cout << "\n\t\t1.All Items\n\n";
        cout << "\t\t2.Back to Main menu\n\n";
        cout << "\t\tPlease Enter Required Option: ";
        int cho;
        cin >> cho;
        if (cho == 1)
        {
            system("cls");
            gotoxy(30, 3);
            cout << " BILL DETAILS ";
            gotoxy(3, 5);
            cout << "ITEM NO";
            gotoxy(13, 5);
            cout << "NAME";
            gotoxy(23, 5);
            cout << "PRICE";
            gotoxy(33, 5);
            cout << "QUANTITY";
            gotoxy(44, 5);
            cout << "TAX %";
            gotoxy(52, 5);
            cout << "DISCOUNT %";
            gotoxy(64, 5);
            cout << "NET AMOUNT";
            fin.open("itemstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal = 0;
            while (fin.read((char*)&amt, sizeof(amt)))
            {


                amt.report();
                gtotal += amt.retnetamt();
                ff = 0;

            }
            gotoxy(17, k);
            cout << "\n\n\n\t\t\tGrand Total=" << gtotal;
            _getch();
            fin.close();
        }
        if (cho == 2)
        {
            goto menu;
        }
        goto ss;
    case 2:
    db:
        system("cls");
        gotoxy(25, 2);
        cout << "Bill Editor";
        gotoxy(25, 3);
        cout << "=================\n\n";
        cout << "\n\t\t1.Add Item Details\n\n";
        cout << "\t\t2.Edit Item Details\n\n";
        cout << "\t\t3.Delete Item Details\n\n";
        cout << "\t\t4.Delete All Item\n\n";
        cout << "\t\t5.Back to Main Menu ";
        int apc;
        cin >> apc;
        switch (apc)
        {
        case 1:
            fout.open("itemstore.dat", ios::binary | ios::app);
            amt.add();
            cout << "\n\t\tItem Added Successfully!";
            _getch();
            goto db;

        case 2: {
            vector<int> no;
            vector<string> name;
            cout << "\n\n\t\tList of item:" << endl;
            fin.open("itemstore.dat", ios::binary);
            while (fin.read((char*)&amt, sizeof(amt))) {
                int x = amt.retno();
                string temp = amt.getName();
                no.push_back(x);
                name.push_back(temp);
            }
            if (no.size() != 0)
                amt.getInfo(no, name);
            else
                cout << "\n\t\t\tEmpty list";
            fin.close();
            amt.edit();
            goto db;
        }
        case 3: {
            vector<int> no;
            vector<string> name;
            cout << "\n\n\t\tList of item:" << endl;
            fin.open("itemstore.dat", ios::binary);
            while (fin.read((char*)&amt, sizeof(amt))) {
                int x = amt.retno();
                string temp = amt.getName();
                no.push_back(x);
                name.push_back(temp);
            }
            if (no.size() != 0)
                amt.getInfo(no, name);
            else
                cout << "\n\t\t\tEmpty list";
            fin.close();
            amt.remove();
            goto db;
        }
        case 4:
            amt.removeAll();
            goto db;
        case 5:
            goto menu;
        default:
            cout << "\n\n\t\tWrong Choice!!! Retry";
            _getch();
            goto db;
        }
    case 3: {
        system("cls");
        flag = 0;
        int ino;
        vector<int> no;
        vector<string> names;
        cout << "\n\n\t\tList of item:" << endl;
        fin.open("itemstore.dat", ios::binary);
        while (fin.read((char*)&amt, sizeof(amt))) {
            int x = amt.retno();
            string temp = amt.getName();
            no.push_back(x);
            names.push_back(temp);
        }
        if (no.size() != 0)
            amt.getInfo(no, names);
        else
            cout << "\n\t\t\tEmpty list";
        fin.close();
        cout << "\n\n\t\tEnter Item Number :";
        cin >> ino;
        fin.open("itemstore.dat", ios::binary);
        if (!fin)
        {
            cout << "\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while (fin.read((char*)&amt, sizeof(amt)))
        {
            int x = amt.item::retno();
            if (x == ino)
            {
                amt.pay();
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            cout << "\n\t\tItem does not exist....Please Retry!";
        _getch();
        fin.close();
        goto menu;
    }
    case 4:
    ch:
        system("cls");
        gotoxy(25, 2);
        cout << "Please, Give us your feed back";
        gotoxy(25, 3);
        cout << "===============================\n\n";
        cout << "\n\t\t1.Add Feedback\n\n";
        cout << "\t\t2.Show Feedback\n\n";
        cout << "\n\t\t3. Remove feedback\n\n";
        cout << "\n\t\t4. Back to menu\n\n";
        int apc1;
        cin >> apc1;
        switch (apc1)
        {
        case 1:
            fbk.addFeedback();
            goto ch;
        case 2:
            fbk.showFeedback();
            goto ch;
        case 3:
            fbk.removeFeedback();
            goto ch;
        case 4:
            goto menu;
        default:
            goto ch;
        }
    case 5:
    qw: {
        system("cls");
        gotoxy(25, 3);
        cout << "\n\t\t1.Register account" << endl;
        cout << "\n\t\t2.View list of account" << endl;
        cout << "\n\t\t3.Back to menu" << endl;
        cout << "\n\t\tEnter your choice: ";
        int option;
        cin >> option;
        while (option != 3) {
            system("cls");
            if (option == 1) {
                Customer customer;
                string name, phone;
                gotoxy(25, 3);
                cin.ignore(1);
                cout << "Enter name: ";
                getline(cin, name);
                gotoxy(25, 5);
                cout << "Enter phone: ";
                getline(cin, phone);
                _getch();
                system("cls");
                customer.regis(name, phone);
                _getch();
                goto qw;
            }
            else if (option == 2) {
                ifstream in;
                Customer temp;
                vector<Customer> customer = temp.readFromFile(in);
                temp.showDetail(customer);
                _getch();
                system("cls");
                goto qw;
            }
        }
        goto menu;
    }
    case 6: {
        system("cls");
        gotoxy(25, 3);
        cin.ignore(1);
        cout << "\n\t\tPlease enter name and phone number to check your account is registered" << endl;
        cout << "\n\t\tEnter name: ";
        string name;
        getline(cin, name);
        cout << "\n\t\tEnter phone number: ";
        string num;
        getline(cin, num);
        system("cls");
        ifstream in;
        if (cus.isAccount(in, name, num)) {
            gotoxy(25, 3);
            flag = true;
            cus.setCustomer(name, num);
            cout << "\n\t\tYou can access to this feature";
            _getch();
            system("cls");
        }
        else {
            gotoxy(25, 3);
            cout << "\n\t\tYou must have a account to access to this feature" << endl;
            cout << "\n\t\tPlease choose number 5 to register account";
            _getch();
            goto menu;
        }
    }
    yy:{
        gotoxy(25, 3);
        cout << "\n\t\t1.Lucky bill" << endl;
        cout << "\n\t\t2.Accumulate point" << endl;
        cout << "\n\t\t4.Back to menu" << endl;
        cout << "\n\t\tEnter your choice: ";
        int option;
        cin >> option;
        switch (option) {
        case 1: {
            system("cls");
            fin.open("itemstore.dat", ios::binary);
            total = 0;
            while (fin.read((char*)&amt, sizeof(amt)))
                total += amt.retnetamt();
            fin.close();
            gotoxy(25, 3);
            if (total >= 100000) {
                cout << "\n\t\tYour grand total is: " << total << endl;
                cout << "\n\t\tYou can play a minigame to decrease your bill" << endl;
                cout << "\n\t\tAlthough you can decrease your bill, your accumulate point can change" << endl;
                cout << "\n\t\tDo you want to play?" << endl;
                cout << "\n\t\t1.YES              2.NO" << endl;
                cout << "\n\t\tEnter your choice: ";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    system("cls");
                    cout << "\n\t\t1.Play" << endl;
                    cout << "\n\t\t2.Show help" << endl;
                    int op;
                    cout << "\n\t\tEnter your choice: " << endl;
                    cin >> op;
                    while (op != 1) {
                        system("cls");
                        gotoxy(25, 3);
                        cout << "\n\t\tEach bill has a value" << endl;
                        cout << "\n\t\tIf this value % 10 until we have a number from 1-9" << endl;
                        cout << "\n\t\tThe system will random a number from 1-9" << endl;
                        cout << "\n\t\tIf they have same value, your bill will descrease" << endl;
                        cout << "\n\t\tOtherwise, you lose this game" << endl;
                        _getch();
                        system("cls");
                        cout << "\n\t\t1.Play" << endl;
                        cout << "\n\t\t2.Show help" << endl;
                        cout << "\n\t\tEnter your choice: " << endl;
                        cin >> op;
                    }
                    system("cls");
                    Game game;
                    game.setNum(total);
                    if (game.isSame()) {
                        gotoxy(25, 3);
                        cout << "\n\t\tCongratulation!!!!You win this game!!!" << endl;
                        cout << "\n\t\tAnd your bill will descrease a secret value" << endl;
                        cout << "\n\t\tTo find it, you need to choose a number from 1-10" << endl;
                        cout << "\n\t\tThis system include 10 value: 4(10%), 3(20%), 2(30%) and 1(50%)" << endl;
                        cout << "\n\t\tWith 1-10 we have a different value" << endl;
                        cout << "\n\t\tEnter your choice: ";
                        int op1;
                        cin >> op1;
                        int percent = game.getValue(op1);
                        _getch();
                        system("cls");
                        gotoxy(25, 3);
                        cout << "\n\t\tYour bill decrease " << percent << "%" << endl;
                        cout << "\n\t\tList of value: " << endl;
                        cout << "\n\t\t";
                        game.show();
                        _getch();
                        system("cls");
                        total = total - total * percent / 100.0;
                        gotoxy(30, 3);
                        cout << " BILL DETAILS ";
                        gotoxy(3, 5);
                        cout << "ITEM NO";
                        gotoxy(13, 5);
                        cout << "NAME";
                        gotoxy(23, 5);
                        cout << "PRICE";
                        gotoxy(33, 5);
                        cout << "QUANTITY";
                        gotoxy(44, 5);
                        cout << "TAX %";
                        gotoxy(52, 5);
                        cout << "DISCOUNT %";
                        gotoxy(64, 5);
                        cout << "NET AMOUNT";
                        fin.open("itemstore.dat", ios::binary);
                        while (fin.read((char*)&amt, sizeof(amt)))
                        {
                            amt.report();
                            ff = 0;
                        }
                        gotoxy(17, k);
                        cout << "\n\n\n\t\t\tGrand Total = " << total << " (decrease " << percent << "%)";
                        fin.close();
                        _getch();
                        system("cls");
                        goto yy;
                    }
                    else {
                        cout << "\n\t\tYour number: " << game.getNum() << endl;
                        cout << "\n\t\tYou lose this game!!!Good luck again" << endl;
                        _getch();
                        system("cls");
                        goto yy;
                    }
                }
                else {
                    system("cls");
                    goto yy;
                }
            }
            else {
                cout << "\n\t\tYour grand total is smaller than 100K" << endl;
                cout << "\n\t\tIf you want to play minigame, you need to cost " << 100000 - total << endl;
                _getch();
                system("cls");
                goto yy;
            }
        }
        case 2: {
            system("cls");
            if (flag == false) {
                gotoxy(25, 3);
                cout << "\n\t\tYour point was updated" << endl;
                _getch();
                system("cls");
                goto yy;
            }
            fin.open("itemstore.dat", ios::binary);
            gtotal = 0;
            while (fin.read((char*)&amt, sizeof(amt)))
                gtotal += amt.retnetamt();
            fin.close();
            if (total == 0)
                total = gtotal;
            gotoxy(25, 3);
            if (total < 100000) {
                cout << "\n\t\tYour bill is " << total << endl;
                cout << "\n\t\tTo use this feature, you need bill greater 100K" << endl;
                cout << "\n\t\tYou need " << 100000 - total << " to use" << endl;
            }
            else {
                ifstream in;
                ofstream out;
                float opoint, npoint;
                vector<Customer> res = cus.readFromFile(in);
                for (int i = 0; i < res.size(); i++) {
                    if (cus == res[i]) {
                        opoint = res[i].getPoint();
                        res[i].accumulatePoint(total);
                        npoint = res[i].getPoint();
                        break;
                    }
                }
                cus.writeToFile(out, res);
                cout << "\n\t\tUpdate point successfully" << endl;
                cout << "\n\t\tOld point: " << opoint << endl;
                cout << "\n\t\tNew point: " << npoint << endl;
                flag = false;
            }
            _getch();
            system("cls");
            goto yy;
        }
        case 4:
            goto menu;
        }
    }
    case 7: {
        system("cls");
        ifstream in;
        ofstream out;
        gotoxy(25, 3);
        cout << "Before exiting this system, we need you vote some stars to improve the system" << endl;
        gotoxy(25, 5);
        cout << "You should vote by entering character *" << endl;
        gotoxy(25, 7);
        cout << "Example: 1 star = *, 2 stars = **, 3 stars = ***, 4 stars = ****, 5 stars = *****" << endl;
        gotoxy(25, 9);
        cout << "Enter your choice here (1-5 stars): ";
        string res;
        cin >> res;
        Star star;
        int val = star.convertStar(res);
        system("cls");
        while (val == -1) {
            gotoxy(25, 3);
            cout << "Your choice is invalid" << endl;
            gotoxy(25, 5);
            cout << "Please choose again: ";
            cin >> res;
            val = star.convertStar(res);
            _getch();
            system("cls");
        }
        gotoxy(25, 3);
        cout << "Thanks for your respond" << endl;
        star.writeToFile(out, res, in);
        _getch();
        system("cls");
        gotoxy(25, 3);
        cout << "Do you want to use some feature?" << endl;
        gotoxy(25, 5);
        cout << "1.View average stars" << endl;
        gotoxy(25, 7);
        cout << "2.View history of respond" << endl;
        gotoxy(25, 9);
        cout << "3.Exit" << endl;
        gotoxy(25, 11);
        cout << "Enter your choice here (1-3): ";
        int option;
        cin >> option;
        _getch();
        system("cls");
        while (option != 3) {
            if (option < 1 || option > 3) {
                gotoxy(25, 3);
                cout << "Your choice is invalid" << endl;
                gotoxy(25, 5);
                cout << "Please choose again: " << endl;
                cin >> option;
            }
            else if (option == 1) {
                ifstream in;
                gotoxy(25, 3);
                cout << "The average stars is: " << star.calcAvg() << endl;
            }
            else {
                ifstream in;
                ofstream out;
                star.printScreen();
            }
            _getch();
            system("cls");
            gotoxy(25, 3);
            cout << "Do you want to use some feature?" << endl;
            gotoxy(25, 5);
            cout << "1.View average stars" << endl;
            gotoxy(25, 7);
            cout << "2.View history of respond" << endl;
            gotoxy(25, 9);
            cout << "3.Exit" << endl;
            gotoxy(25, 11);
            cout << "Enter your choice here (1-3): ";
            cin >> option;
            _getch();
            system("cls");
        }
        _getch();
        system("cls");
        gotoxy(20, 20);
        cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin >> yn;
        if ((yn == 'Y') || (yn == 'y'))
        {
            gotoxy(12, 20);
            system("cls");
            cout << "************************** THANKS **************************************";
            _getch();
            exit(0);
        }
        else if ((yn == 'N') || (yn == 'n'))
            goto menu;
        else
        {
            goto menu;
        }
    }
    default:
        cout << "\n\n\t\tWrong Choice....Please Retry!";
        _getch();
        goto menu;
    }
    return 0;
}
