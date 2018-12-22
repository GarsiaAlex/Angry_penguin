#include "Movable.h"

Movable::Movable(string fileName)
{
	gravity.x = 0;
	gravity.y = 100;
}

inline float Movable::getDistance(float x1, float y1, float x2, float y2)
{
	return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

inline float Movable::getDistance(Vector2f& first, Vector2f& second)
{
	return ((first.x - second.x) * (first.x - second.x)) + ((first.y - second.y) * (first.y - second.y));
}

// костыыыыль!
// перегонять FloatRect в координаты вершин
struct {
	FloatRect *r;
	void operator()(FloatRect rect) { r = &rect; }
	Vector2f operator[](int point) {
		switch (point){
		case 0:
			return Vector2f(r->left, r->top);
			break;
		case 1:
			return Vector2f(r->left + r->width, r->top);
			break;
		case 2:
			return Vector2f(r->left + r->width, r->top + r->height);
			break;
		case 3:
			return Vector2f(r->left, r->top + r->height);
			break;
		}
	}
} getCoords;

void Movable::move(Time elapsed)
{
	auto bounds = sprite.getGlobalBounds();
	getCoords(bounds);
	// X movement
	int direction = (speed.x > 0) ? 1 : -1;
	float forward = (direction > 0) ? getCoords[1].x : getCoords[0].x;
	vector<float> xInters;
	for (float i = bounds.top; i <= bounds.top + bounds.height; i += map->getTileSize()) {
		xInters.push_back(i);
	}
	Vertex* closestIntersQuad = nullptr;
	float closestScan = FLT_MAX;
	for (auto it = xInters.begin(); it != xInters.end(); it++) {
		for (float scan = 0; scan < map->getTileSize() * 3; scan += map->getTileSize()) {
			float x = forward + scan * direction;
			float y = *it;
			if (Map::isCollidable(map->getTileNum(x, y)) && (scan < closestScan)) {
				closestIntersQuad = map->getQuad(x, y);
				closestScan = scan;
				break;
			}
		}
	}
	float forwardFrameMovement = speed.x*elapsed.asSeconds();
	float distanceToQuad = direction * min(abs(forward - closestIntersQuad[0].position.x), abs(forward - closestIntersQuad[1].position.x));
	float realMovement = direction * min( abs(forwardFrameMovement), abs(distanceToQuad) );
	point.x += realMovement;
}

/*
void Movable::move(Time elapsed)
{
	Vector2f pointMovement[4];
	Vector2f distanceToMove;
	Vector2f accelSpeed = gravity * elapsed.asSeconds() * elapsed.asSeconds();
	accelSpeed.x = accelSpeed.x / 2;
	accelSpeed.y = accelSpeed.y / 2;
	distanceToMove = speed * elapsed.asSeconds() + accelSpeed;
	auto vpoint = point;
	auto bounds = sprite.getGlobalBounds();
	pointMovement[0] = vpoint + distanceToMove;
	vpoint.x += bounds.width;
	pointMovement[1] = vpoint + distanceToMove;
	vpoint.y += bounds.height;
	pointMovement[2] = vpoint + distanceToMove;
	vpoint.x -= bounds.width;
	pointMovement[3] = vpoint + distanceToMove;

	float min_distance = FLT_MAX, distance;
	bool collision = false;
	Vector2f closestPoints[2];
	for (int i = 0; i < 4; i++) {
		if (Map::isCollidable(map->getTileNum(pointMovement[i].x, pointMovement[i].y))) {
			collision = true;
			Vertex* quad = map->getQuad(pointMovement[i].x, pointMovement[i].y);
			for (int j = 0; j < 4; j++) {
				distance = getDistance(quad[j].position.x, quad[j].position.y, bounds.left, bounds.top);
				if ((min_distance - distance) > 0) {
					min_distance = distance;
					closestPoints[0].x = bounds.left; closestPoints[0].y = bounds.top;
					closestPoints[1].x = quad[j].position.x; closestPoints[1].y = quad[j].position.y;
				}
				distance = getDistance(quad[j].position.x, quad[j].position.y, bounds.left + bounds.width, bounds.top);
				if ((min_distance - distance) > 0) {
					min_distance = distance;
					closestPoints[0].x = bounds.left; closestPoints[0].y = bounds.top;
					closestPoints[1].x = quad[j].position.x; closestPoints[1].y = quad[j].position.y;
				}
				distance = getDistance(quad[j].position.x, quad[j].position.y, bounds.left + bounds.width, bounds.top + bounds.height);
				if ((min_distance - distance) > 0) {
					min_distance = distance;
					closestPoints[0].x = bounds.left; closestPoints[0].y = bounds.top;
					closestPoints[1].x = quad[j].position.x; closestPoints[1].y = quad[j].position.y;
				}
				distance = getDistance(quad[j].position.x, quad[j].position.y, bounds.left, bounds.top + bounds.height);
				if ((min_distance - distance) > 0) {
					min_distance = distance;
					closestPoints[0].x = bounds.left; closestPoints[0].y = bounds.top;
					closestPoints[1].x = quad[j].position.x; closestPoints[1].y = quad[j].position.y;
				}
			}
		}
	}
	if (collision) {
		point += distanceToMove;
	}else {
		Vector2f realMovement(abs(closestPoints[0].x - closestPoints[1].x), abs(closestPoints[0].y - closestPoints[1].y));
		point += realMovement;
	}
}
*/
bool Movable::isPhasing()
{
	auto bounds = sprite.getGlobalBounds();
	bool phasing = false;
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left, bounds.top));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left + bounds.width, bounds.top));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left, bounds.top + bounds.height));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left + bounds.width, bounds.top + bounds.height));
}
