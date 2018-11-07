#include "Ball.h"
#include<cmath>

using namespace sf;

SoundBuffer buf1;
SoundBuffer buf2;
Sound sound;
bool isColled = false;


void Ball::SetBall(float x, float y) {
	ball.setRadius(12);
	ball.setOrigin(12, 12);
	ball.setFillColor(Color::Red);
	ball.setPosition(x, y);
    buf1.loadFromFile("SFX1.wav");
	buf2.loadFromFile("SFX2.wav");
}

void Ball::UpdateState(float dt, bool collisionP1, RectangleShape p1, bool collisionP2, RectangleShape p2, bool collisionBarrier, RectangleShape b)
{
	pos = ball.getPosition();
	pos += vel * dt;

	if (pos.y > 600 && vel.y > 0) {
		vel.y = -vel.y;
		borderCount++;
		sound.setBuffer(buf1);
		sound.play();
	}
	if (pos.y < 0 && vel.y < 0) {
		vel.y = -vel.y;
		borderCount++;
		sound.setBuffer(buf1);
		sound.play();
	}
	if (pos.x > 800 && vel.x > 0) {
		playerSide = 2;
	}
	if (pos.x < 0 && vel.x < 0) {
		playerSide = 1;
	}

	if (reset) {
		playerSide = 0;
		vel.x = -vel.x;
		pos = Vector2f(400, 300);
		count = 0;
		borderCount = 0;
		vel /= sqrt(vel.x*vel.x + vel.y*vel.y);
		vel *= speed;
		if (vel.x < 100&&vel.x>0) vel.x += 100;
		if (vel.x > -100 && vel.x<0) vel.x -= 100;
	}

	if (collisionP1&&!isColled) {
		isColled = true;
		record = 1;
		count++;
		vel = pos - p1.getPosition();
		vel /= sqrt(vel.x*vel.x + vel.y*vel.y);
		vel *= speed;
		vel *= (1 + count / 20);
		sound.setBuffer(buf2);
		sound.play();
	}

	if (collisionP2&&!isColled) {
		isColled = true;
		record = 2;
		count++;
		vel = pos - p2.getPosition();
		vel /= sqrt(vel.x*vel.x + vel.y*vel.y);
		vel *= speed;
		vel *= (1 + count / 20);
		sound.setBuffer(buf2);
		sound.play();
	}

	if (collisionBarrier) {
		vel = pos - b.getPosition();
		vel /= sqrt(vel.x*vel.x + vel.y*vel.y);
		vel *= speed;
		vel *= (1 + count / 20);
	/*	if (pos.x > 300 && pos.x <= 305&&vel.x<0)vel.x = -vel.x;
		if (pos.x >= 295 && pos.x < 300 && vel.x>0)vel.x = -vel.x;*/
		sound.setBuffer(buf1);
		sound.play();
	}

	reset = false;
	isColled = false;
	ball.setPosition(pos);
}

