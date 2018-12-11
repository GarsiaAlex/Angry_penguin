#include "Movable.h"

class Player : public Movable {
private:
	int score;
	int HP;

public:
	Player(Texture texture);
	int getHP();
	int getScore();
	void gravitation();
	bool collition();
};