#include "Player.h"

Player::Player(Map* map, string fileName) : Movable (map, fileName) {
	HP = 150;
	score = 0;
	stateOfDeath = false;
	colType:: platform;
}

int Player::getHP() {
	return HP;
}

int Player::getScore() {
	return score;
}

void Player::addScore(int num) {
	score += num;
}

void Player::addHP(int num) {
	HP += num;
}

void Player::subHP(int num) {
	HP -= num;
}

bool Player::collision()
{
	return false;
}

void Player::activateWalrus(list<Walrus*> wlr, Movable& peng)
{
	for (auto i = wlr.begin(); i != wlr.end(); i++) {
		if (sprite.getGlobalBounds().intersects((*i)->sprite.getGlobalBounds())) {
			// DO SOMETHING
			// (**i) <= морж
			// this <= плеер
			
			//если морж активирован и если пингвин находится в нужной области действи (+/-50 по х и у)
			if ((*i)->isActive()) {
				if (abs(peng.position.x - (*i)->position.x) <= 50) {
					peng.position.x -= 200;
					if (abs(peng.position.y - (*i)->position.y) <= 50) {
						peng.position.x -= 200;
					}
				}
				(*i)->deactivate();
				break;
			}
		}
	}
}

void Player::update(Time elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		speed.x = 200;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		speed.x = -200;
	}
	else {
		speed.x = 0;
	}

	//уменьшение количества здоровья раз в секунду
	colDown -= elapsed.asSeconds();
	if (colDown <= 0) {
		colDown = 1;
		subHP(5);
	}
	//////////////////////// Взаимодействие со звездой
	auto bounds = sprite.getGlobalBounds();


	collStarAndSweater(); //проверка столкновения с свитером и/или звездой
	onDeath();			  //проверка "а не умер ли случаем наш игрок?"
}

int Player::getColType() {
	return  colType::platform;
}

bool Player::getStateOfDeath()
{
	return stateOfDeath;
}

//Метод устанавливающий момент смерти
void Player::onDeath()
{
	auto bounds = sprite.getGlobalBounds();

	if (HP <= 0)
		stateOfDeath = true;

	if (map->getTileNum(bounds.left + 20, bounds.top + 20) == 1) {
		HP = 0;
	}
}

void Player::collStarAndSweater()
{
	//////////////////////// Взаимодействие со звездой
	auto bounds = sprite.getGlobalBounds();

	if (map->getTileNum(bounds.left + 20, bounds.top + 20) == 4)
	{
		auto cell = map->getTileCell(bounds.left + 20, bounds.top + 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		addScore(10);
	}

	if (map->getTileNum(bounds.left + 20, bounds.top + bounds.height - 20) == 4)
	{
		auto cell = map->getTileCell(bounds.left + 20, bounds.top + bounds.height - 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		addScore(10);
	}

	if (map->getTileNum(bounds.left + bounds.width - 20, bounds.top + 20) == 4)
	{
		auto cell = map->getTileCell(bounds.left + bounds.width - 20, bounds.top + 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		addScore(10);
	}

	if (map->getTileNum((bounds.left + bounds.width) - 20, (bounds.top + bounds.width) - 20) == 4)
	{
		auto cell = map->getTileCell((bounds.left + bounds.width) - 20, (bounds.top + bounds.width) - 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		addScore(10);
	}
	////////////////////////

	//////////////////////// Взаимодействие со свитером
	bounds = sprite.getGlobalBounds();


	if (map->getTileNum(bounds.left + 20, bounds.top + 20) == 3)
	{
		auto cell = map->getTileCell(bounds.left + 20, bounds.top + 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		if (HP < 141)
			addHP(10);
	}

	if (map->getTileNum(bounds.left + 20, bounds.top + bounds.height - 20) == 3)
	{
		auto cell = map->getTileCell(bounds.left + 20, bounds.top + bounds.height - 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		if (HP < 141)
			addHP(10);
	}

	if (map->getTileNum(bounds.left + bounds.width - 20, bounds.top + 20) == 3)
	{
		auto cell = map->getTileCell(bounds.left + bounds.width - 20, bounds.top + 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		if (HP < 141)
			addHP(10);
	}

	if (map->getTileNum((bounds.left + bounds.width) - 20, (bounds.top + bounds.width) - 20) == 3)
	{
		auto cell = map->getTileCell((bounds.left + bounds.width) - 20, (bounds.top + bounds.width) - 20);
		map->setTileNum(cell.x, cell.y, 0);
		map->refresh();
		if (HP < 141)
			addHP(10);
	}

}


