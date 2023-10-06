#include "HardWheel.h"

HardWheel::HardWheel() : Wheel() {
	wins = 0;
	losses = 0;
}

int HardWheel::spin(int pball) {
	//will be called instead of the other spin in Charlie's methods... separate from player's wheel
	int hball = Wheel::spin();
	
	//updates wins and losses in instance
	if (hball >= pball) {
		wins++;
		//if wins twice in a row, decrease range
		if (wins == 2) {
			//std::cout << "House wheel range decreases..." << '\n';
			changeRange(minVal, maxVal / 2);
			wins = 0;
		}
	}
	else {
		losses++;
		//if loses, increase range
		//std::cout << "House wheel range increases..." << '\n';
		changeRange(minVal, maxVal * 2);
	}
	return hball;
}