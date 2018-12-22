#include "Entity.h"
#include "Map.h"

class Movable : public Entity {
public:
	Map *map;
	Vector2f speed;
	Vector2f gravity;

public:
	Movable(Map* map, string fileName);
	virtual void move(Time elapsed);
	bool isPhasing();
};