#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Entity : public Drawable {
protected:
	Sprite sprite;
	Texture texture;
	Vector2f position;

public:
	Entity(string fileName);
	virtual void draw(RenderTarget& target, RenderStates states) const override;
	virtual void update(Time elapsed);
};