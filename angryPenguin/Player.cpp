#include "Player.h"

Player::Player(Map* map, string fileName) : Movable (map, fileName) {
	HP = 150;
	score = 0;
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
	////////////////////////
}

int Player::getColType() {
	return  colType::platform;
}
