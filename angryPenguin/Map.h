#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Map : public Drawable{
protected:
	VertexArray vertices;
	Texture tileset;
	vector<vector<char>> levelData;
	Vector2u levelSize;
	int tileSize;
	string textureSet;
	string levelFile;

public:
	Map();
	bool load(string textureSet, int size, string levelFile);
	bool refresh();

	int getTileNum(int x, int y);
	void setTileNum(int x, int y, char value);
	int getTileSize();
	Vector2u getLevelSize();

	virtual void draw(RenderTarget & target, RenderStates states) const override;
};