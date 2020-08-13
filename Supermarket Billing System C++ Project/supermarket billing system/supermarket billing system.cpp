#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>
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
//struct time
//{
//    int mm,dd,yy;
//};

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

class Tokenizer
{
public:
    static vector<string> split(string haystack, string needle);
};

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

class item 
{
    int itemno;
    char name[25];
    char* Time;
public:
    char* getTime()
    {
        // tra ve date/time hien tai dua tren system hien tai
        time_t hientai = time(0);

        // chuyen doi hientai thanh dang chuoi
        char* dt = ctime(&hientai);

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
        Time = getTime();
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
};

class amount : public item
{
    float price, qty, tax, gross, dis, netamt;
public:
    void add();
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
        for (int i = 0; i < tokens.size(); i++){
            if (tokens[i].size() == 0)
                break;
            int x = stoi(tokens[i]);
            nums.push_back(x);
        }
        if (count % 2 == 1){
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
    cout << "\t\t4.Exit\n\n";
    cout << "\t\tPlease Enter Required Option: ";
    int ch, ff;
    float gtotal;
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
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    amt.report();
                    gtotal += amt.retnetamt();
                    ff = 0;
                }
                if (ff != 0) gtotal = 0;
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
        cout << "\t\t4.Back to Main Menu ";
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

        case 2:
            int ino;
            flag = 0;
            cout << "\n\n\tEnter Item Number to be Edited :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);
            fout.open("itemstore.dat", ios::binary | ios::app);
            if (!fin)
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r = 0;
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    int x = amt.item::retno();
                    if (x == ino)
                    {
                        flag = 1;
                        fout.seekp(r * sizeof(amt));
                        system("cls");
                        cout << "\n\t\tCurrent Details are\n";
                        amt.show();
                        cout << "\n\n\t\tEnter New Details\n";
                        amt.add();
                        cout << "\n\t\tItem Details editted";
                    }
                }
                r++;
            }
            if (flag == 0)
            {
                cout << "\n\t\tItem No does not exist...Please Retry!";
                _getch();
                goto db;
            }
            fin.close();
            _getch();
            goto db;

        case 3:
            flag = 0;
            cout << "\n\n\tEnter Item Number to be deleted :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            //fstream tmp("temp.dat",ios::binary|ios::out);
            fin.seekg(0);
            while (fin.read((char*)&amt, sizeof(amt)))
            {
                int x = amt.item::retno();
                if (x != ino)
                    tmp.write((char*)&amt, sizeof(amt));
                else
                {
                    flag = 1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat", ios::trunc | ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat", ios::binary | ios::in);
            if (!tmp)
            {
                cout << "Error in File";
                goto db;
            }
            while (tmp.read((char*)&amt, sizeof(amt)))
                fout.write((char*)&amt, sizeof(amt));
            tmp.close();
            fout.close();
            if (flag == 1)
                cout << "\n\t\tItem Succesfully Deleted";
            else if (flag == 0)
                cout << "\n\t\tItem does not Exist! Please Retry";
            _getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout << "\n\n\t\tWrong Choice!!! Retry";
            _getch();
            goto db;
        }
    case 3:
        system("cls");
        flag = 0;
        int ino;
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
    case 4: {
        system("cls");
        ifstream in;
        ofstream out;
        cout << "Before exiting this system, we need you vote some stars to improve the system" << endl;
        cout << "You should vote by entering character *" << endl;
        cout << "Example: 1 star = *, 2 stars = **, 3 stars = ***, 4 stars = ****, 5 stars = *****" << endl;
        cout << "Enter your choice here (1-5 stars): ";
        string res;
        cin >> res;
        Star star;
        int val = star.convertStar(res);
        system("cls");
        while (val == -1) {
            cout << "Your choice is invalid" << endl;
            cout << "Please choose again: ";
            cin >> res;
            val = star.convertStar(res);
            _getch();
            system("cls");
        }
        cout << "Thanks for your respond" << endl;
        star.writeToFile(out, res, in);
        _getch();
        system("cls");
        cout << "Do you want to use some feature?" << endl;
        cout << "1.View average stars" << endl;
        cout << "2.View history of respond" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter your choice here (1-3): ";
        int option;
        cin >> option;
        _getch();
        system("cls");
        while (option != 3) {
            if (option < 1 || option > 3) {
                cout << "Your choice is invalid" << endl;
                cout << "Please choose again: " << endl;
                cin >> option;
            }
            else if (option == 1) {
                ifstream in;
                cout << "The average stars is: " << star.calcAvg() << endl;
            }
            else {
                ifstream in;
                ofstream out;
                star.printScreen();
            }
            _getch();
            system("cls");
            cout << "Do you want to use some feature?" << endl;
            cout << "1.View average stars" << endl;
            cout << "2.View history of respond" << endl;
            cout << "3.Exit" << endl;
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
