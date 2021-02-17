#include "Spring.h"


Spring::Spring(RigidBody* body1, RigidBody* body2, float restLength, float springCoefficient, float damping, vec4 colour) 
	: PhysicsObject(ShapeType::JOINT, colour), m_body1(body1), m_body2(body2), m_restLength(restLength), m_springCoefficient(springCoefficient), m_damping(damping)
{
	
}

void Spring::fixedUpdate(vec2 gravity, float timeStep)
{
	vec2 dist = m_body2->getPosition() - m_body1->getPosition();

	float length = sqrtf(dist.x * dist.x + dist.y * dist.y);

	vec2 relativeVelocity = m_body2->getVelocity() - m_body1->getVelocity();

	vec2 force = dist * m_springCoefficient * (m_restLength - length) - m_damping * relativeVelocity;

	m_body1->applyForce(-force * timeStep, m_body1->getPosition() - m_body1->getPosition());
	m_body2->applyForce(force * timeStep, m_body2->getPosition() - m_body1->getPosition());
}

void Spring::draw()
{
	vec2 start = m_body1->getPosition();
	vec2 end = m_body2->getPosition() - start;
	aie::Gizmos::add2DLine(start, start + end, m_colour);
}
