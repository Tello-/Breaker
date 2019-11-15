#include "ball.h"

Ball::Ball(const BallDef& def) 
	: m_world{def.world}, m_ptmScale{def.ptmScale}, m_texture{def.texture}, m_physicsBody{nullptr}
{

	float32 physSize{ def.graphicRadius / m_ptmScale };

	b2BodyDef myBodyDef;
	myBodyDef.bullet = true;
	myBodyDef.type = b2_dynamicBody; 
	myBodyDef.position.Set(def.windowPosition.x / m_ptmScale , def.windowPosition.y / m_ptmScale );

	m_physicsBody = m_world->CreateBody(&myBodyDef);
	b2CircleShape circShape;
	circShape.m_radius = def.graphicRadius / m_ptmScale;

	b2FixtureDef circFixtureDef;

	circFixtureDef.shape = &circShape;
	circFixtureDef.density = 0.f;
	circFixtureDef.restitution = 1.f;
	circFixtureDef.friction = 0.f;
	m_physicsBody->CreateFixture(&circFixtureDef);

	m_physicsBody->SetGravityScale(0.0f);

	
	m_graphicsBody.setFillColor(sf::Color::Green);
	m_graphicsBody.setOrigin(def.graphicRadius, def.graphicRadius);
	m_graphicsBody.setRadius(def.graphicRadius);	
	m_graphicsBody.setPosition(def.windowPosition);
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_graphicsBody);
}

void Ball::update(float dt)
{
	m_graphicsBody.setPosition(m_physicsBody->GetPosition().x * m_ptmScale, m_physicsBody->GetPosition().y * m_ptmScale);
}

void Ball::nudge(b2Vec2 direction)
{
	m_physicsBody->ApplyLinearImpulseToCenter(direction, true);
}
