#include "Penguin.h"

//метод проверки столкновения с игроком
bool Penguin::collPlayer(Player *pl)
{
	if (this->sprite.getGlobalBounds().intersects(pl->sprite.getGlobalBounds())) {
		countCollPlayer += 1;
		return isCollPlayer = true;
	}
	else
		countCollPlayer = 0;
		return isCollPlayer = false;
}

Penguin::Penguin(Map* map, string fileName) : Movable(map, fileName) {
	speed.y = 300;
	position.x = 100;
	position.y = 300;
	colType::water;
}

void Penguin::update(Time elapsed)
{
	int direction = (speed.x > 0) ? 1 : -1;
	if (abs(speed.x) > 30) {
		speed.x = 30;
		speed.x *= direction;
	}
	direction = (speed.y>0) ? 1 : -1;
	if (abs(speed.y) > 700) {
		speed.y = 700;
		speed.y *= direction;
	}
}

int Penguin::getColType() {
	return  colType::water;
}

void Penguin::jump()
{
	if (isOnGround)
		speed.y -= 500;
}

void Penguin::move(Time elapsed, Player *pl)
{
	Direction = (pl->position - this->position);
	//std::cout << Direction.x << "  - x   " << Direction.y << "  - y" << endl;
	colDown -= elapsed.asSeconds();
	if (abs(Direction.x) < 300) {
		if (colDown <= 0) {
			colDown = 1;
			jump();
		}
	}

	//cout << "x/y    " << (Direction.x / Direction.y) << endl;
	speed.x = Direction.x*3;
	Movable::move(elapsed);

	//результат столкновения пингвина с игроком
	collPlayer(pl);
	if (isCollPlayer) {
		if (countCollPlayer == 1)
		pl->subHP(10);
	}

}