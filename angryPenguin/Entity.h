#include <SFML/Graphics.hpp>
using namespace sf;

class Entity : public Drawable {
protected:
	Sprite sprite;
	Texture texture;

public:
	virtual void draw();
	virtual void update();
};