#include "Entity.h"
#include "Map.h"

class Movable : public Entity {
public:
	Map *map;
	Vector2f speed;
	Vector2f gravity;
	bool onGround = true;
	int l = 1;

public:
	Movable(Map* map, string fileName);
	void jump();
	virtual void move(Time elapsed);
	bool isPhasing();
};