#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "constants.h"
#include "enclosure.h"
#include "game_clock.h"
#include "ball.h"
#include "paddle.h"

class Breakout
{
public:
	Breakout(float width, float height);
	~Breakout();

	void run();
	void update(float dt);

private:
	void input();
	void render();
	void reset();

	void initGameObjects();
	void initBall(const sf::Vector2f& pixelPos);
	void initPaddle(const sf::Vector2f& pixelPos);

private:
	sf::RenderWindow* m_window;
	b2World* m_world;


	Enclosure m_enclosure;
	Ball* m_ball;
	Paddle* m_paddle;

	bool shouldNudge{ false };
	enum PaddleDirection {LEFT = -1, NONE, RIGHT} paddleDir;
};

// TODO: build resource manager to facilitate texture functionality