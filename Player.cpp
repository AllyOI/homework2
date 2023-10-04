#include "Player.h"

Player::Player(int initialMoney) : money(initialMoney) {}

int Player::getMoney() const {
    return money;
}

void Player::setMoney(int newMoney) {
    money = newMoney;
}

void Player::adjustMoney(int amount) {
    money += amount;
}