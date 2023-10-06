#ifndef WHEEL_H
#define WHEEL_H
#include <cstdlib>
#include <ctime>
#include <Windows.h>

class Wheel {
public:
    Wheel(int minVal = 1, int maxVal = 10);
    virtual int spin();
    void changeRange(int newMin, int newMax);

protected:
    int minVal;
    int maxVal;
};
#endif