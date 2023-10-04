#ifndef HOUSE_H
#define HOUSE_H
#include "Wheel.h"
#include "Player.h"
class House {
public:
    House();
    int wagerSame(Player&); //if player wins, return true.
    int wagerHalve(Player&);
    int wagerDouble(Player&);
    Wheel& getWheel();
    int getGameType();
private:
    Wheel wheel;
    //    int gameType; //This will track if a double, half or other is used. 

};
#endif