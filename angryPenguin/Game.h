#include <SFML/Graphics.hpp>
#include "Player.h"
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

public:
	Game();
	~Game();
	void start();
};
