#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Penguin.h"
#include <list>
using namespace sf;

class Game {
private:
	RenderWindow* window;
	View* view;
	Map map;
	float viewStart, viewEnd;
	float viewOffset;
	Texture background;
	Player player;
	Penguin pengy;
	list<Walrus*> walrii;

public:
	Game();
	~Game();
	void start(int speed);
};
