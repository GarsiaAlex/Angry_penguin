#include "Bar.h"
#include <fstream>

Bar::Bar(string nameOfFileForHP, string nameOfFileForPoints, Player * p, float posXHP, float posXScore)
{
	this->player = p;
	HPTexture.loadFromFile(nameOfFileForHP);		//подгрузить текстуру для HP-bar'a

	//Настройка HP-bar'a
	HP.setSize(Vector2f(player->getHP(), 25));		//Установка нач. размера для его послед. изме. при уменьшении здоровья игрока
	HP.setPosition(Vector2f(position.x = posXHP, position.y = 5));		//Установка расположения HP-bar'a
	HP.setTexture(&HPTexture);			//Установка фонового изображения
	HP.setOutlineThickness(4);			//Установка размера рамки
	HP.setOutlineColor(sf::Color::Blue); //Установка цвета рамки

	//Настройка points
	font.loadFromFile(nameOfFileForPoints);
	points.setFont(font);
	points.setCharacterSize(24);
	points.setPosition(Vector2f(pointsPosition.x = posXScore, 5));
	points.setString("0");
	points.setFillColor(Color::Black);

	// Экран
	blackScreen.setSize(Vector2f(2000, 2000));
	blackScreen.setPosition(Vector2f(0, 0));
	blackScreen.setFillColor(Color(200, 200, 200));

	// Cообщение
	message.setFont(font);
	message.setCharacterSize(40);
	message.setPosition(Vector2f(10, 10));
	message.setFillColor(Color::Red);
}

void Bar::update(Time elapsed)
{
	int HPLevel = player->getHP();
	int pointsLevel = player->getScore();
	if (HPLevel < 0)
		HPLevel = 0;
	HP.setSize(Vector2f(HPLevel, 25));
	HP.setTextureRect(IntRect(0, 0, (int)HPLevel*1.5, 25));
	points.setString(std::to_string(pointsLevel));

	HP.setPosition(Vector2f(position.x, position.y));
	points.setPosition(Vector2f(pointsPosition.x, pointsPosition.y));
}

void Bar::draw(RenderTarget & target, RenderStates states) const
{
	if (gameStarted) {
		target.draw(HP, states);
		target.draw(points, states);
	}
	else {
		target.draw(blackScreen);
		target.draw(message);
	}
}

void Bar::setPosition(int posX)
{
	position.x = posX;
}

void Bar::setPointsPositions(int posX)
{
	pointsPosition.x = posX;
}

void Bar::setMsg(String str)
{
	message.setString(str);
}

void Bar::setMsgPosition(Vector2f coords)
{
	message.setPosition(coords);
}

void Bar::loadMsgFromFile(std::string fileName)
{
	string s, buffer;
	ifstream file(fileName);
	while (file >> buffer) {
		if (buffer == "n") {
			s += "\n";
		}
		else {
			s += buffer;
			s += " ";
		}
	}
	setMsg(s);
}

bool Bar::isStarted()
{
	return gameStarted;
}

void Bar::startGame()
{
	gameStarted = true;
}

void Bar::stopGame()
{
	gameStarted = false;
}
