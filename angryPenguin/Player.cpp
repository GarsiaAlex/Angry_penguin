#include "Player.h"

Player::Player(string fileName) : Movable (fileName) {
	HP = 150;
	score = 0;
}