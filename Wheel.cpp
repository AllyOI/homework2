#include "Wheel.h"

//Eder

Wheel::Wheel(int minVal, int maxVal) : minVal(minVal), maxVal(maxVal) {

}

int Wheel::spin() {
    //initialize the random number generator with the current time as the seed. this will ensure new numbers are generated each time this method is called
    srand(time(0));
    //Program goes too fast, not engaging to the user, this will delay it a bit
    Sleep(1000);
    //generate random number between min and max values set on this class
    int random = rand() % (maxVal + 1 - minVal) + minVal;
    return random;

}


void Wheel::changeRange(int min, int max) {
    this->minVal = min;
    this->maxVal = max;
}