#pragma once
#include "Movable.h"

class Walrus : public Movable {
private:
	bool active;
public:
	Walrus(Map* map, string fileName, Vector2f start);
	bool isActive();
	void deactivate();
	int getColType();
};
