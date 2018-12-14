#include "Entity.h"

class Movable : public Entity {
private:
	Vector2f speed;
	Vector2f point;

public:
	Movable(string fileName);
	virtual void move();
};