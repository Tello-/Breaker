#include "paddle.h"
#include <iostream>

Paddle::Paddle(const PaddleDef& def)
	: m_world{ def.world }, m_ptmScale{ def.ptmScale }, m_texture{ def.texture }
{

	b2Vec2 physSize = b2Vec2{ def.pixelSize.x / m_ptmScale, def.pixelSize.y / m_ptmScale };
	b2Vec2 physPos = b2Vec2{ def.windowPosition.x / m_ptmScale, def.windowPosition.y / m_ptmScale };
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_kinematicBody;
	myBodyDef.position.Set(physPos.x, physPos.y);

	m_physicsBody = m_world->CreateBody(&myBodyDef);
	b2PolygonShape polyShape;

	
	polyShape.SetAsBox(physSize.x / 2.0f, physSize.y / 2.0f);

	b2FixtureDef polyFixtureDef;

	polyFixtureDef.shape = &polyShape;
	polyFixtureDef.density = 1.f;
	polyFixtureDef.restitution = 0.1f;
	polyFixtureDef.friction = 0.f;
	m_physicsBody->CreateFixture(&polyFixtureDef);


	m_graphicsBody.setFillColor(sf::Color::Green);
	m_graphicsBody.setOrigin(def.pixelSize / 2.0f);
	m_graphicsBody.setSize(def.pixelSize);	
	m_graphicsBody.setPosition(def.windowPosition);
}

void Paddle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_graphicsBody);
}

void Paddle::update(float dt)
{
	m_graphicsBody.setPosition(m_physicsBody->GetPosition().x * m_ptmScale, m_physicsBody->GetPosition().y * m_ptmScale);

}

void Paddle::nudge(NudgeDirection dir, float32 force)
{
	m_physicsBody->SetLinearVelocity(b2Vec2{ force * (float32)dir, 0.0f });
}
