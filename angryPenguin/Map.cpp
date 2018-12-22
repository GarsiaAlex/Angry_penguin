#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map()
{
	this->levelSize.x = -1;
	this->levelSize.y = -1;
}

/*
Загрузка тайлсета
texture: путь к картинке с тайлсетом
size: размер стороны квадрата одной клетки в пикселях
level: путь к текстовому файлу с уровнем
*/
bool Map::load(string texture, int size, string level)
{
	// сохраняем параметры карты
	this->textureSet = texture;
	this->tileSize = size;
	this->levelFile = level;

	// считывает карту из текста
	ifstream file(levelFile);
	if (file.fail() || file.bad()) {
		cout << "Error opening level file " << levelFile << endl;
		return false;
	}
	string line;
	bool isLevelCorrect = true;
	while (getline(file, line)) {
		vector<char> layer(line.c_str(), line.c_str() + line.size());
		if (levelSize.x != -1 && levelSize.x != layer.size())
			isLevelCorrect = false;
		levelSize.x = layer.size();
		levelData.push_back(layer);
	}
	file.close();
	if (!isLevelCorrect) {
		cout << "Lines in level file must be of equal size" << endl;
		return false;
	}
	levelSize.y = levelData.size();

	// загружаем текстуру и инициализируем квады
	tileset.loadFromFile(textureSet);
	vertices.setPrimitiveType(Quads);
	vertices.resize(levelSize.x * levelSize.y * 4);

	return refresh();
}

bool Map::refresh()
{
	// для каждой клетки на карте указываем 4 координаты - вершины квадрата, два раза - на карте и в текстуре
	for (int i = 0; i < levelSize.x; i++) {
		for (int j = 0; j < levelSize.y; j++) {
			int tileNum = levelData[j][i] - '0';
			int texCoordX = tileNum % (tileset.getSize().x / tileSize);
			int texCoordY = tileNum / (tileset.getSize().x / tileSize);

			Vertex* quad = &vertices[(i + j * levelSize.x) * 4];
			quad[0].position = Vector2f(i * tileSize, j * tileSize);
			quad[1].position = Vector2f((i + 1) * tileSize, j * tileSize);
			quad[2].position = Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
			quad[3].position = Vector2f(i * tileSize, (j + 1) * tileSize);

			quad[0].texCoords = Vector2f(texCoordX * tileSize, texCoordY * tileSize);
			quad[1].texCoords = Vector2f((texCoordX + 1) * tileSize, texCoordY * tileSize);
			quad[2].texCoords = Vector2f((texCoordX + 1) * tileSize, (texCoordY + 1) * tileSize);
			quad[3].texCoords = Vector2f(texCoordX * tileSize, (texCoordY + 1) * tileSize);
		}
	}
	return true;
}

/*
Окно для рисования карты
speed: скорость обычной прокрутки в пикселях/секунду
fast: speed*fast = скорость ускоренной прокрутки при зажатом пробеле
reload: время перезагрузки карты из файла в секундах
*/
/*
Получение номера тайла (из текстуры) по заданным координатам
!!! при использовании View не забудь window->mapPixelToCoords !!!
*/
int Map::getTileNum(int x, int y)
{
	int cellX, cellY;
	cellX = x / tileSize;
	cellY = y / tileSize;
	return levelData[cellY][cellX] - '0';
}

void Map::setTileNum(int x, int y, char value)
{
	levelData[y][x] = value + '0';
}

/*
Получение размера тайла в пикселях
*/
int Map::getTileSize()
{
	return tileSize;
}

/*
Получение размера карты
*/
Vector2u Map::getLevelSize()
{
	return levelSize;
}

/*
Наследуется из sf::Drawable
Отрисовка карты
*/
void Map::draw(RenderTarget & target, RenderStates states) const
{
	states.texture = &tileset;
	target.draw(vertices, states);
}
