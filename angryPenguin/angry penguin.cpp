#include "Game.h"
#include "Map.h"

int main() {
	/*
	отладочное окно для рисования карты
	*/
	
	Map map;
	map.load("tileset.png", 32, "map.txt");
	map.showDebugWindow(500, 5, 1);
	//*/
	/*
	основной объект игры
	*/
	//Game game;
	//game.start();
}