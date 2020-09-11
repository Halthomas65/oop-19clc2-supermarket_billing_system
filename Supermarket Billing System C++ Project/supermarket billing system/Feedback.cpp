#include "Feedback.h"

void Feedback::addFeedback()
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
    cin.getline(feedback, 100);
    cout << "\n\n\n\tThank your feed back, We will try our best to solve this problem. ";
    fout.write((char*)&fbk, sizeof(fbk));
    fout.close();
    _getch();
}
void Feedback::showFeedback()
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
        cout << "\n\n\tFeedback: " << feedback;
        cout << "\n\t\n--------------------------";
    }
    fin.close();
    _getch();
}
void Feedback::removeFeedback()
{
    char phone[11];
    flag = 0;
    vector<Feedback> tmp_fbk;
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
char* Feedback::returnPhone()
{
    return fbk.phone;
}