#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "mainHeader.h"

class Account {
protected:
    char userName[20];
    char password[8];
    int type;//1: Staff, 2: manager
public:
    static vector<Account> loadAccount();
    int login(vector<Account> vt);
    char* getUserName();
    char* getPasswoed();
    int getType();
    void addAccount();
    void setAccount(string userName, string password, int type);
} acc;

#endif