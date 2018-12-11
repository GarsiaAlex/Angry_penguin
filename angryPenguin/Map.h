#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Map : public Drawable{
private:
	VertexArray vertices;
	Texture tileset;
	vector<vector<char>> levelData;
	Vector2u levelSize;
	int tileSize;
	string textureSet, levelFile;
public:
	Map();
	bool load(string textureSet, int size, string levelFile);
	void showDebugWindow(int speed, int fast, float reload);

	int getTileNum(int x, int y);
	int getTileSize();
	Vector2u getLevelSize();

	virtual void draw(RenderTarget & target, RenderStates states) const override;
};