#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Item
{
public:
	void SetItem(int i, float x, float y);
	bool Collision(sf::FloatRect r1, sf::FloatRect r2);
	sf::CircleShape item;
	sf::FloatRect r;
	sf::Texture tex;

};

