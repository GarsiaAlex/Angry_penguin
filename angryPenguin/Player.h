#pragma once
#include "Movable.h"
#include "Walrus.h"
#include "Penguin.h"

class Player : public Movable {
private:
	int score;
	int HP;

public:
	Player(Map* map, string fileName);
	int getHP();
	int getScore();
	void addScore(int num);
	void addHP(int num);
	void subHP(int num);
	bool collision();
	void activateWalrus(list<Walrus*> wlr, Penguin& peng);
	virtual void update(Time elapsed) override;
	int getColType();
};