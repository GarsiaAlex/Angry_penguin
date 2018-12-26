#include "Walrus.h"

Walrus::Walrus(Map * map, string fileName, Vector2f start) : Movable(map, fileName)
{
	active = true;
	position = start;
}

bool Walrus::isActive()
{
	return active;
}

void Walrus::deactivate()
{
	active = false;
}

int Walrus::getColType()
{
	return colType::platform;
}

void Walrus::unloadListOfWalrus(list<Walrus*> wlr)
{
	/*if (wlr.size() > 0) {
		cout << wlr.size() << endl;
		for (auto iter = wlr.begin(); iter != wlr.end(); iter++) {
			if ((*iter)->active == false) {
				delete (*iter);
				iter = wlr.erase(iter);
			}
		}
	}*/
}
