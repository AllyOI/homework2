#include <iostream>
#include "Wheel.h"
#include "Player.h"

int getBet();
float adjustBet();
void spin(std::string, int); 
int wagerSame(int, Wheel&); 
int wagerHalve(int, Wheel&);
int wagerDouble(int, Wheel&);

int main() {
    char playing = 'y';
    // Initialize the game
    Player player;
    Wheel wheel;

    // Main game loop
    while (playing == 'y') {
        // Get the bet amount from the player
        float bet = getBet();

        //player balls
        int pball = wheel.spin();
        spin("Player", pball);

        // Ask the player whether to double, halve, or keep the same wager
        float coeff = adjustBet();
        bet *= coeff;
        int win;

        if (coeff == 0.5) { //must win twice
            win = wagerHalve(pball, wheel);
        }
        else if (coeff == 2) { //must win once
            win = wagerDouble(pball, wheel);
        }
        else {
            win = wagerSame(pball, wheel);
        }

        // Compare results and adjust money accordingly
        if (win == 1) {
            player.adjustMoney(bet);
        }
        else {
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

void spin(std::string s, int ball) {
    std::cout << s << "'s ball landed on " << ball << std::endl;
}

//Charlie

//returns 1 if player wins
//returns 2 if house wins
int wagerSame(int playerResult, Wheel& w) {
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin();
    std::cout << "House Result: " << houseResult << "\n";
    if (playerResult > houseResult) {
        return 1;
    }
    else {
        return 2;
    }
}

//returns 1 if player wins
//returns 2 if house wins
int wagerDouble(int playerResult, Wheel& w) {
    std::cout << "You chose to double, meaning the house needs to beat you twice now!\nDealer wins on ties\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin();
    std::cout << "House Result: " << houseResult;
    if (playerResult <= houseResult) { //if player loses the first time, try again
        std::cout << "\nAttempt 2...\n";

        int houseResult2 = w.spin();
        std::cout << "House Result: " << houseResult2;
        if (playerResult <= houseResult2) { //if player loses twice
            std::cout << "\n*****LOSER!*****\n";
            return 2;
        }
    }
    std::cout << "\n******WINNER******\n";
    return 1;
}
//returns 1 if player wins
//returns 2 if house wins
int wagerHalve(int playerResult, Wheel& w) {
    std::cout << "You chose to halve, meaning you have to beat the house twice now!\nDealer wins on ties\n";
    std::cout << "Player Result: " << playerResult << "!\nLet's see what the house has\n";
    int houseResult = w.spin();
    int houseResult2 = w.spin();
    std::cout << "House Results: " << houseResult << ", " << houseResult2 << "\n";
    if (playerResult > houseResult && playerResult > houseResult2) {//if player wins twice
        std::cout << "******WINNER******\n";
        return 1;
    }
    else { //if player loses once
        std::cout << "*****LOSER!*****\n";
        return 2;
    }

}