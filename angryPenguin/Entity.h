#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Entity : public Drawable {
private:
	Sprite sprite;
	Texture texture;

public:
	Entity(string fileName);
	virtual void draw();
	virtual void update();
};