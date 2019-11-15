#pragma once

#include <SFML/System/Clock.hpp>

class GameClock
{
public:
	/* Note: Clock starts at construction*/
	GameClock(float fps = 60.0f);

	~GameClock() { delete m_clock; }

	/* Restart the clock */
	void reset();

	/* Update the current time of the clock */
	void update();

	/* True if elapsed time > time needed for a frame */
	inline bool readyToTick() const { return m_elapsed >= m_frametime; }

	/* Reduces elapsed time by 1 frame count */
	void tick();

	/* Elapsed time since last tick */
	inline float elapsed() const { return m_elapsed; };

	/* Gets the fps count */
	inline float getFps() const { return m_fps; }

private:
	sf::Clock* m_clock;
	float m_elapsed;
	float m_lastTick;
	float m_frametime;
	float m_fps;
};
