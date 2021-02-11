#include "Box.h"

Box::Box(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, vec4 colour)
	: RigidBody(BOX, position, velocity, angularVelocity, 0 /*moment value needed*/, orientation, mass, colour)
{

}

void Box::fixedUpdate(vec2 gravity, float timeStep)
{
	RigidBody::fixedUpdate(gravity, timeStep);

	float cs = cosf(m_orientation);
	float sn = sinf(m_orientation);

	m_localX = normalize(vec2(cs, sn));
	m_localY = normalize(vec2(-sn, cs));
}

void Box::draw()
{
}
