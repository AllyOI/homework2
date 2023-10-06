#ifndef PLAYER_H
#define PLAYER_H
#include "Wheel.h"
class Player {
public:
    Player(int initialMoney = 1000);
    int getMoney() const;
    void setMoney(int newMoney);
    void adjustMoney(int amount);
    Wheel wheel;

private:
    int money;
    int bet;
};
#endif