#include "Entity.h"
#include "Map.h"

class Movable : public Entity {
private:
	Map *map;
	Vector2f speed;
	Vector2f point;
	Vector2f gravity;
	inline float getDistance(float x1, float y1, float x2, float y2);
	inline float getDistance(Vector2f& first, Vector2f& second);

public:
	Movable(string fileName);
	virtual void move(Time elapsed);
	bool isPhasing();
};