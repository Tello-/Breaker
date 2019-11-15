#pragma once
#include <Box2D/Box2D.h>

class Enclosure
{
public:
	Enclosure(const b2Vec2& size, const float scale, b2World& world) : m_world{ &world }
	{

		b2BodyDef bd;
		m_body = m_world->CreateBody(&bd);
		b2EdgeShape shape;

		b2Vec2 halfSize{ size.x / 2.0f, size.y / 2.0f};
		b2Vec2 scaledSize{ halfSize.x / scale, halfSize.y / scale };

		b2Vec2 bL = b2Vec2{-scaledSize.x, -scaledSize.y} + scaledSize;
		b2Vec2 bR = b2Vec2{scaledSize.x, -scaledSize.y} +scaledSize;
		b2Vec2 tL = b2Vec2{-scaledSize.x, scaledSize.y} +scaledSize;
		b2Vec2 tR = b2Vec2{scaledSize.x, scaledSize.y} +scaledSize;

		
		// Floor
		shape.Set(bL, bR);
		m_body->CreateFixture(&shape, 0.0f);

		// Left wall
		shape.Set(bL, tL);
		m_body->CreateFixture(&shape, 0.0f);

		// Right wall
		shape.Set(bR, tR);
		m_body->CreateFixture(&shape, 0.0f);

		// Roof
		shape.Set(tL, tR);
		m_body->CreateFixture(&shape, 0.0f);
	}

	~Enclosure() { 
		m_body = nullptr; // owned by physics world
		m_world = nullptr; // owned by physics world
	}

private:
	b2Body* m_body;
	b2World* m_world;
};