#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map()
{
	this->levelSizeX = -1;
	this->levelSizeY = -1;
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
	vector<vector<char>> levelData;
	bool isLevelCorrect = true;
	while (getline(file, line)) {
		vector<char> layer(line.c_str(), line.c_str() + line.size());
		if (levelSizeX != -1 && levelSizeX != layer.size())
			isLevelCorrect = false;
		levelSizeX = layer.size();
		levelData.push_back(layer);
	}
	file.close();
	if (!isLevelCorrect) {
		cout << "Lines in level file must be of equal size" << endl;
		return false;
	}
	levelSizeY = levelData.size();

	// загружаем текстуру и инициализируем квады
	tileset.loadFromFile(textureSet);
	vertices.setPrimitiveType(Quads);
	vertices.resize(levelSizeX * levelSizeY * 4);

	// для каждой клетки на карте указываем 4 координаты - вершины квадрата, два раза - на карте и в текстуре
	for (int i = 0; i < levelSizeX; i++) {
		for (int j = 0; j < levelSizeY; j++) {
			int tileNum = levelData[j][i] - '0';
			int texCoordX = tileNum % (tileset.getSize().x / tileSize);
			int texCoordY = tileNum / (tileset.getSize().x / tileSize);

			Vertex* quad = &vertices[(i + j * levelSizeX) * 4];
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
	RenderWindow wnd(VideoMode(tileSize * levelSizeY * 2, tileSize * levelSizeY), "MAP WINDOW", Style::Titlebar | Style::Close);
	View view(FloatRect(0, 0, tileSize * levelSizeY * 2, tileSize * levelSizeY));
	float reloadSeconds = reload;
	wnd.setVerticalSyncEnabled(true);
	Clock clock;
	Event event;
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
				break;
			default:
				break;
			}
		}
		wnd.setView(view);
		wnd.clear();
		wnd.draw(*this);
		wnd.display();

		// прокрутка карты
		if(Keyboard::isKeyPressed(Keyboard::Right))
			view.move(Vector2f(elapsed.asSeconds() * (Keyboard::isKeyPressed(Keyboard::Space) ? speed * fast : speed), 0));
		if (Keyboard::isKeyPressed(Keyboard::Left))
			view.move(Vector2f(elapsed.asSeconds() * (Keyboard::isKeyPressed(Keyboard::Space) ? -speed * fast : -speed), 0));

		// перезагрузка карты
		reloadSeconds -= elapsed.asSeconds();
		if (reloadSeconds <= 0) {
			reloadSeconds = reload;
			this->load(textureSet, tileSize, levelFile);
		}
	}
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
