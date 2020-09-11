#include "Game.h"

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
