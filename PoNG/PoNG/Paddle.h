#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Paddle
{
public:
	void SetPaddle(int i);
	void ResetSpeed();
	void UpdateState(float dt,int i,sf::CircleShape b);
	bool Collision(sf::FloatRect r1, sf::FloatRect r2);
	sf::RectangleShape paddle;
	sf::FloatRect r;
	sf::Vector2f vel;
	int speed;

private:

};

