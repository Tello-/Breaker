#include "breakout.h"

#include <iostream>
using namespace std;

Breakout::Breakout(float width, float height) 
	: m_window{new sf::RenderWindow{ sf::VideoMode{(unsigned)WINDOW_WIDTH, (unsigned)WINDOW_HEIGHT}, "Breaker" } },
	m_world{new b2World{b2Vec2{0.0f, 10.0f}}}, m_enclosure{ b2Vec2{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}, SCALE, *m_world }, 
	m_ball{nullptr}
{
	reset();	
}

/* Need to start getting familiar with smart pointers
	-- or decide if/when pointers are necessary at all. */
Breakout::~Breakout()
{
	delete m_world;
	delete m_ball;
	m_ball = nullptr;
	m_world = nullptr;
	
}

void Breakout::run()
{
	GameClock clock{ FPS };
	while (m_window->isOpen())
	{
		clock.update();
		input();
		if (clock.readyToTick())
		{
			update(clock.elapsed());
			clock.tick();
		}

		render();		
	}
}

void Breakout::update(float dt)
{
	

	if (shouldNudge) m_ball->nudge(b2Vec2{1.0f, -4.0f});

	switch (paddleDir)
	{
	case Breakout::LEFT:
		m_paddle->nudge(Paddle::NudgeDirection::LEFT, 10.0f);
		break;
	case Breakout::RIGHT:
		m_paddle->nudge(Paddle::NudgeDirection::RIGHT, 10.0f);
		break;
	case Breakout::NONE:
		m_paddle->nudge(Paddle::NudgeDirection::NONE, 0.0f);
	default:
		break;
	}

	m_ball->update(dt);
	m_paddle->update(dt);

	m_world->Step(1 / FPS, 10, 8);
}

void Breakout::input()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			
			m_window->close();
		}
		
	}

	/* This if/else group is for giving the ball some momentum for debugging currently*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		shouldNudge = true;
	}
	else
	{
		shouldNudge = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		paddleDir = LEFT;
		
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		paddleDir = RIGHT;
	}
	else
	{
		paddleDir = NONE;
	}
}

void Breakout::render()
{
	m_window->clear();
	m_window->draw(*m_ball);
	m_window->draw(*m_paddle);
	m_window->display();
}

void Breakout::reset()
{
	initGameObjects();
}

void Breakout::initGameObjects()
{
	initBall(sf::Vector2f{ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
	initPaddle(sf::Vector2f{ WINDOW_WIDTH / 2.0f, .80 * WINDOW_HEIGHT });
}

void Breakout::initBall(const sf::Vector2f& pixelPos)
{
	BallDef bDef;
	bDef.graphicRadius = 15.0f;
	bDef.ptmScale = SCALE;
	bDef.windowPosition = pixelPos;
	bDef.world = m_world;
	bDef.texture = nullptr;

	if (m_ball) delete m_ball;
	
	m_ball = new Ball{ bDef };
}

void Breakout::initPaddle(const sf::Vector2f & pixelPos)
{
	PaddleDef pDef;
	pDef.pixelSize = sf::Vector2f{ 100.0f, 30.0f };
	pDef.ptmScale = SCALE;
	pDef.windowPosition = pixelPos;
	pDef.world = m_world;
	pDef.texture = nullptr;

	if (m_paddle) delete m_paddle;

	m_paddle = new Paddle{ pDef };
}
