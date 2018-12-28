#include "Player.h"

Player::Player(Map* map, string fileName) : Movable (map, fileName) {
	HP = 150;
	score = 0;
	stateOfDeath = false;
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	CurrentFrame = 0; //Для перемещения по тайлсету
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
			//если морж активирован и если пингвин находится в нужной области действи (+/-50 по х и у)
			if ((*i)->isActive()) {
				sprite.setTextureRect(IntRect(128, 96, 32, 32));	//установка тайла атаки
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
		if (CurrentFrame > 6) CurrentFrame -= 6; //если пришли 6 кадру - 
														 //откатываемся назад. 
		if (speed.y == 0) sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 32, 32, 32)); //Анимация "бег вправо"
		CurrentFrame += 9 * elapsed.asSeconds();
		speed.x = 200;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (CurrentFrame > 6) CurrentFrame -= 6;
		if (speed.y == 0) sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32)); //Влево
		CurrentFrame += 9 * elapsed.asSeconds();
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


