#include "Entity.h"

Entity::Entity(string fileName) {
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = &texture;
	target.draw(sprite, states);
}

void Entity::update(Time elapsed)
{
}
