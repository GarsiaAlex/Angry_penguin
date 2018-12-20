#include "Movable.h"

Movable::Movable(string fileName) : Entity (fileName) {

}

Vector2f Movable::getMovePoint(Vector2f spritePoint, Vector2f quadPoint, Vector2f futurePoint)
{
	return Vector2f();
}

void Movable::move(Time elapsed)
{
}
