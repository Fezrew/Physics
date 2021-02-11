#include "Sphere.h"
#include <Gizmos.h>
 
Sphere::Sphere(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, float radius, vec4 colour)
	: RigidBody(SPHERE, position, velocity, angularVelocity, 0.5f * mass * radius * radius, orientation, mass, colour)
{
	m_radius = radius;
}

Sphere::~Sphere()
{
}

void Sphere::draw()
{
	vec2 end = glm::vec2(cos(m_orientation), sin(m_orientation)) * m_radius;

	aie::Gizmos::add2DCircle(m_position, m_radius, 50, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, vec4(1, 1, 1, 1));
}
