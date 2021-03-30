#include "Spring.h"


Spring::Spring(RigidBody* body1, RigidBody* body2, float restLength, float springCoefficient, float damping, vec4 colour)
	: PhysicsObject(ShapeType::JOINT, colour), m_body1(body1), m_body2(body2), m_spacing(restLength), m_springForce(springCoefficient), m_damping(damping)
{

}

void Spring::fixedUpdate(vec2 gravity, float timeStep)
{
	vec2 p1 = m_body1->getPosition();
	vec2 p2 = m_body2->getPosition();
	vec2 dist = p2 - p1;

	float length = sqrtf(dist.x * dist.x + dist.y * dist.y);

	vec2 relativeVelocity = m_body2->getVelocity() - m_body1->getVelocity();

	//if (length > m_spacing && m_isLink)
	{
		vec2 force = dist * m_springForce * (m_spacing - length) - m_damping * relativeVelocity;

		// cap the spring force to 1000 N to prevent numerical instability
		const float threshold = 1000.0f;
		float forceMag = glm::length(force);

		if (forceMag > threshold)
		{
			force *= threshold / forceMag;
		}

		m_body1->applyForce(-force * timeStep, p1 - p1);
		m_body2->applyForce(force * timeStep, p2 - p1);
	}
	//else
	//{
		vec2 force = dist * m_springForce * (m_spacing - length) - m_damping * relativeVelocity;

		// cap the spring force to 1000 N to prevent numerical instability
		const float threshold = 1000.0f;
		float forceMag = glm::length(force);

		if (forceMag > threshold)
		{
			force *= threshold / forceMag;
		}


		m_body1->applyForce(-force * timeStep, p1 - p1);
		m_body2->applyForce(force * timeStep, p2 - p1);
	//}
}

void Spring::draw()
{
	vec2 start = m_body1->getPosition();
	vec2 end = m_body2->getPosition() - start;
	aie::Gizmos::add2DLine(start, start + end, m_colour);
}

