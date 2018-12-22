#include "Player.h"

Player::Player(string fileName) : Movable (fileName) {
	HP = 150;
	score = 0;
	position.y = 400;
	sprite.setTextureRect(IntRect(30, 30, 30, 30));
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

void Player::update(Time elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		speed.x = 100;
		position.x += speed.x*0.025f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		speed.x = -100;
		position.x += speed.x * 0.025f;
	}
	sprite.setPosition(position);
}
