#include "Entity.h"
#include "Map.h"

class Movable : public Entity {
private:
	Map *map;
	Vector2f speed;
	Vector2f point;
	Vector2f gravity;
	bool standing;

public:
	Movable(string fileName);
	virtual void move(Time elapsed);
	bool isStanding();
};