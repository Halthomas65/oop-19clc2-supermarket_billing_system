#include "Account.h"
#include "Amount.h"         //included Item.h
#include "BestCustomer.h"   //included Customer.h
#include "Feedback.h"
#include "Game.h"           //included Random.h
#include "Money.h"          //included Time.h
#include "Product.h"
#include "Star.h"
#include "Tokenizer.h"

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
  
    cout<<setprecision(2);
    /*cout << setprecision(2);*/
    fstream tmp("temp.dat", ios::binary | ios::out);
    // lay time hien tai, neu ket thuc mot nam thi file customer.txt duoc thiet lap lai
    Time current;

    // Thực hiện chặn đăng nhập trong thời gian bảo trì hệ thống
    if (current.getHour() >= 21 && current.getMin() <= 15)
    {
        cout << "System is in maintenance, please be back after 21:15 p.m.\n";
        return 0;
    }

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
    // ----------------------------------------------------------------------dang nhap vao he thong
login:
    system("cls");
    int type;
    gotoxy(25, 2);
    /*acc.setAccount("vodinhphuc", "20092001", 2);
    acc.addAccount();*/
    cout << "Please, login here...";
    type = acc.login(Account::loadAccount());
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
    cout << "\t\t7.Statistic\n\n";
    cout << "\t\t8.Exit\n\n";
    cout << "\t\tPlease Enter Required Option: ";
    int ch, ff;
    float gtotal = 0, total = 0;
    bool flag = true;
    Customer cus;
    cin >> ch;
    switch (ch)
    {

    case 1://--------------------------------------------------------------------Bill Report
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
            ifstream in;
            ofstream out;
            Money money;
            money.writeToFile(out, current.getYear(), gtotal, in, current);

            _getch();
            fin.close();
        }
        if (cho == 2)
        {
            goto menu;
        }
        goto ss;

    case 2:  //-------------------------------------------------- --------------------Add/Edit/Delete
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

    case 3://--------------------------------------------------------------------------- show item detail
        {
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
            int x = amt.Item::retno();
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
    case 4://-------------------------------------------------------------------------------- feed back
    ch:
        system("cls");
        gotoxy(25, 2);
        cout << "Please, Give us your feed back";
        gotoxy(25, 3);
        cout << "===============================\n\n";
        cout << "\n\t\t1.Add feedback\n\n";
        cout << "\t\t2.Show feedback\n\n";
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
        cout << "\n\t\t2.Accumulate point (required)" << endl; //diem tich luy, tinh nang bat buoc dung neu da co tai khoan
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
            ifstream in;
            ofstream out;
            Money money;
            money.writeToFile(out, current.getYear(), total, in, current);
            if (total < 100000) { // tich luy diem duoc dung khi bill tren 100K
                gotoxy(25, 3);
                cout << "\n\t\tYour bill is " << total << endl;
                cout << "\n\t\tTo use this feature, you need bill greater 100K" << endl;
                cout << "\n\t\tYou need " << 100000 - total << " to use" << endl;
                _getch();
                system("cls");
            }
            gotoxy(25, 3);
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
    case 7: 
    // tinh nang thong ke
    abc: {
        system("cls");
        gotoxy(25, 3);
        cout << "\n\t\t1.Calculate income in one day, one month, one year" << endl; //tinh thu nhap sieu thi trong 1 ngay, 1 tuan hay 1 nam
        cout << "\n\t\t2.Count number of custumers in one day, one month, one year" << endl; //tinh so luot mua hang trong 1 ngay, 1 tuan hay 1 nam
        cout << "\n\t\t3.Compare income between two days, two months, two years" << endl; //so sanh thu nhap giua hai ngay, hai thang hay hai nam
        cout << "\n\t\t4.Back to menu" << endl;
        cout << "\n\t\tEnter your choice: ";
        int op;
        cin >> op;
        switch (op) {
        case 1: {
        c1: {
            system("cls");
            gotoxy(25, 3);
            cout << "\n\t\t1.One day" << endl;
            cout << "\n\t\t2.One month" << endl;
            cout << "\n\t\t3.One year" << endl;
            cout << "\n\t\t4.Back" << endl;
            }
            cout << "\n\t\tEnter your choice: ";
            int op1;
            cin >> op1;
            switch (op1) {
            case 1: {
                system("cls");
                gotoxy(25, 3);
                int day, month, year;
                cout << "\n\t\tEnter day: ";
                cin >> day;
                cout << "\n\t\tEnter month: ";
                cin >> month;
                cout << "\n\t\tEnter year: ";
                cin >> year;
                Time temp;
                temp.setDay(day);
                temp.setMonth(month);
                temp.setYear(year);
                Money money;
                ifstream in;
                money.readFromFile(in, year);
                cout << "\n\t\tIncome in " << day << "/" << month << "/" << year << ": " << money.calcOneDay(temp) << endl;
                _getch();
                system("cls");
                goto c1;
            }
            case 2: {
                system("cls");
                gotoxy(25, 3);
                int month, year;
                cout << "\n\t\tEnter month: ";
                cin >> month;
                cout << "\n\t\tEnter year: ";
                cin >> year;
                Time temp;
                temp.setMonth(month);
                temp.setYear(year);
                Money money;
                ifstream in;
                money.readFromFile(in, year);
                cout << "\n\t\tIncome in " << month << "/" << year << ": " << money.calcOneMonth(temp) << endl;
                _getch();
                system("cls");
                goto c1;
            }
            case 3: {
                system("cls");
                gotoxy(25, 3);
                int year;
                cout << "\n\t\tEnter year: ";
                cin >> year;
                Time temp;
                temp.setYear(year);
                Money money;
                ifstream in;
                money.readFromFile(in, year);
                cout << "\n\t\tIncome in " << year << ": " << money.calcOneYear(temp) << endl;
                _getch();
                system("cls");
                goto c1;
            }
            case 4: {
                system("cls");
                goto abc;
            }
            }
        }
        case 2: {
        c2: {
            system("cls");
            gotoxy(25, 3);
            cout << "\n\t\t1.One day" << endl;
            cout << "\n\t\t2.One month" << endl;
            cout << "\n\t\t3.One year" << endl;
            cout << "\n\t\t4.Back" << endl;
            }
            cout << "\n\t\tEnter your choice: ";
            int op1;
            cin >> op1;
            switch (op1) {
            case 1: {
                system("cls");
                gotoxy(25, 3);
                int day, month, year;
                cout << "\n\t\tEnter day: ";
                cin >> day;
                cout << "\n\t\tEnter month: ";
                cin >> month;
                cout << "\n\t\tEnter year: ";
                cin >> year;
                Time temp;
                temp.setDay(day);
                temp.setMonth(month);
                temp.setYear(year);
                ifstream in;
                Money money;
                money.readFromFile(in, year);
                cout << "\n\t\tNumber of customers in " << day << "/" << month << "/" << year << ": " << money.countOneDay(temp) << endl;
                _getch();
                system("cls");
                goto c2;
            }
            case 2: {
                system("cls");
                gotoxy(25, 3);
                int month, year;
                cout << "\n\t\tEnter month: ";
                cin >> month;
                cout << "\n\t\tEnter year: ";
                cin >> year;
                Time temp;
                temp.setMonth(month);
                temp.setYear(year);
                ifstream in;
                Money money;
                money.readFromFile(in, year);
                cout << "\n\t\tNumber of customers in " << month << "/" << year << ": " << money.countOneMonth(temp) << endl;
                _getch();
                system("cls");
                goto c2;
            }
            case 3: {
                system("cls");
                gotoxy(25, 3);
                int year;
                cout << "\n\t\tEnter year: ";
                cin >> year;
                Time temp;
                temp.setYear(year);
                ifstream in;
                Money money;
                money.readFromFile(in, year);
                cout << "\n\t\tNumber of customers in " << year << ": " << money.countOneYear(temp) << endl;
                _getch();
                system("cls");
                goto c2;
            }
            case 4: {
                system("cls");
                goto abc;
            }
            }
        }
        case 3: {
        c3: {
            system("cls");
            gotoxy(25, 3);
            cout << "\n\t\t1.Compare between two days" << endl;
            cout << "\n\t\t2.Compare between two months" << endl;
            cout << "\n\t\t3.Compare between two years" << endl;
            cout << "\n\t\t4.Back" << endl;
            }
            cout << "\n\t\tEnter your choice: ";
            int op1;
            cin >> op1;
            switch (op1) {
            case 1: {
                system("cls");
                gotoxy(25, 3);
                cout << "\n\t\tEnter the first time with this format XX/XX/XXXX: ";
                string temp;
                cin.ignore(1);
                getline(cin, temp);
                Time t1, t2;
                vector<string> tokens = Tokenizer::split(temp, "/");
                t1.setDay(stoi(tokens[0]));
                t1.setMonth(stoi(tokens[1]));
                t1.setYear(stoi(tokens[2]));
                cout << "\n\t\tEnter the second time with this format XX/XX/XXXX: ";
                getline(cin, temp);
                tokens.clear();
                tokens = Tokenizer::split(temp, "/");
                t2.setDay(stoi(tokens[0]));
                t2.setMonth(stoi(tokens[1]));
                t2.setYear(stoi(tokens[2]));
                Money m1, m2;
                ifstream in;
                m1.readFromFile(in, t1.getYear());
                m2.readFromFile(in, t2.getYear());
                float sum1 = m1.calcOneDay(t1);
                float sum2 = m2.calcOneDay(t2);
                if (sum1 < sum2)
                    cout << "\n\t\tThe income in " << t2.getDay() << "/" << t2.getMonth() << "/" << t2.getYear() << " larger than " << t1.getDay() << "/" << t1.getMonth() << "/" << t1.getYear() << ": " << sum2 - sum1 << endl;
                else if (sum1 > sum2)
                    cout << "\n\t\tThe income in " << t1.getDay() << "/" << t1.getMonth() << "/" << t1.getYear() << " larger than " << t2.getDay() << "/" << t2.getMonth() << "/" << t2.getYear() << ": " << sum1 - sum2 << endl;
                else
                    cout << "\n\t\tThe income in " << t1.getDay() << "/" << t1.getMonth() << "/" << t1.getYear() << " equal to " << t2.getDay() << "/" << t2.getMonth() << "/" << t2.getYear() << endl;
                _getch();
                system("cls");
                goto c3;
            }
            case 2: {
                system("cls");
                gotoxy(25, 3);
                cout << "\n\t\tEnter the first time with this format XX/XXXX: ";
                string temp;
                cin.ignore(1);
                getline(cin, temp);
                Time t1, t2;
                vector<string> tokens = Tokenizer::split(temp, "/");
                t1.setMonth(stoi(tokens[0]));
                t1.setYear(stoi(tokens[1]));
                cout << "\n\t\tEnter the second time with this format XX/XXXX: ";
                getline(cin, temp);
                tokens.clear();
                tokens = Tokenizer::split(temp, "/");
                t2.setMonth(stoi(tokens[0]));
                t2.setYear(stoi(tokens[1]));
                Money m1, m2;
                ifstream in;
                m1.readFromFile(in, t1.getYear());
                m2.readFromFile(in, t2.getYear());
                float sum1 = m1.calcOneMonth(t1);
                float sum2 = m2.calcOneMonth(t2);
                if (sum1 < sum2)
                    cout << "\n\t\tThe income in " << t2.getMonth() << "/" << t2.getYear() << " larger than " << t1.getMonth() << "/" << t1.getYear() << ": " << sum2 - sum1 << endl;
                else if (sum1 > sum2)
                    cout << "\n\t\tThe income in " << t1.getMonth() << "/" << t1.getYear() << " larger than " << t2.getMonth() << "/" << t2.getYear() << ": " << sum1 - sum2 << endl;
                else
                    cout << "\n\t\tThe income in " << t1.getMonth() << "/" << t1.getYear() << " equal to " << t2.getMonth() << "/" << t2.getYear() << endl;
                _getch();
                system("cls");
                goto c3;
            }
            case 3: {
                system("cls");
                gotoxy(25, 3);
                cout << "\n\t\tEnter the first year: ";
                int year;
                cin >> year;
                Time t1, t2;
                t1.setYear(year);
                cout << "\n\t\tEnter the second year: ";
                cin >> year;
                t2.setYear(year);
                Money m1, m2;
                ifstream in;
                m1.readFromFile(in, t1.getYear());
                m2.readFromFile(in, t2.getYear());
                float sum1 = m1.calcOneYear(t1);
                float sum2 = m2.calcOneYear(t2);
                if (sum1 < sum2)
                    cout << "\n\t\tThe income in " << t2.getYear() << " larger than " << t1.getYear() << ": " << sum2 - sum1 << endl;
                else if (sum1 > sum2)
                    cout << "\n\t\tThe income in " << t1.getYear() << " larger than " << t2.getYear() << ": " << sum1 - sum2 << endl;
                else
                    cout << "\n\t\tThe income in " << t1.getYear() << " equal to " << t2.getYear() << endl;
                _getch();
                system("cls");
                goto c3;
            }
            case 4: {
                system("cls");
                goto abc;
            }
            }
        }
        case 4: {
            system("cls");
            goto menu;
        }
        }
    }
    //truoc khi thoat khoi he thong can vote sao de phat trien he thong
    case 8: {
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
