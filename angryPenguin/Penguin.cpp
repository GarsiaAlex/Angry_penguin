#include "Penguin.h"

Penguin::Penguin(Map* map, string fileName) : Movable(map, fileName) {
	speed.y = 300;
}

void Penguin::update(Time elapsed, Movable *pl) {
	direction = (this->position.x - pl->position.x) * (-1);
	speed.x += direction * elapsed.asSeconds();

}