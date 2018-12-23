#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Penguin.h"
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
	Penguin penguin;

public:
	Game();
	~Game();
	void start(int speed, int fast, float reload);
};
