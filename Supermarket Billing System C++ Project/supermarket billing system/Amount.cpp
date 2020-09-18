#include "Amount.h"

void Amount::add()
{
    Item::add();
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

void Amount::input()
{
    Item::add();
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

void Amount::edit()
{
    int ino;
    flag = 0;
    vector<Amount> tmp_amt;
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

        int x = amt.Item::retno();
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

void Amount::remove()
{
    int ino;
    flag = 0;
    vector<Amount> tmp_amt;
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

        int x = amt.Item::retno();
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

void Amount::removeAll()
{
    fout.open("itemstore.dat", ios::binary);
    fout.close();
}

void Amount::calculate()
{
    gross = price + (price * (tax / 100));
    netamt = qty * (gross - (gross * (dis / 100)));
}

void Amount::show()
{
    fin.open("itemstore.dat", ios::binary);
    fin.read((char*)&amt, sizeof(amt));
    Item::show();
    cout << "\n\n\tNet amount: ";
    cout << netamt;
    fin.close();
}

void Amount::report()
{
    Item::report();
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

void Amount::pay()
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
