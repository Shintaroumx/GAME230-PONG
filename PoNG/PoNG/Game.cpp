#include "Ball.h"
#include "Paddle.h"
#include"Item.h"
#include<ctime>
#include<cstdlib>

using namespace sf;

void RenderFrame();
void SettingText();
void Score();
void ResetPaddle();

float x = 0;
float y = 0;
float xx = 0;
float yy = 0;
RenderWindow window;
Font font;
Ball ball1;
Ball ball2;
Paddle playerPaddle;
Paddle AIPaddle;
Paddle obstacle;
Paddle p2Paddle;
Item powerUp;
Item split;
int p1Score;
int p2Score;
Text tp1Score,tp2Score;
Text winningInfo;
Text playMode;
bool gameOver;
bool gameStart;
int mode=0;
bool showPower;
bool showSplit;
bool newRound;
bool reset;
bool isPlayed = false;
bool isPlayed2 = false;
SoundBuffer powerUpSd;
SoundBuffer splitSd;
SoundBuffer endSd;
SoundBuffer menuSd;
SoundBuffer startSd;
SoundBuffer scoreSd;
Sound sd;
Sound menuMusic;


int main()
{	
	//Initialize
	window.create(VideoMode(800, 600), "SFML Example");
	font.loadFromFile("verdana.ttf");
	powerUpSd.loadFromFile("SFX4.wav");
	endSd.loadFromFile("SFX9.wav");
	startSd.loadFromFile("start.wav");
	splitSd.loadFromFile("split.wav");
	menuSd.loadFromFile("menu.wav");
	scoreSd.loadFromFile("score.wav");
	Clock clock;

	ball1.SetBall(400,300);
	ball1.vel = Vector2f(300, 20);
	ball1.speed = sqrt(ball1.vel.x*ball1.vel.x+ ball1.vel.y*ball1.vel.y);
	ball1.playerSide = 0;
	ball1.count = 0;

	playerPaddle.ResetSpeed();
	p2Paddle.ResetSpeed();
	AIPaddle.ResetSpeed();

	p1Score = 0;
	p2Score = 0;
	gameOver = false;
	gameStart = false;
	showPower = false;
	showSplit = false;
	newRound = true;
	static bool reset = false;

	playerPaddle.SetPaddle(1);
	AIPaddle.SetPaddle(0);
	p2Paddle.SetPaddle(2);
	obstacle.SetPaddle(3);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		
		}
		SettingText();
		float dt = clock.restart().asSeconds();
		srand((unsigned)time(nullptr));
		x = 200 + rand() % (600 - 200 + 1);
		y = 100 + rand() % (300 - 100 + 1);
		xx = 200 + rand() % (600 - 200 + 1);
		yy = 300 + rand() % (500 - 300 + 1);

		if (!gameStart) {
			if (menuMusic.getStatus() != SoundSource::Playing) {
				menuMusic.setBuffer(menuSd);
				menuMusic.play();
			}
			ball1.vel = Vector2f(0, 0);
			obstacle.vel = Vector2f(0, 0);
			if (Keyboard::isKeyPressed(Keyboard::F1)) {
				mode = 1;
				gameStart = true;
				ball1.vel = Vector2f(300, 20);
				obstacle.vel = Vector2f(0, 250);
			}
			if (Keyboard::isKeyPressed(Keyboard::F2)) {
				mode = 2;
				gameStart = true;
				ball1.vel = Vector2f(300, 20);
				obstacle.vel = Vector2f(0, 250);
			}
		}


		if (!gameOver&&gameStart) {
			menuMusic.stop();
			if (sd.getStatus() != SoundSource::Playing && !isPlayed2) {
				sd.setBuffer(startSd);
				sd.play();
				isPlayed2 = true;
			}
			if (mode == 1) {
				ball1.UpdateState(dt, playerPaddle.Collision(playerPaddle.r, ball1.ball.getGlobalBounds()), playerPaddle.paddle, AIPaddle.Collision(AIPaddle.r, ball1.ball.getGlobalBounds()), AIPaddle.paddle, obstacle.Collision(obstacle.r, ball1.ball.getGlobalBounds()), obstacle.paddle);
				if(!newRound)
				    ball2.UpdateState(dt, playerPaddle.Collision(playerPaddle.r, ball2.ball.getGlobalBounds()), playerPaddle.paddle, AIPaddle.Collision(AIPaddle.r, ball2.ball.getGlobalBounds()), AIPaddle.paddle, obstacle.Collision(obstacle.r, ball2.ball.getGlobalBounds()), obstacle.paddle);
				playerPaddle.UpdateState(dt, 1, ball1.ball);
				AIPaddle.UpdateState(dt, 0, ball1.ball);
			}
			if (mode == 2) {
				ball1.UpdateState(dt, playerPaddle.Collision(playerPaddle.r, ball1.ball.getGlobalBounds()), playerPaddle.paddle, p2Paddle.Collision(p2Paddle.r, ball1.ball.getGlobalBounds()), p2Paddle.paddle, obstacle.Collision(obstacle.r, ball1.ball.getGlobalBounds()), obstacle.paddle);
				if(!newRound)
				    ball2.UpdateState(dt, playerPaddle.Collision(playerPaddle.r, ball2.ball.getGlobalBounds()), playerPaddle.paddle, p2Paddle.Collision(p2Paddle.r, ball2.ball.getGlobalBounds()), p2Paddle.paddle, obstacle.Collision(obstacle.r, ball2.ball.getGlobalBounds()), obstacle.paddle);
				playerPaddle.UpdateState(dt, 1, ball1.ball);
				p2Paddle.UpdateState(dt, 2, ball1.ball);
			}

			obstacle.UpdateState(dt, 3, ball1.ball);
			if (p1Score == 5) {
				winningInfo.setString("P1 Win!");
				gameOver= true;
			}
			if (p2Score == 5) {
				winningInfo.setString("P2 Win!");
				gameOver= true;
			}

			if (ball1.count == 8) {//Powerup trigger 
				if (!showPower) {
					powerUp.SetItem(2, xx, yy);
				}
					showPower = true;
			}
			if (ball1.borderCount == 4) {//Split trigger
				if (!showSplit) {
					split.SetItem(1, x, y);
				}
					showSplit = true;
			}


			if (showSplit&&newRound) {
				if (split.Collision(split.r, ball1.ball.getGlobalBounds())) {
					if (sd.getStatus() != SoundSource::Playing) {
						sd.setBuffer(splitSd);
						sd.play();
					}
					newRound = false;
					ball2.SetBall(ball1.ball.getPosition().x, ball1.ball.getPosition().y);
					ball2.vel = -ball1.vel;
					ball2.speed = sqrt(ball1.vel.x*ball1.vel.x + ball1.vel.y*ball1.vel.y);
					ball2.playerSide = 0;
					ball2.count = 0;
					showSplit = false;
				}
			}

			if (showPower) {
				if (powerUp.Collision(powerUp.r, ball1.ball.getGlobalBounds())) {

					if (sd.getStatus() != SoundSource::Playing) {
						sd.setBuffer(powerUpSd);
						sd.play();
					}
					if (ball1.record == 1) {
						playerPaddle.speed = 500;
						playerPaddle.paddle.setFillColor(Color::Cyan);
					}
					if (ball1.record == 2) {
						p2Paddle.speed = 500;
						AIPaddle.speed = 470;
						p2Paddle.paddle.setFillColor(Color::Cyan);
						AIPaddle.paddle.setFillColor(Color::Cyan);
					}
					showPower = false;
				}
				if (powerUp.Collision(powerUp.r, ball2.ball.getGlobalBounds())) {
					if (sd.getStatus() != SoundSource::Playing) {
						sd.setBuffer(powerUpSd);
						sd.play();
					}
					if (ball2.record == 1) {
						playerPaddle.speed =500;
						playerPaddle.paddle.setFillColor(Color::Cyan);
					}
					if (ball2.record == 2) {
						p2Paddle.speed = 500;
						AIPaddle.speed = 470;
						p2Paddle.paddle.setFillColor(Color::Cyan);
						AIPaddle.paddle.setFillColor(Color::Cyan);
					}
					showPower = false;
				}
			}
		}


		if (gameOver) {
			if (sd.getStatus() != SoundSource::Playing&&!isPlayed) {
				sd.setBuffer(endSd);
				sd.play();
				isPlayed = true;
			}
			ball1.vel = Vector2f(0,0);
			ResetPaddle();
			obstacle.vel = Vector2f(0, 0);
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				p1Score = 0;
				p2Score = 0;
				gameOver = false;
				gameStart = false;
				newRound = true;
				isPlayed = false;
				isPlayed2 = false;
			}
		}

		RenderFrame();
		Score();

		window.display();
	}

	return 0;
}


