#pragma once
#include "Wheel.h"
#include <iostream>
class HardWheel :
    public Wheel
{
private:
    int wins;
    int losses;
public:
    HardWheel();
    int spin(int);
};

