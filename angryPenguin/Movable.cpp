#include "Movable.h"

Movable::Movable(string fileName)
{
	gravity.x = 0;
	gravity.y = 100;
}

void Movable::move(Time elapsed)
{
	Vector2f frameMovement;
	if (standing) {
		frameMovement = point + speed * elapsed.asSeconds();
	}
	else {
		Vector2f accelSpeed = gravity * elapsed.asSeconds() * elapsed.asSeconds();
		accelSpeed.x = accelSpeed.x / 2;
		accelSpeed.y = accelSpeed.y / 2;
		frameMovement = point + speed * elapsed.asSeconds() + accelSpeed;
	}
	bool collision = Map::isCollidable(map->getTileNum(frameMovement.x, frameMovement.y));
	if (collision) {
		map->getQuad(frameMovement.x, frameMovement.y);
		//...//
	}
}

bool Movable::isStanding()
{
	return standing;
}
