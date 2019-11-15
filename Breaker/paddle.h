#pragma once

#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


struct PaddleDef
{
	float32 ptmScale;
	sf::Texture* texture;
	sf::Vector2f windowPosition;
	b2World * world;
	sf::Vector2f pixelSize;
};
class Paddle : public sf::Drawable
{
public:
	Paddle(const PaddleDef& def);
	~Paddle()
	{
		m_physicsBody = nullptr; // belongs to physics world
		m_world = nullptr; // belongs to physics world
		m_texture = nullptr; // belongs to resource manager(game class at the moment)
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float dt);	

	enum NudgeDirection { LEFT = -1, NONE, RIGHT };
	void nudge(NudgeDirection dir, float32 force);

private:
	b2World* m_world;
	float32 m_ptmScale; // conversion factor between pixels and phys units
	b2Body* m_physicsBody{ nullptr };
	sf::RectangleShape m_graphicsBody;
	sf::Texture* m_texture;  
};