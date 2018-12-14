#include "Movable.h"

class Player : public Movable {
private:
	int score;
	int HP;

public:
	Player(string fileName);
	int getHP();
	int getScore();
	void gravitation();
	bool collition();
};