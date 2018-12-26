#pragma once
#include "Entity.h"
#include "Map.h"

class Movable : public Entity {
protected:
	Map *map;
	Vector2f speed;
	Vector2f gravity;
	bool isOnGround;
	enum colType {water, platform};
	Vector2f Direction;

public:
	Movable(Map* map, string fileName);
	virtual void move(Time elapsed);
	virtual void jump();
	bool isPhasing();
	virtual int getColType();
};