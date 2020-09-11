#include "Item.h"

char* Item::getTime()
{
    // tra ve date/time hien tai dua tren system hien tai
    time_t hientai = time(0);

    // chuyen doi hientai thanh dang chuoi
    char* dt = ctime(&hientai);


    strcpy(Time, dt);
    cout << "Time of Bill: " << dt << endl;

    return dt;
}
void Item::add()
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
void Item::show()
{
    cout << "\n\tItem No: ";
    cout << itemno;
    cout << "\n\n\tName of the item: ";
    cout << name;
    cout << "\n\n\tTime: " << Time << endl;
}
void Item::report()
{
    gotoxy(3, k);
    cout << itemno;
    gotoxy(13, k);
    puts(name);
}
int Item::retno()
{
    return(itemno);
}
string Item::getName() {
    string temp(name);
    return temp;
}
void Item::getInfo(vector<int> no, vector<string> name) {
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