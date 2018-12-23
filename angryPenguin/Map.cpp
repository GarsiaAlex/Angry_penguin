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
void Map::showDebugWindow(int speed, int fast, float reload)
{
	// окно размером в высоту карты и шириной=высота*2
	// 300 x 240
	RenderWindow wnd(VideoMode(tileSize * levelSize.y * 2, tileSize * levelSize.y), "MAP WINDOW", Style::Titlebar | Style::Close);
	View view(FloatRect(0, 0, tileSize * levelSize.y * 2, tileSize * levelSize.y));
	float reloadSeconds = reload;
	wnd.setVerticalSyncEnabled(true);
	Clock clock;
	Event event;
	int x, y;
	Vector2f coords;

	// плеер создается тут
	Player m(this, "test_move.png");
	m.position.x = 32*5; m.position.y = 32*6;

	while (wnd.isOpen()) {
		Time elapsed = clock.restart();
		while (wnd.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				wnd.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					wnd.close();
				if (event.key.code == Keyboard::Up)
					m.jump();
				break;
			case Event::MouseMoved:
				coords = wnd.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y), view);
				//cout << coords.x << " " << coords.y << endl;
				break;
			default:
				break;
			}
		}
		wnd.setView(view);
		wnd.clear();
		wnd.draw(*this);

		m.update(elapsed);
		m.move(elapsed);
		wnd.draw(m);

		wnd.display();

		// прокрутка карты
		//if(Keyboard::isKeyPressed(Keyboard::Right))
		//	view.move(Vector2f(elapsed.asSeconds() * (Keyboard::isKeyPressed(Keyboard::Space) ? speed * fast : speed), 0));
		//if (Keyboard::isKeyPressed(Keyboard::Left))
		//	view.move(Vector2f(elapsed.asSeconds() * (Keyboard::isKeyPressed(Keyboard::Space) ? -speed * fast : -speed), 0));

		// перезагрузка карты
		//reloadSeconds -= elapsed.asSeconds();
		//if (reloadSeconds <= 0) {
		//	reloadSeconds = reload;
		//	this->load(textureSet, tileSize, levelFile);
		//}
	}
}

Vertex * Map::getQuad(int x, int y)
{
	Vector2i cell = getTileCell(x, y);
	Vertex* quad = &vertices[(cell.x + cell.y * levelSize.x) * 4];
	return quad;
}

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
	return levelData[min((unsigned int)cell.y, levelData.size() - 1)][min((unsigned int)cell.x, levelData[0].size() - 1)] - '0';
}

void Map::setTileNum(int cellX, int cellY, char value)
{
	levelData[cellY][cellX] = value + '0';
}

bool Map::isCollidable(char value)
{
	switch (value){
	case 2:
		return true;
	default:
		return false;
	}
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
