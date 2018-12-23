#include "Movable.h"

Movable::Movable(Map* map, string fileName) : Entity(fileName)
{
	this->map = map;
	gravity.x = 0;
	gravity.y = 600;
}

void Movable::move(Time elapsed)
{
	auto bounds = sprite.getGlobalBounds();
	/* ========================================================================================== */
	// X movement
	// ВСЕ КООРДИНАТЫ В БЛОКЕ - ДЛЯ ОСИ Х
	/* ========================================================================================== */
	int direction = (speed.x >= 0) ? 1 : -1; // направление движения по оси
	float forward = (direction > 0) ? bounds.left + bounds.width : bounds.left; // соответствующая направлению координата (вперед - передняя грань объекта итд)
	
	// координаты линий, следуя которым мы ищем столкновения
	/*
	000----------   <= линия
	000
	000----------   <= линия
	
	*/
	vector<float> xInters;
	for (float i = bounds.top + 1; i < bounds.top + bounds.height; i += map->getTileSize() / 2) {
		xInters.push_back(i);
	}
	xInters.push_back(bounds.top + bounds.height - 1);

	// в цикле двигаемся по линии, ищем ближайший тайл с которым можно столкнутся
	Vector2i closestXIntersTile;
	bool collision = false;
	float closestScan = FLT_MAX;
	for (auto it = xInters.begin(); it != xInters.end(); it++) {
		for (float scan = 0; scan < map->getTileSize() * 3; scan += map->getTileSize()) {
			float x = forward + scan * direction;
			float y = *it;
			if (Map::isCollidable(map->getTileNum(x, y)) && (scan < closestScan)) {
				collision = true;
				closestXIntersTile = Vector2i(x, y);
				closestScan = scan;
				break;
			}
		}
	}

	// предполагаемое движение
	float forwardFrameMovement = speed.x*elapsed.asSeconds();
	float distanceToQuad = FLT_MAX;

	// движение до препятствия
	if (collision) {
		auto quad = map->getQuad(closestXIntersTile.x, closestXIntersTile.y);
		distanceToQuad = direction * min(abs(forward - quad[0].position.x), abs(forward - quad[1].position.x));
	}

	// берем минимум между "до преп." и предполагаемым
	float realMovement = direction * min( abs(forwardFrameMovement), abs(distanceToQuad) );
	
	// подправляем скорость в соотв. в перемещением
	if (elapsed.asMilliseconds() != 0)
		speed.x = realMovement / elapsed.asSeconds();

	// двигаемся
	position.x += realMovement;
	
	/* ========================================================================================== */
	// Y movement
	// логика аналогично оси Х
	/* ========================================================================================== */
	direction = (speed.y >= 0) ? 1 : -1;
	forward = (direction > 0) ? bounds.top + bounds.height : bounds.top;
	vector<float> yInters;
	for (float i = bounds.left + 1; i < bounds.left + bounds.width; i += map->getTileSize() / 2) {
		yInters.push_back(i);
	}
	yInters.push_back(bounds.left + bounds.width - 1);
	Vector2i closestYIntersTile;
	collision = false;
	closestScan = FLT_MAX;
	for (auto it = yInters.begin(); it != yInters.end(); it++) {
		for (float scan = 0; scan < map->getTileSize() * 3; scan += map->getTileSize()) {
			float y = forward + scan * direction;
			float x = *it;
			if (Map::isCollidable(map->getTileNum(x, y)) && (scan < closestScan)) {
				collision = true;
				closestYIntersTile = Vector2i(x, y);
				closestScan = scan;
				break;
			}
		}
	}
	speed.y += gravity.y * elapsed.asSeconds();
	forwardFrameMovement = speed.y*elapsed.asSeconds();
	distanceToQuad = FLT_MAX;
	if (collision) {
		auto quad = map->getQuad(closestYIntersTile.x, closestYIntersTile.y);
		distanceToQuad = direction * min(abs(forward - quad[0].position.y), abs(forward - quad[2].position.y));
	}
	realMovement = direction * min(abs(forwardFrameMovement), abs(distanceToQuad));
	if(elapsed.asMilliseconds() != 0)
		speed.y = realMovement / elapsed.asSeconds();
	if (abs(speed.y) < 3) {
		speed.y = 0;
		isOnGround = true;
	}
	else {
		isOnGround = false;
	}
	position.y += realMovement;

	// Move sprite
	//cout << "Speed X: " << speed.x << " Y: " << speed.y << endl;
	sprite.setPosition(position);
}

void Movable::jump()
{
	if(isOnGround)
		speed.y -= 350;
}

// ПОКА не используется. не трогать :Р
bool Movable::isPhasing()
{
	auto bounds = sprite.getGlobalBounds();
	bool phasing = false;
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left, bounds.top));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left + bounds.width, bounds.top));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left, bounds.top + bounds.height));
	phasing = phasing or Map::isCollidable(map->getTileNum(bounds.left + bounds.width, bounds.top + bounds.height));
	return phasing;
}
