#ifndef _GAME_H_
#define _GAME_H_

#include "Random.h"

class Game {
private:
    vector<int> value;
    int num;
    Random rng;
public:
    void setNum(float total);
    int getNum();
    Game(); //thiet lap mang gia tri
    void show();//show mang gia tri
    bool isSame();//kiem tra 2 gia tri giong nhau khong
    int getValue(int x);
};

#endif // !_GAME_H_

