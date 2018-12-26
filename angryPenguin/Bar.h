#include <SFML\Graphics.hpp>
#include "Player.h"
using namespace sf;

class Bar : public Drawable {
private:
	RectangleShape HP;
	Font font;
	Text points;
	Player *player;
	Texture HPTexture;
	Vector2f position;
	Vector2f pointsPosition;

public:
	Bar(string nameOfFileForHP, string nameOfFileForPoints, Player *p, float posXHP, float posXScore);
	void update(Time elapsed);
	virtual void draw(RenderTarget& target, RenderStates states) const override;
	void setPosition(int posX);
	void setPointsPositions(int posX);
};