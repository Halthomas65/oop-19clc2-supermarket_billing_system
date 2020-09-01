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
int k=7,r=0,flag=0;
COORD coord = {0, 0};

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

class feedback {
private:
    char phone[11];
    char name[26];
    char Feedback[101];
public:
    void addFeedback()
    {
        cin.ignore();
        fout.open("Storefeedback1.dat", ios::binary|ios::app);
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

            
            if (strcmp(phone,fbk.returnPhone()) != 0)
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
        cout<<"\n\n\tItem No: ";
        cin>>itemno;
        cin.ignore();
        cout<<"\n\n\tName of the item: ";
        cin.getline(name, 25);
        cout << "\n\n\t";
//gets(name);
        char* Time = getTime();
        strcpy(this->Time, Time);
    }
    void show()
    {
        cout<<"\n\tItem No: ";
        cout<<itemno;
        cout<<"\n\n\tName of the item: ";
        cout<<name;
        cout << "\n\n\tTime: " << Time << endl;
    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    int retno()
    {
        return(itemno);

    }

};

class amount: public item
{
    float price,qty,tax,gross,dis,netamt;
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

class account {
protected:
    char userName[20];
    char password[8];
    int type;//1: Staff, 2: manager
public:
    static vector<account> loadAccount()
    {
        vector<account> tmp_acc;
        fin.open("accountstore.txt", ios::binary);

        if (!fin.is_open())
        {
            cout << "\n\nFile Not Found...";
            return tmp_acc;
        }
        while (fin.read((char*)&acc, sizeof(acc)))
        {
            tmp_acc.push_back(acc);
        }
        fin.close();
        return tmp_acc;
    }
    int login(vector<account> vt)
    {
        do {
            
            cout << "\n\n\tEnter user name: ";
            cin.getline(this->userName, 20);
            cout << "\n\n\tEnter password: ";
            cin.getline(this->password, 8);
            bool flag = false;
            for (int i = 0; i < vt.size(); i++)
            {
                if (strcmp(this->userName,vt[i].getUserName())==0 && strcmp(this->password, vt[i].getPasswoed()) == 0)
                {
                    flag = true;
                    this->type = vt[i].getType();
                    break;
                }
            }
            if (flag == true)
            {
                cout << "\n\n\t\tLogin successfully";
                return this->type;
            }
            if (flag == false)
            {
                cout << "\n\n\t\tFailed....";
                cout << "\n\n\t1. Try again.";
                cout << "\n\n\t2. Exit.";
                int op;
                cout << "\n\n\tYour option: ";
                cin >> op;
                cin.ignore();
                if (op == 2)
                    return -1;  
                if (op == 1)
                {
                    system("cls");
                }
            }
        } while (true);
    }
    char* getUserName()
    {
        return this->userName;
    }
    char* getPasswoed()
    {
        return this->password;
    }
    int getType()
    {
        return this->type;
    }
    void addAccount()
    {
        if (this->type != 2)
        {
            cout << "\n\n\tThis task is not yours !!!";
            return;
        }
        else {
            vector<account> tmp_acc = account::loadAccount();
            string userName, password;
            int type;
            cout << "\n\n\tEnter user name: ";
            cin >> userName;
            cout << "\n\n\tEnter password: ";
            cin >> password;
            cout << "\n\n\tEnter type: ";
            cin >> type;
            fout.open("accountstore.txt",ios::binary);
            account acc1;
            acc1.setAccount(userName, password, type);
            tmp_acc.push_back(acc1);
            for (int i = 0; i < tmp_acc.size(); i++)
            {
                fout.write((char*)&tmp_acc[i], sizeof(acc));
            }
            fout.close();
        }
    }
    void setAccount(string userName, string password, int type)
    {
        strcpy(this->userName,userName.c_str());
        strcpy(this->password, password.c_str());
        this->type = type;
    }
} acc;

void amount::add()
{
    item::add();
    cout<<"\n\n\tPrice: ";
    cin>>price;
    cout<<"\n\n\tQuantity: ";
    cin>>qty;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::input()
{
    item::add();
    cout<<"\n\n\tPrice: ";
    cin>>price;
    cout<<"\n\n\tQuantity: ";
    cin>>qty;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;
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
    fin.seekg(0,ios::beg);
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
    gross=price+(price*(tax/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"\n\n\tNet amount: ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(44,k);
    cout<<tax;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        _getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tPRICE                     :"<<price;
    cout<<"\n\n\t\tQUANTITY                  :"<<qty;
    cout<<"\n\t\tTAX PERCENTAGE              :"<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
    cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt;
    cout<<"\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);

    // ----------------------------------------------------------------------dang nhap vao he thong
login:
    system("cls");
    int type;
    gotoxy(25, 2);
    /*acc.setAccount("vodinhphuc", "20092001", 2);
    acc.addAccount();*/
    cout << "Please, login here...";
    type = acc.login(account::loadAccount());
    if (type == 1)
    {
        fstream tmp("temp.dat", ios::binary | ios::out);
        goto menu;
    }
    if (type == 2)
    {
    manager:
        cout << "\n\n\t1. Add Account.";
        cout << "\n\n\t2. Return.";
        cout << "Your Choice: ";
        int opt;
        cin >> opt;
        cin.ignore();
        if (opt == 2)
            goto login;
        acc.addAccount();
        cout << "\n\n\t1. Logout";
        cout << "\n\n\t2. Login with another.";
        cout << "\n\n\t3. Return";
        int op;
        cout << "Your choice: ";
        cin >> op;
        cin.ignore();
        if (op == 1)
            return 0;
        if (op == 2)
            goto login;
        if (op == 3)
            goto manager;
        system("cls");
    }
    else
        return 0;
    //----------------------------------------------------------------------ket thuc dang nhap
    
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"Super Market Billing ";
    gotoxy(25,3);
    cout<<"===========================\n\n";
    cout<<"\n\t\t1.Bill Report\n\n";
    cout<<"\t\t2.Add/Remove/Edit Item\n\n";
    cout<<"\t\t3.Show Item Details\n\n";
    cout << "\t\t4.Feed back\n\n";
    cout<<"\t\t5.Exit\n\n";
    cout<<"\t\tPlease Enter Required Option: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1://--------------------------------------------------------------------Bill Report
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Details";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.All Items\n\n";
        cout<<"\t\t2.Back to Main menu\n\n";
        cout<<"\t\tPlease Enter Required Option: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" BILL DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"TAX %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
            }
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
            _getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:  //-------------------------------------------------- --------------------Add/Edit/Delete
db:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Editor";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout << "\t\t4.Delete All Item\n\n";
        cout<<"\t\t5.Back to Main Menu ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\tItem Added Successfully!";
            _getch();
            goto db;

        case 2:
            amt.edit();
            goto db;

        case 3:
            amt.remove();
            goto db;
        
        case 4:
            amt.removeAll();
            goto db;
        case 5:
            goto menu;
        default:
            cout<<"\n\n\t\tWrong Choice!!! Retry";
            _getch();
            goto db;
        }
    case 3://--------------------------------------------------------------------------- show item detail
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\tEnter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tItem does not exist....Please Retry!";
        _getch();
        fin.close();
        goto menu;
    case 4://-------------------------------------------------------------------------------- feed back
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
    case 5: //----------------------------------------------------------------------------------- Exit
        system("cls");
        gotoxy(20,20);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"************************** THANKS **************************************";
            _getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tWrong Choice....Please Retry!";
        _getch();
        goto menu;
    }
    return 0;
}
