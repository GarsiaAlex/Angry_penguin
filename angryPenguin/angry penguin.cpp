#include "Game.h"
#include "Map.h"

int main() {
	Map map;
	map.load("tileset.png", 32, "map.txt");
	map.showDebugWindow(500, 5, 1);
	/*
	Game game;
	game.start();
	*/
}