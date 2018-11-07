#include "Paddle.h"

using namespace sf;

void Paddle::SetPaddle(int i) {
	if (i == 1) {
		paddle.setSize(Vector2f(10, 100));
		paddle.setOrigin(5, 50);
		paddle.setFillColor(Color::Blue);
		paddle.setPosition(10, 300);
	}
	if (i == 0 || i == 2) {
		paddle.setSize(Vector2f(10, 100));
		paddle.setOrigin(5, 50);
		paddle.setFillColor(Color::Blue);
		paddle.setPosition(790, 300);
	}
	if (i == 3) {
		paddle.setSize(Vector2f(10, 150));
		paddle.setOrigin(5, 75);
		paddle.setFillColor(Color::White);
		paddle.setPosition(400, 100);
	}	
}

void Paddle::ResetSpeed() {
	speed = 350;
}


void Paddle::UpdateState(float dt,int i,CircleShape b)
{
	Vector2f pos = paddle.getPosition();
	r.left = pos.x-5;
	r.top = pos.y-50;
	r.width = paddle.getSize().x;
	r.height = paddle.getSize().y;

	if (i == 1) {
		if (Keyboard::isKeyPressed(Keyboard::W) && pos.y > 50)
			pos.y -= speed * dt;
		if (Keyboard::isKeyPressed(Keyboard::S) && pos.y < 550)
			pos.y += speed * dt;
	}

	if (i == 2) {
		if (Keyboard::isKeyPressed(Keyboard::Up) && pos.y > 50)
			pos.y -= speed * dt;
		if (Keyboard::isKeyPressed(Keyboard::Down) && pos.y < 550)
			pos.y += speed * dt;
	}

	if (i == 0) {
		if(pos.y+50<b.getPosition().y)
			pos.y += (speed+50) * dt;
		if(pos.y -50> b.getPosition().y)
			pos.y -= (speed +50)* dt;
	}

	if (i == 3) {
		pos += vel * dt;
		if (pos.y > 550 && vel.y > 0)
			vel.y = -vel.y;
		if (pos.y < 50 && vel.y < 0)
			vel.y = -vel.y;
	}

	paddle.setPosition(pos);
}


bool Paddle::Collision(FloatRect r1, FloatRect r2)
{
	return !(r1.left + r1.width <= r2.left ||
		r1.left >= r2.left + r2.width ||
		r1.top + r1.height <= r2.top ||
		r1.top >= r2.top + r2.height);
}




