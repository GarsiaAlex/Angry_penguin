#include "Map.h"
#include "Player.h"
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

//перегрузка карты на ходу
bool Map::load(string texture, int size, string levelFile)
{
	// сохраняем параметры карты
	this->textureSet = texture;
	this->tileSize = size;
	this->levelFile = levelFile;

	// считывает карту из текста
	ifstream file(levelFile);
	if (file.fail() || file.bad()) {
		cout << "Error opening level file " << levelFile << endl;
		return false;
	}
	string line;
	bool isLevelCorrect = true;
	while (getline(file, line)) {
		vector<char> layer(line.c_str(), line.c_str() + line.size()); //слой (без \0 символа)
		//-1 ропускает первый заход cчитывfz первую строку как длину уровня
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
	vertices.setPrimitiveType(Quads); //квадр = прямоуг. точки рисуются последовательно 
	vertices.resize(levelSize.x * levelSize.y * 4); //количество квадр. (Важно помнить, что они имеют 4 вершины)

	return refresh();
}

bool Map::refresh()
{
	// для каждой клетки на карте указываем 4 координаты - вершины квадрата, два раза - на карте и в текстуре
	for (int i = 0; i < levelSize.x; i++) {
		for (int j = 0; j < levelSize.y; j++) {
			int tileNum = levelData[j][i] - '0'; //-'0' чтобы начать с 0 (т.к. в рассч нужен 0, а не 48+х)
			int texCoordX = tileNum % (tileset.getSize().x / tileSize);//смещение по осям
			int texCoordY = tileNum / (tileset.getSize().x / tileSize);

			Vertex* quad = &vertices[(i + j * levelSize.x) * 4]; //смещение по вектору на коорд (х + смещ по у)
			quad[0].position = Vector2f(i * tileSize, j * tileSize); //00
			quad[1].position = Vector2f((i + 1) * tileSize, j * tileSize);//10
			quad[2].position = Vector2f((i + 1) * tileSize, (j + 1) * tileSize);//11
			quad[3].position = Vector2f(i * tileSize, (j + 1) * tileSize);//01

			//тож сам но по текстуре
			quad[0].texCoords = Vector2f(texCoordX * tileSize, texCoordY * tileSize);
			quad[1].texCoords = Vector2f((texCoordX + 1) * tileSize, texCoordY * tileSize);
			quad[2].texCoords = Vector2f((texCoordX + 1) * tileSize, (texCoordY + 1) * tileSize);
			quad[3].texCoords = Vector2f(texCoordX * tileSize, (texCoordY + 1) * tileSize);
		}
	}
	return true;
}

//квад пор координатам
Vertex * Map::getQuad(int x, int y)
{
	Vector2i cell = getTileCell(x, y); //ячейка
	Vertex* quad = &vertices[(cell.x + cell.y * levelSize.x) * 4];
	return quad;
}

//получение ячейки
Vector2i Map::getTileCell(int x, int y)
{
	Vector2i cell;
	cell.x = max(x, 0) / tileSize;
	cell.y = max(y, 0) / tileSize;
	return cell;
}

/*
Получение номера тайла (из текстуры) по заданным координатам
!!! при использовании View не забудь window->mapPixelToCoords !!!
*/
int Map::getTileNum(int x, int y)
{
	Vector2i cell = getTileCell(x, y);
	//мин м/у тем, что хотим и границей уровня
	return levelData[min((unsigned int)cell.y, levelData.size() - 1)][min((unsigned int)cell.x, levelData[0].size() - 1)] - '0';
}

void Map::setTileNum(int cellX, int cellY, char value)
{
	levelData[cellY][cellX] = value + '0';
}

bool Map::isCollidable(char value, int colTypeIndex)
{
	if (colTypeIndex == 0) {
		switch (value) {
		case 1:
			return true;
			break;
		default:
			return false;
			break;
		}
	}
	else if (colTypeIndex == 1) {
		switch (value) {
		case 2:
			return true;
			break;
		default:
			return false;
			break;
		}
	}
}

//Получение размера тайла в пикселях
int Map::getTileSize()
{
	return tileSize;
}

//Получение размера карты
Vector2u Map::getLevelSize()
{
	return levelSize;
}

Vector2u Map::getLevelPixelSize()
{
	return Vector2u(levelSize.x * tileSize, levelSize.y * tileSize);
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
