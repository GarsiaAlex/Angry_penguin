#include "Movable.h"

class Penguin : public Movable {
private: 
	float direction;
public:
	bool collPlayer();
	void move(Time elapsed);
	Penguin(Map* map, string fileName);
	void update(Time elapsed, Movable *pl);

}; 
