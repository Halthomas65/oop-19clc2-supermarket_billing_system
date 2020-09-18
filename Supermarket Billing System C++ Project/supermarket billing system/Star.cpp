#include "Star.h"
#include "Tokenizer.h"

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
