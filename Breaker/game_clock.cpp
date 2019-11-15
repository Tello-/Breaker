#include "game_clock.h"

GameClock::GameClock(float fps)
	: m_clock{ new sf::Clock{} }, m_elapsed{ 0.f }, m_lastTick{ 0.0f }, m_fps{ fps }
{
	m_frametime = 1.0f / m_fps;
}

void GameClock::reset()
{
	m_elapsed = 0.f;
	m_lastTick = 0.0f;
	delete m_clock;
	m_clock = new sf::Clock{};
}

void GameClock::update()
{
	m_elapsed += m_clock->restart().asSeconds();
}

void GameClock::tick()
{	
	m_elapsed -= m_frametime;
}
