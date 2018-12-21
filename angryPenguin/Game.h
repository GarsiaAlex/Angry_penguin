#include <SFML/Graphics.hpp>
#include "Map.h"
using namespace sf;

class Game {
private:
	RenderWindow* window;
	Map map;
	Texture background;

public:
	Game();
	~Game();
	void start(int speed, int fast, float reload);
};
