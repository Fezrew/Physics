#include "Sphere.h"
#include <Gizmos.h>
 
Sphere::Sphere(vec2 position, vec2 velocity, float mass, float radius, vec4 colour)
	: RigidBody(SPHERE, position, velocity, 0, mass, colour)
{
	m_radius = radius;
}

Sphere::~Sphere()
{
}

void Sphere::draw()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 50, m_colour);
}
