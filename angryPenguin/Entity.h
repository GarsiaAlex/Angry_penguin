#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <vector>
using namespace sf;
using namespace std;

class Entity : public Drawable {
public:
	Sprite sprite;
	Texture texture;
	Vector2f position;

public:
	Entity(string fileName);
	virtual void draw(RenderTarget& target, RenderStates states) const override;
	virtual void update(Time elapsed);
};