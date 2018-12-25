#pragma once
#include "Movable.h"
#include "Player.h"

class Penguin : public Movable {
private: 
	float direction;
	bool isCollPlayer = false;
	float colDown = 1;
	int countCollPlayer = 0;

public:
	bool collPlayer(Player *pl);
	void move(Time elapsed, Player *pl);
	Penguin(Map* map, string fileName);
	void update(Time elapsed);
	int getColType();
	void jump();
}; 
