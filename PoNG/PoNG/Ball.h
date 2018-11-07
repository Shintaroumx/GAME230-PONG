#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Ball
{
public:
	void SetBall(float x, float y);
	void UpdateState(float dt, bool collisionP1, sf::RectangleShape p1, bool collisionP2, sf::RectangleShape p2, bool collisionBarrier, sf::RectangleShape b);
	sf::CircleShape ball;
	sf::Vector2f vel;
	sf::Vector2f pos;
	float speed;
	float count;
	int playerSide;
	int record=0;
	int borderCount=0;
	bool reset=false;


private:

};