void RenderFrame()
{
	window.clear();
	window.draw(ball1.ball);
	if(!newRound)window.draw(ball2.ball);
	window.draw(playerPaddle.paddle);
	if(mode==1)window.draw(AIPaddle.paddle);
	if(mode==2)window.draw(p2Paddle.paddle);
	window.draw(obstacle.paddle);
	window.draw(tp1Score);
	window.draw(tp2Score);
	if(gameOver)	window.draw(winningInfo);
	if (!gameStart)window.draw(playMode);
	if (showSplit&&newRound)window.draw(split.item);
	if (showPower)window.draw(powerUp.item);
}


void SettingText()
{
	tp1Score.setFont(font);
	tp1Score.setString(std::to_string(p1Score));
	tp1Score.setCharacterSize(50);
	tp1Score.setStyle(sf::Text::Bold);
	tp1Score.setFillColor(sf::Color::White);

	tp2Score.setFont(font);
	tp2Score.setPosition(770,0);
	tp2Score.setString(std::to_string(p2Score));
	tp2Score.setCharacterSize(50);
	tp2Score.setStyle(sf::Text::Bold);
	tp2Score.setFillColor(sf::Color::White);

	winningInfo.setFont(font);
	winningInfo.setPosition(300, 300);
	winningInfo.setCharacterSize(50);
	winningInfo.setStyle(sf::Text::Bold);
	winningInfo.setFillColor(sf::Color::White);

	playMode.setFont(font);
	playMode.setString("Press F1 to play with AI or press F2 to play with another player");
	playMode.setPosition(50, 550);
	playMode.setCharacterSize(20);
	playMode.setStyle(sf::Text::Bold);
	playMode.setFillColor(sf::Color::White);
}

void Score()
{
	if (ball1.playerSide == 1|| ball2.playerSide == 1)
	{
		if (sd.getStatus() != SoundSource::Playing) {
			sd.setBuffer(scoreSd);
			sd.play();
		}
		p2Score++;
		ball1.reset = true;
		ball2.reset = true;
		ResetPaddle();
		newRound = true;
		showPower = false;
		showSplit = false;
	}
	if (ball1.playerSide == 2|| ball2.playerSide == 2)
	{
		if (sd.getStatus() != SoundSource::Playing) {
			sd.setBuffer(scoreSd);
			sd.play();
		}
		p1Score++;
		ball1.reset = true;
		ball2.reset = true;
		ResetPaddle();
		newRound = true;
		showPower = false;
		showSplit = false;
	}
	ball1.playerSide = 0;
	ball2.playerSide = 0;
}


void ResetPaddle() {
	playerPaddle.ResetSpeed();
	p2Paddle.ResetSpeed();
	AIPaddle.ResetSpeed();
	obstacle.paddle.setPosition(400, 100);
	playerPaddle.paddle.setFillColor(Color::Blue);
	p2Paddle.paddle.setFillColor(Color::Blue);
	AIPaddle.paddle.setFillColor(Color::Blue);
}


