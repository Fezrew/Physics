#include "Ship.h"

Ship::Ship(vec2 position, float acceleration, float speedCap, float orientation, vec4 colour)
	: PhysicsObject(SHIP, colour)
{
	m_position = position;
	m_orientation = orientation;
	m_acceleration = acceleration;
	m_speedCap = speedCap;
	m_colour = colour;
	m_velocity = vec2(0, 0);
}

Ship::~Ship()
{

}

void Ship::fixedUpdate(vec2 gravity, float timeStep)
{
	vec2 movement = vec2(cosf(m_orientation), sinf(m_orientation)) * m_acceleration;

	if (m_velocity.x <= m_speedCap && m_velocity.y <= m_speedCap)
	{
		applyForce(movement);
	}
	for (int i = 0; i < sizeof(shipParts); i++)
	{
		shipParts[i]->applyForce(movement, shipParts[i]->getPosition());
	}
	m_position += m_velocity * timeStep;

}

void Ship::applyForce(vec2 force)
{
	m_velocity += force / getMass();
}

void Ship::addToShip(RigidBody* rb)
{
	shipParts.push_back(rb);
	rb->setShip(true);
	m_mass += rb->getMass();
	rb->PhysicsObject::setColour(m_colour);
}

void Ship::draw()
{
}
