#include "Player.h"

Player::Player(string fileName) : Movable (fileName) {
	HP = 150;
	score = 0;
}

int Player::getHP() {
	return HP;
}

int Player::getScore() {
	return score;
}

void Player::addScore(int num) {
	score += num;
}

void Player::addHP(int num) {
	HP += num;
}

void Player::subHP(int num) {
	HP -= num;
}