#include "Movable.h"

Movable::Movable(string fileName)
{
	gravity.x = 0;
	gravity.y = 100;
}

void Movable::move(Time elapsed)
{
	Vector2f frameMovement;
	Vector2f accelSpeed = gravity * elapsed.asSeconds() * elapsed.asSeconds();
	accelSpeed.x = accelSpeed.x / 2;
	accelSpeed.y = accelSpeed.y / 2;
	frameMovement = point + speed * elapsed.asSeconds() + accelSpeed;

	bool collision = Map::isCollidable(map->getTileNum(frameMovement.x, frameMovement.y));
	if (collision) {
		Vertex* quad = map->getQuad(frameMovement.x, frameMovement.y);
		auto bounds = sprite.getGlobalBounds();
		//...//
	}
}

bool Movable::isPhasing()
{
	auto bounds = sprite.getGlobalBounds();
	bool phasing = false;
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left, bounds.top));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left + bounds.width, bounds.top));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left, bounds.top + bounds.height));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left + bounds.width, bounds.top + bounds.height));
}
