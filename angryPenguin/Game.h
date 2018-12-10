#include <SFML/Graphics.hpp>
using namespace sf;

class Game {
private:
	RenderWindow* window;
	Texture background;
	
public:
	Game();
	~Game();
	void start();
};
