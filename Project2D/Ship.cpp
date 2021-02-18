#include "Ship.h"

Ship::Ship(vec2 position, float acceleration, float speedCap, float orientation)
{
	m_position = position;
	m_orientation = orientation;
	m_acceleration = acceleration;
	m_speedCap = speedCap;
}

void Ship::fixedUpdate(vec2 gravity, float timeStep)
{
	vec2 movement = vec2(cosf(m_orientation), sinf(m_orientation)) * m_acceleration;

	if (m_velocity.x <= m_speedCap && m_velocity.y <= m_speedCap)
	{
		applyForce(movement);
	}
	for (int i = 0; i <= sizeof(shipParts); i++)
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
	rb.setColour(m_colour)
}
