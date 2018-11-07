#include "Item.h"

using namespace sf;

void Item::SetItem(int i,float x,float y)
{
	tex.loadFromFile("split.png");
	if (i == 1) {
		item.setRadius(20);
		item.setPosition(x, y);
		item.setTexture(&tex);
		item.setFillColor(Color::Red);
	}//Split
	if (i == 2) {
		item.setRadius(20);
		item.setPosition(x, y);
		item.setTexture(&tex);
		item.setFillColor(Color::Green);
	}//PowerUp
	r = item.getGlobalBounds();
}


bool Item::Collision(FloatRect r1, FloatRect r2)
{
	return !(r1.left + r1.width <= r2.left ||
		r1.left >= r2.left + r2.width ||
		r1.top + r1.height <= r2.top ||
		r1.top >= r2.top + r2.height);
}