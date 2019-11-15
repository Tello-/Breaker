#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


struct BallDef
{
	float32 ptmScale;
	sf::Texture* texture;
	sf::Vector2f windowPosition;
	b2World * world;
	float graphicRadius;
};
class Ball : public sf::Drawable
{
public:
	Ball(const BallDef& def);
	~Ball() 
	{ 
		m_world = nullptr; // owned by physics world
		m_texture = nullptr; // owned by resource manager (game class atm)
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float dt);

	/* Currently used for applying some impulse to the ball while still building the game*/
	void nudge(b2Vec2 direction);

private:
	b2World* m_world;
	float32 m_ptmScale; // conversion factor between pixels and phys units
	b2Body* m_physicsBody;
	sf::CircleShape m_graphicsBody;
	sf::Texture* m_texture;
};