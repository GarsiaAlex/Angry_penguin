#include "Entity.h"

Entity::Entity(string fileName) {
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
}