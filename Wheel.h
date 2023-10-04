#ifndef WHEEL_H
#define WHEEL_H
#include <cstdlib>
#include <ctime>
#include <Windows.h>

class Wheel {
public:
    Wheel(int minVal = 1, int maxVal = 10);
    int spin();
    void changeRange(int newMin, int newMax);

private:
    int minVal;
    int maxVal;
};
#endif