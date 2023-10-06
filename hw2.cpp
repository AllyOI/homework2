#include <iostream>
#include "HardWheel.h"
#include "Player.h"

bool getMode(); //True for normal mode, false for hard mode
int getBet();
float adjustBet();
int spin(std::string, Wheel&); 
int wagerSame(int, Wheel&); 
int wagerHalve(int, Wheel&);
int wagerDouble(int, Wheel&);
int wagerSameH(int, HardWheel&);
int wagerHalveH(int, HardWheel&);
int wagerDoubleH(int, HardWheel&);
static bool hardMode;

int main() {
    int wins = 0;
    int losses = 0;
    char playing = 'y';
    // Initialize the game
    Player player;
    HardWheel *houseWheel;

    hardMode = getMode();
    if (hardMode) {
        houseWheel = new HardWheel();
    }
    else {
        houseWheel = new HardWheel();
    }

    // Main game loop
    while (playing == 'y') {
        // Get the bet amount from the player
        float bet = getBet();

        //player balls
        int pball = spin("Player", player.wheel);

        // Ask the player whether to double, halve, or keep the same wager
        float coeff = adjustBet();
        bet *= coeff;
        int win;
        if (hardMode) {
            if (coeff == 0.5) { //must win twice
                win = wagerHalveH(pball, *houseWheel);
            }
            else if (coeff == 2) { //must win once
                win = wagerDoubleH(pball, *houseWheel);
            }
            else {
                win = wagerSameH(pball, *houseWheel);
            }
        }
        else {
            if (coeff == 0.5) { //must win twice
                win = wagerHalve(pball, *houseWheel);
            }
            else if (coeff == 2) { //must win once
                win = wagerDouble(pball, *houseWheel);
            }
            else {
                win = wagerSame(pball, *houseWheel);
            }
        }

        // Compare results and adjust money accordingly
        if (win == 1) {
            player.adjustMoney(bet);
        }
        else if (win == 2) {
            player.adjustMoney(-bet);
        }
        // Print player's current money
        std::cout << "Player's current money: " << player.getMoney() << std::endl;

        //prompt for continue
        if (player.getMoney() <= 0) {
            playing = 'n';
            std::cout << "Game over. You ran out of money!" << std::endl;
        }
        else {
            std::cout << "Continue?(y/n)\n";
            std::cin >> playing;
        }
    }
    return 0;
}

int getBet() {
    int bet = 0;
    do {
        std::cout << "Enter your minimum bet (between 6 and 20): \n";
        std::cin >> bet;
    } while (bet < 6 || bet > 20);
    return bet;
}

bool getMode() {
    int mode;
    do {
        std::cout << "Enter 1 for normal mode and 2 for hard mode.\n";
        std::cin >> mode;
    } while (!(mode == 1 || mode == 2));
    return mode ==2;
}

float adjustBet() {
    float coeff = 0;
    std::string op = "";
    std::cout << "Do you want to DOUBLE, HALVE, or KEEP the same wager? \n";

    while ((coeff != 1) && (coeff != 0.5) && (coeff != 2)) {
        std::cout << "Enter DOUBLE, HALVE, or KEEP.\n";
        std::cin >> op;
        if (op == "DOUBLE")
            coeff = 2;
        else if (op == "HALVE")
            coeff = 0.5;
        else if (op == "KEEP")
            coeff = 1;
    }
    return coeff;
}

int spin(std::string s, Wheel& w) {
    int ball = w.spin();
    std::cout << s << "'s ball landed on " << ball << std::endl;
    return ball;
}

//Charlie

//returns 1 if player wins
//returns 2 if house wins
int wagerSame(int playerResult, Wheel& w) {
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin();
    std::cout << "House Result: " << houseResult << "\n";
    if (playerResult > houseResult) {
        std::cout << "\n*****WINNER*****\n";
        return 1;
    }
    else {
        std::cout << "\n*****LOSER!*****\n";
        return 2;
    }
}

//returns 1 if player wins
//returns 2 if house wins
int wagerDouble(int playerResult, Wheel& w) {
    std::cout << "You chose to double, meaning the house needs to beat you one of two times! (Dealer wins on ties)\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin();
    std::cout << "House Result: " << houseResult;
    if (playerResult > houseResult) { //if player wins the first time, house tries again
        std::cout << "\nAttempt 2...\n";

        int houseResult2 = w.spin();
        std::cout << "House Result: " << houseResult2;
        if (playerResult > houseResult2) { //if house loses twice
            std::cout << "\n*****LOSER!*****\n";
            return 2;
        }
    }
    std::cout << "\n*****WINNER*****\n";
    return 1;
}
//returns 1 if player wins
//returns 2 if house wins
//returns 3 if nobody wins
int wagerHalve(int playerResult, Wheel& w) {
    std::cout << "You chose to halve, meaning you have to beat the house twice now!\nBut if you each win one then nothing changes\nDealer wins on ties\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin();
    int houseResult2 = w.spin();
    std::cout << "House Results: " << houseResult << ", " << houseResult2 << "\n";
    if (playerResult > houseResult && playerResult > houseResult2) { // if player wins both
        std::cout << "*****WINNER*****\n";
        return 1;
    }
    else if (playerResult > houseResult || playerResult > houseResult2) { // if player wins one
        return 3;
    }
    else { // if player loses both
        std::cout << "*****LOSER!*****\n";
        return 2;
    }

}

int wagerSameH(int playerResult, HardWheel& w) {
    //std::cout << "HARDWHEEL VERSION\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin(playerResult);
    std::cout << "House Result: " << houseResult << "\n";
    if (playerResult > houseResult) {
        std::cout << "\n*****WINNER*****\n";
        return 1;
    }
    else {
        std::cout << "\n*****LOSER!*****\n";
        return 2;
    }
}

//returns 1 if player wins
//returns 2 if house wins
int wagerDoubleH(int playerResult, HardWheel& w) {
    //std::cout << "HARDWHEEL VERSION\n";
    std::cout << "You chose to double, meaning the house needs to beat you one of two times! (Dealer wins on ties)\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin(playerResult);
    std::cout << "House Result: " << houseResult;
    if (playerResult > houseResult) { //if player wins the first time, house tries again
        std::cout << "\nAttempt 2...\n";

        int houseResult2 = w.spin(playerResult);
        std::cout << "House Result: " << houseResult2;
        if (playerResult > houseResult2) { //if house loses twice
            std::cout << "\n*****LOSER!*****\n";
            return 2;
        }
    }
    std::cout << "\n*****WINNER*****\n";
    return 1;
}

//returns 1 if player wins
//returns 2 if house wins
//returns 3 if nobody wins
int wagerHalveH(int playerResult, HardWheel& w) {
    //std::cout << "HARDWHEEL VERSION\n";
    std::cout << "You chose to halve, meaning you have to beat the house twice now!\nBut if you each win one then nothing changes\nDealer wins on ties\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin(playerResult);
    int houseResult2 = w.spin(playerResult);
    std::cout << "House Results: " << houseResult << ", " << houseResult2 << "\n";
    if (playerResult > houseResult && playerResult > houseResult2) { // if player wins both
        std::cout << "*****WINNER*****\n";
        return 1;
    }
    else if (playerResult > houseResult || playerResult > houseResult2) { // if player wins one
        return 3;
    }
    else { // if player loses both
        std::cout << "*****LOSER!*****\n";
        return 2;
    }
}