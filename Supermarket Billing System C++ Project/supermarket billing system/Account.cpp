#include "Account.h"

vector<Account> Account::loadAccount()
{
    vector<Account> tmp_acc;
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
int Account::login(vector<Account> vt)
{
    do {

        cout << "\n\n\tEnter user name: ";
        cin.getline(this->userName, 20);
        cout << "\n\n\tEnter password: ";
        cin.getline(this->password, 8);
        bool flag = false;
        for (int i = 0; i < vt.size(); i++)
        {
            if (strcmp(this->userName, vt[i].getUserName()) == 0 && strcmp(this->password, vt[i].getPasswoed()) == 0)
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
char* Account::getUserName()
{
    return this->userName;
}
char* Account::getPasswoed()
{
    return this->password;
}
int Account::getType()
{
    return this->type;
}
void Account::addAccount()
{
    if (this->type != 2)
    {
        cout << "\n\n\tThis task is not yours !!!";
        return;
    }
    else {
        vector<Account> tmp_acc = Account::loadAccount();
        string userName, password;
        int type;
        cout << "\n\n\tEnter user name: ";
        cin >> userName;
        cout << "\n\n\tEnter password: ";
        cin >> password;
        cout << "\n\n\tEnter type: ";
        cin >> type;
        fout.open("accountstore.txt", ios::binary);
        Account acc1;
        acc1.setAccount(userName, password, type);
        tmp_acc.push_back(acc1);
        for (int i = 0; i < tmp_acc.size(); i++)
        {
            fout.write((char*)&tmp_acc[i], sizeof(acc));
        }
        fout.close();
    }
}
void Account::setAccount(string userName, string password, int type)
{
    strcpy(this->userName, userName.c_str());
    strcpy(this->password, password.c_str());
    this->type = type;
}