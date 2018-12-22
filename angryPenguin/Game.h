#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Game {
private:
	RenderWindow* window;
	Map* map;
	Texture background;
	Player player;

public:
	Game();
	~Game();
	void start();
};
