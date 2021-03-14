#include "Ship.h"

Ship::Ship(vec2 position, float acceleration, float speedCap, float turnSpeed, float orientation, vec4 colour, aie::EInputCodes inputLeft, aie::EInputCodes inputRight)
	: PhysicsObject(SHIP, colour)
{
	m_position = position;
	m_acceleration = acceleration;
	m_speedCap = speedCap;
	m_turnSpeed = turnSpeed * (pi<float>() / 180.0f);
	m_orientation = orientation * (pi<float>() / 180.0f);
	m_colour = colour;
	m_velocity = vec2(0, 0);
	m_mass = 0;
	m_left = inputLeft;
	m_right = inputRight;

	ball = new Sphere(m_position, vec2(0, 0), 0, m_orientation, 0.5f, 1.5f, vec4(1, 1, 1, 1));
	ball->setShip(this);

	input = Input::getInstance();
}

Ship::~Ship()
{

}

void Ship::fixedUpdate(vec2 gravity, float timeStep)
{
	shipOrientation = vec2(cosf(m_orientation), sinf(m_orientation));
	vec2 movement = shipOrientation * m_acceleration;

	applyForce(movement);

	if (length(m_velocity) > m_speedCap)
	{
		m_velocity = normalize(m_velocity) * m_speedCap;
	}

	m_position += m_velocity * timeStep;
	ball->setPosition(m_position);
	ball->setOrientation(m_orientation);

	if (input->isKeyDown(m_left))
	{
		m_orientation += m_turnSpeed;
	}
	else if (input->isKeyDown(m_right))
	{
		m_orientation -= m_turnSpeed;
	}

	for (int i = 0; i < shipParts.size(); i++)
	{
		shipParts[i]->setPosition(m_position + (shipParts[i]->getLocalPos() * shipOrientation));
		shipParts[i]->setOrientation(shipParts[i]->getLocalOrientation() + m_orientation);
		shipParts[i]->setVelocity(m_velocity);
	}
}

void Ship::applyForce(vec2 force)
{
	m_velocity += force / getMass();
}

void Ship::addToShip(RigidBody* rb, vec2 localPos, float localOri)
{
	rb->setShip(this);
	shipParts.push_back(rb);
	m_mass += rb->getMass();

	shipOrientation = vec2(cosf(m_orientation), sinf(m_orientation));
	rb->setLocalPos(localPos);
	rb->setLocalOrientation(localOri);
	rb->setPosition(m_position + (localPos * shipOrientation));
	rb->setOrientation(rb->getLocalOrientation() + m_orientation);
	rb->PhysicsObject::setColour(m_colour);
	rb->setVelocity(m_velocity);
}

void Ship::shipContact(vec2 contact)
{
	setPosition(contact);

	for (int i = 0; i < shipParts.size(); i++)
	{
		shipParts[i]->setPosition(m_position + (shipParts[i]->getLocalPos() * shipOrientation));
	}
}

void Ship::shipDestroy()
{
}

void Ship::draw()
{
	ball->draw();
}
