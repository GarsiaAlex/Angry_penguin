#include "Player.h"

Player::Player(Map* map, string fileName) : Movable (map, fileName) {
	HP = 150;
	score = 0;
	colType:: platform;
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

bool Player::collision()
{
	return false;
}

void Player::activateWalrus(list<Walrus*> wlr, Penguin& peng)
{
	for (auto i = wlr.begin(); i != wlr.end(); i++) {
		if (sprite.getGlobalBounds().intersects((*i)->sprite.getGlobalBounds())) {
			// DO SOMETHING
			// (**i) <= морж
			// this <= плеер
			cout << "ACTIVATED" << endl;
			(*i)->deactivate();
			break;
		}
	}
}

void Player::update(Time elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		speed.x = 200;
	}else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		speed.x = -200;
	}
	else {
		speed.x = 0;
	}
}

int Player::getColType() {
	return  colType::platform;
}
