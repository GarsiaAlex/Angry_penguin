#include "Walrus.h"

Walrus::Walrus(Map * map, string fileName, Vector2f start) : Movable(map, fileName)
{
	active = true;
	position = start;
}

bool Walrus::isActive()
{
	return active;
}

void Walrus::deactivate()
{
	active = false;
}

int Walrus::getColType()
{
	return colType::platform;
}
