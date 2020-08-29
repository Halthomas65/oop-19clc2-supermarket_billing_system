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
    static void writeToFile(ofstream& out, int year); //ghi file year.txt
    static int readFromFile(ifstream& in); //doc file year.txt
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

class Game {
private:
    vector<int> value;
    int num;
    Random rng;
public:
    void setNum(float total);
    int getNum();
    Game(); //thiet lap mang gia tri
    void show();//show mang gia tri
    bool isSame();//kiem tra 2 gia tri giong nhau khong
    int getValue(int x);
};

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

Time::Time() {//lay time hien tai
    time_t now = time(0);
    tm* t = localtime(&now);
    this->year = 1900 + t->tm_year;
    this->month = 1 + t->tm_mon;
    this->day = t->tm_mday;
    this->hour = t->tm_hour;
    this->min = t->tm_min;
    this->sec = t->tm_sec;
}

int Time::readFromFile(ifstream& in) {
    in.open("year.txt");
    int x;
    in >> x;
    in.close();
    return x;
}

void Time::writeToFile(ofstream& out, int x) {
    out.open("year.txt");
    out << x;
    out.close();
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

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat", ios::binary | ios::out);
    // lay time hien tai, neu ket thuc mot nam thi file customer.txt duoc thiet lap lai
    Time current;
    ifstream in1;
    ofstream out1;
    int year = Time::readFromFile(in1); //lay nam trong file year.txt
    if (year != current.getYear()) { //so sanh nam lay ra voi nam hien tai, neu khac thi thiet lap file txt lai tu dau
        Customer temp;
        vector<Customer> customer = temp.readFromFile(in1);
        for (int i = 0; i < customer.size(); i++) {
            customer[i].setPoint(0);
            customer[i].setMoney(0);
        }
        temp.writeToFile(out1, customer);
        Time::writeToFile(out1, current.getYear());
    }
    //
menu:
    // menu chinh
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
    // hien thi bill
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
    // tinh nang dang ky tai khoan
    qw: {
        system("cls");
        gotoxy(25, 3);
        cout << "\n\t\t1.Register account" << endl; // dang ky tai khoan
        cout << "\n\t\t2.View list of account" << endl; // xem danh sach tai khoan
        cout << "\n\t\t3.Back to menu" << endl; // quay ve menu chinh
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
                customer.regis(name, phone); // ham dang ky
                _getch();
                goto qw;
            }
            else if (option == 2) {
                ifstream in;
                Customer temp;
                vector<Customer> customer = temp.readFromFile(in); //doc file customer.txt
                temp.showDetail(customer, true); //show ra man hinh thong tin
                _getch();
                system("cls");
                goto qw;
            }
        }
        goto menu;
    }
    // tinh nang dich vu khach hang
    case 6: {
        system("cls");
        gotoxy(25, 3);
        cin.ignore(1);
        cout << "\n\t\tPlease enter name and phone number to check your account is registered" << endl;
        cout << "\n\t\tEnter name: "; // nhap ten
        string name;
        getline(cin, name);
        cout << "\n\t\tEnter phone number: "; // nhap sdt
        string num;
        getline(cin, num);
        system("cls");
        ifstream in;
        if (cus.isAccount(in, name, num)) { //kiem tra tai khoan nay co ton tai khong
            gotoxy(25, 3);
            flag = true;
            cus.setCustomer(name, num);
            cout << "\n\t\tYou can access to this feature";
            _getch();
            system("cls");
        }
        else { //neu khong ton tai thi can su dung chuc nang so 5 de dang ky tai khoan
            gotoxy(25, 3);
            cout << "\n\t\tYou must have a account to access to this feature" << endl;
            cout << "\n\t\tPlease choose number 5 to register account";
            _getch();
            goto menu;
        }
    }
    // menu tinh nang dich vu khach hang
    yy:{
        gotoxy(25, 3);
        cout << "\n\t\t1.Lucky bill" << endl; //mini game (neu dung co the se giam gia cua bill nhung anh huong den diem tich luy)
        cout << "\n\t\t2.Accumulate point" << endl; //diem tich luy, tinh nang bat buoc dung neu da co tai khoan
        cout << "\n\t\t3.Use point" << endl; //su dung diem tich luy bang cach mua hang bang diem
        cout << "\n\t\t4.Customer Gratitude" << endl; //tri an khach hang, khach hang co tong tien cao nhat mot nam se duoc tang mot phan qua
        cout << "\n\t\t5.View rank" << endl; //xem muc rank cua khach hang, dua vao diem hoac so tien
        cout << "\n\t\t6.Back to menu" << endl; // quay ve menu chinh
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
            if (total >= 100000) { //neu bill co gia tri lon hon 100K thi tinh nang moi duoc thuc hien
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
                    if (game.isSame()) { //neu chu so cuoi cung dau tien khac 0 cua bill giong voi so he thong random thi win game
                        gotoxy(25, 3);
                        cout << "\n\t\tCongratulation!!!!You win this game!!!" << endl;
                        cout << "\n\t\tAnd your bill will descrease a secret value" << endl;
                        cout << "\n\t\tTo find it, you need to choose a number from 1-10" << endl;
                        cout << "\n\t\tThis system include 10 value: 4(10%), 3(20%), 2(30%) and 1(50%)" << endl;
                        cout << "\n\t\tWith 1-10 we have a different value" << endl;
                        cout << "\n\t\tEnter your choice: ";
                        int op1;
                        cin >> op1; // nhap lua chon so tu 1-10, tuong ung voi moi so la mot gia tri giam khac nhau
                        int percent = game.getValue(op1);
                        _getch();
                        system("cls");
                        gotoxy(25, 3);
                        cout << "\n\t\tYour bill decrease " << percent << "%" << endl;
                        cout << "\n\t\tList of value: " << endl;
                        cout << "\n\t\t";
                        game.show(); // hien gia tri cua tung con so
                        _getch();
                        system("cls");
                        total = total - total * percent / 100.0; // giam gia bill theo gia tri tim duoc
                        // xuat bill
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
                        //
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
        // tinh nang diem tich luy
        case 2: {
            system("cls");
            if (flag == false) { //su dung bien flag de dam bao tai khoan khong tich luy diem 2 lan lien tuc
                gotoxy(25, 3);
                cout << "\n\t\tYour point was updated" << endl;
                _getch();
                system("cls");
                goto yy;
            }
            fin.open("itemstore.dat", ios::binary);
            gtotal = 0; // bien luu gia tri bill khi chua dung minigame
            while (fin.read((char*)&amt, sizeof(amt)))
                gtotal += amt.retnetamt();
            fin.close();
            if (total == 0) // total la bien dung de luu gia tri bill sau khi dung minigame
                total = gtotal;
            if (total < 100000) { // tich luy diem duoc dung khi bill tren 100K
                gotoxy(25, 3);
                cout << "\n\t\tYour bill is " << total << endl;
                cout << "\n\t\tTo use this feature, you need bill greater 100K" << endl;
                cout << "\n\t\tYou need " << 100000 - total << " to use" << endl;
                _getch();
                system("cls");
            }
            gotoxy(25, 3);
            ifstream in;
            ofstream out;
            float opoint, npoint;
            vector<Customer> res = cus.readFromFile(in); //doc file customer.txt
            for (int i = 0; i < res.size(); i++) {
                if (cus == res[i]) {
                    opoint = res[i].getPoint(); //lay diem tich luy hien tai
                    res[i].accumulatePoint(total); //cap nhat diem
                    res[i].updateMoney(total);// cap nhat tien
                    npoint = res[i].getPoint(); //lay diem sau khi cap nhat
                    break;
                }
            }
            cus.writeToFile(out, res);// ghi file customer.txt
            cout << "\n\t\tUpdate point successfully" << endl;
            cout << "\n\t\tOld point: " << opoint << endl;
            cout << "\n\t\tNew point: " << npoint << endl;
            flag = false;
            _getch();
            system("cls");
            goto yy;
        }
        // tinh nang mua hang bang diem
        case 3: {
            system("cls");
        aa: {
            gotoxy(25, 3);
            cout << "\n\t\t1.View list product" << endl; //xem danh sach san pham
            cout << "\n\t\t2.Buy product" << endl;// mua san pham
            cout << "\n\t\t3.Back" << endl;// quay ve menu 
            cout << "\n\t\tEnter your choice: ";
            }
            int op;
            cin >> op;
            switch (op) {
            case 1: {
                system("cls");
                ifstream in;
                vector<Product> pro = Product::readFromFile(in, "product.txt");//doc danh sach trong file product.txt
                _getch();
                system("cls");
                goto aa;
            }
            case 2: {
                system("cls");
                int point;
                ifstream in;
                vector<Customer> res = cus.readFromFile(in); //doc file customer.txt
                for (int i = 0; i < res.size(); i++) {
                    if (cus == res[i]) {
                        point = res[i].getPoint(); //lay diem cua khach hang dang su dung tinh nang nay
                        break;
                    }
                }
                if (point == 0) { 
                    cout << "\n\t\tYour point is 0" << endl;
                    cout << "\n\t\tYou need more point to buy" << endl;
                    _getch();
                    system("cls");
                    goto yy;
                }
                gotoxy(25, 3);
                cout << "\n\t\tYour point: " << point << endl << endl;
                cout << "\n\t\t\t\tLIST PRODUCT YOU CAN BUY WITH THIS POINT" << endl;
                gotoxy(25, 9);
                vector<Product> pro = Product::readFromFile(in, "product.txt");
                Product::showList(pro, point);// hien thi danh sach hang hoa voi so diem ma khach hang nay co the mua
                cout << "\n\t\tEnter position of product you want to buy: ";
                int pos, quantity; //pos la vi tri hang, quantity la so luong hang
                cin >> pos;
                cout << "\n\t\tEnter quantity of this product: ";
                cin >> quantity;
                vector<Product> final; //luu danh sach hang hoa sau khi da mua bang diem
                vector<int> size; //luu so luong moi loai hang hoa
                while (true) {
                    system("cls"); 
                    gotoxy(25, 3);
                    point -= pro[pos - 1].getPoint() * quantity; //tinh diem sau khi mua hang
                    if (point < 0) { //neu diem am thi yeu cau giam bot so luong san pham nay xuong
                        cout << "\n\t\tYour point is not enough" << endl;
                        cout << "\n\t\tYou need to descrease this product's quantity" << endl; 
                        point += pro[pos - 1].getPoint() * quantity; //tra lai diem
                    }
                    else {
                        cout << "\n\t\tBuy product successfully" << endl;
                        if (final.size() == 0) {
                            final.push_back(pro[pos - 1]);
                            size.push_back(quantity);
                        }
                        else { //phan nay dung de kiem tra xem neu hang hoa A duoc mua voi cac so luong khac nhau thi se cong don, tranh trung lap
                            bool flag1 = true;
                            for (int i = 0; i < final.size(); i++) {
                                if (final[i].getName() == pro[pos - 1].getName()) {
                                    size[i] += quantity;
                                    flag1 = false;
                                    break;
                                }
                            }
                            if (flag1 == true) {
                                final.push_back(pro[pos - 1]);
                                size.push_back(quantity);
                            }
                        }
                        //
                        if (point == 0) {
                            cout << "\n\t\tYour point is: 0" << endl;
                            cout << "\n\t\tYou need more point to continue buying" << endl;
                            cout << "\n\t\tThank you for buying" << endl;
                            _getch();
                            break;
                        }
                    }
                    // hoi nguoi dung co muon tiep tuc mua hang khong
                    cout << "\n\t\tDo you want to continue buying?" << endl;
                    cout << "\n\t\t1.YES              2.NO" << endl;
                    int op1;
                    cout << "\n\t\tEnter your choice: ";
                    cin >> op1;
                    if (op1 == 2)
                        break;
                    _getch();
                    system("cls");
                    gotoxy(25, 3);
                    //lap lai menu
                    cout << "\n\t\tYour point: " << point << endl << endl;
                    cout << "\n\t\t\t\tLIST PRODUCT YOU CAN BUY WITH THIS POINT" << endl;
                    gotoxy(25, 9);
                    vector<Product> pro = Product::readFromFile(in, "product.txt");
                    Product::showList(pro, point);
                    cout << "\n\t\tEnter position of product you want to buy: ";
                    cin >> pos;
                    cout << "\n\t\tEnter quantity of this product: ";
                    cin >> quantity;
                    //
                }
                system("cls");
                gotoxy(25, 3);
                cout << "\n\t\t\t\tBILL DETAIL" << endl; //xuat hoa don
                cout << "\n\tITEM NO        NAME        POINT      QUANTITY" << endl;
                for (int i = 0; i < final.size(); i++) {
                    cout << "\n\t" << i + 1 << "              " << final[i].getName() << "        " << final[i].getPoint() << "             " << size[i] << endl;
                }
                for (int i = 0; i < res.size(); i++) {
                    if (cus == res[i]) {
                        res[i].setPoint(point); //cap nhat lai diem
                        break;
                    }
                }
                ofstream out;
                cus.writeToFile(out, res);
                _getch();
                system("cls");
                goto aa;
            }
            case 3: {
                system("cls");
                goto yy;
            }
            }
        }
        //tri an khach hang
        case 4: {
            system("cls");
        bb: {
            gotoxy(25, 3);
            cout << "\n\t\t1.View history" << endl; //xem lich su khach hang mua hang nhieu nhat qua cac nam
            cout << "\n\t\t2.Use feature" << endl; //su dung tinh nang
            cout << "\n\t\t3.Show help" << endl;// xem huong dan
            cout << "\n\t\t4.Back" << endl;
            }
            cout << "\n\t\tEnter your choice: ";
            int op;
            cin >> op;
            switch (op) {
            case 1: {
                system("cls");
                ifstream in;
                vector<BestCustomer> cus = BestCustomer::readFromFile(in); //doc file best customer.txt
                BestCustomer::showDetail(cus);//show ra man hinh thong tin
                _getch();
                system("cls");
                goto bb;
            }
            case 2: {
                system("cls");
                ifstream in;
                ofstream out;
                Customer best = cus.findBestCustomer(in);// tim khach hang tot nhat
                gotoxy(25, 3);
                cout << "\n\t\t\t\tBEST CUSTOMER IN " << current.getYear() << endl;
                best.showDetail();
                cout << "\n\t\tThis customer will give a gift equal to 10% sum money" << endl;
                cout << "\n\t\tThis gift values " << best.getMoney() * 10.0 / 100 << endl;
                // them thong tin khach hang tot nhat vao file best customer.txt
                BestCustomer bcus = bcus.convert(best, current.getYear()); 
                vector<BestCustomer> temp = BestCustomer::readFromFile(in); 
                if (temp[temp.size()-1].getYear() != bcus.getYear())
                    temp.push_back(bcus);
                else {
                    temp.erase(temp.begin() + temp.size() - 1);
                    temp.push_back(bcus);
                }
                BestCustomer::writeToFile(out, temp);
                //
                _getch();
                system("cls");
                goto bb;
            }
            case 3: { // tinh nang duoc dung 1 nam 1 lan, co the thay doi thoi gian he thong de su dung lap tuc
                system("cls");
                gotoxy(25, 3);
                cout << "\n\t\tThis feature use after 1 year" << endl;
                cout << "\n\t\tThe system will find the best customer with highest money" << endl;
                cout << "\n\t\tIf you want to use immediately, you can change time in your system in the end of year" << endl;
                cout << "\n\t\tExample: today is 24/8/2020, you need to change time into 31/12/2020 to use feature" << endl;
                _getch();
                system("cls");
                goto bb;
            }
            case 4: {
                system("cls");
                goto yy;
            }
            }
        }
        // xem rank
        case 5: {
            system("cls");
        cc: {
            gotoxy(25, 3);
            cout << "\n\t\t1.View rank (base on point)" << endl;// xem rank dua theo diem
            cout << "\n\t\t2.View rank (base on money)" << endl;// xem rank dua theo tong tien
            cout << "\n\t\t3.View list (sort descending by point)" << endl;// xem danh sach theo thu tu giam diem
            cout << "\n\t\t4.View list (sort descending by money)" << endl;// xem danh sach theo thu tu giam tien
            cout << "\n\t\t5.Back to menu" << endl;
            }
            cout << "\n\t\tEnter your choice: ";
            int op1;
            cin >> op1;
            switch (op1) {
            case 1: {
                system("cls");
                ifstream in;
                vector<Customer> res = cus.readFromFile(in); //doc file customer.txt
                Customer::sortCustomerPoint(res); //sap xep giam theo diem
                gotoxy(25, 3);
                for (int i = 0; i < res.size(); i++) {
                    if (cus == res[i]) { //duyet vector tim thong tin khach hang
                        cout << "\n\t\tYour point is: " << res[i].getPoint() << endl;
                        cout << "\n\t\tYour position is: " << i + 1 << " in " << res.size() << " customers" << endl;
                        if (i > 2)
                            cout << "\n\t\tTo reach top 3, you need " << res[2].getPoint() - res[i].getPoint() << " point left" << endl;
                        break;
                    }
                }
                _getch();
                system("cls");
                goto cc;
            }
            case 2: {
                system("cls");
                ifstream in;
                vector<Customer> res = cus.readFromFile(in); //doc file customer.txt
                Customer::sortCustomerMoney(res); //sap xep giam theo tien
                gotoxy(25, 3);
                for (int i = 0; i < res.size(); i++) {
                    if (cus == res[i]) { //duyet mang de hien thong tin
                        cout << "\n\t\tYour money is: " << res[i].getMoney() << endl;
                        cout << "\n\t\tYour position is: " << i + 1 << " in " << res.size() << " customers" << endl;
                        cout << "\n\t\tYour rank is: " << res[i].getRank() << endl;
                        if (i > 2)
                            cout << "\n\t\tTo reach top 3, you need " << res[2].getMoney() - res[i].getMoney() << " point left" << endl;
                        break;
                    }
                }
                _getch();
                system("cls");
                goto cc;
            }
            case 3: {
                system("cls");
                ifstream in;
                vector<Customer> res = cus.readFromFile(in);
                Customer::sortCustomerPoint(res);
                cus.showDetail(res, true);
                _getch();
                system("cls");
                goto cc;
            }
            case 4: {
                system("cls");
                ifstream in;
                vector<Customer> res = cus.readFromFile(in);
                Customer::sortCustomerMoney(res);
                cus.showDetail(res, false);
                _getch();
                system("cls");
                goto cc;
            }
            case 5: {
                system("cls");
                goto yy;
            }
            }
        }
        case 6:
            goto menu;
        }
    }
    //truoc khi thoat khoi he thong can vote sao de phat trien he thong
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
        int val = star.convertStar(res); //chuyen doi string sang int
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
        star.writeToFile(out, res, in); //ghi vao file star.txt
        _getch();
        system("cls");
        gotoxy(25, 3);
        cout << "Do you want to use some feature?" << endl;
        gotoxy(25, 5);
        cout << "1.View average stars" << endl; //xem so sao trung binh (max la 5)
        gotoxy(25, 7);
        cout << "2.View history of respond" << endl;// xem lich su vote
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
