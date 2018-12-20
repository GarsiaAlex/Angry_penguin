#include "Entity.h"

class Movable : public Entity {
protected:
	Vector2f speed;
	Vector2f point;

public:
	Movable(string fileName);
	Vector2f getMovePoint(Vector2f spritePoint, Vector2f quadPoint, Vector2f futurePoint);
	virtual void move(Time elapsed);
};