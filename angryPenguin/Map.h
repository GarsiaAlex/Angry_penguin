#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Map : public Drawable{
private:
	VertexArray vertices;
	Texture tileset;
	int tileSize, levelSizeX, levelSizeY;
	string textureSet, levelFile;
public:
	Map();
	bool load(string textureSet, int size, string levelFile);
	void showDebugWindow(int speed, int fast, float reload);

	virtual void draw(RenderTarget & target, RenderStates states) const override;
};