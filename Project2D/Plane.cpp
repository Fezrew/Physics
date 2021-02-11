#include "Plane.h"
#include "RigidBody.h"

Plane::Plane(vec2 normal, float distance, vec4 colour) : PhysicsObject(ShapeType::PLANE, colour)
{
	m_distanceToOrigin = distance;
	m_normal = normal;
	colour = m_colour;
}

Plane::~Plane()
{
}

void Plane::fixedUpdate(vec2 gravity, float timeStep)
{
}

void Plane::draw()
{
	float lineSegmentLength = 300;
	vec2 centerPoint = m_normal * m_distanceToOrigin;
	vec2 parallel(m_normal.y, -m_normal.x);

	vec4 colourFade = m_colour;
	colourFade.a = 0;

	vec2 start = centerPoint + (parallel * lineSegmentLength);
	vec2 end = centerPoint - (parallel * lineSegmentLength);

	//aie::Gizmos::add2DLine(start, end, colour)
	aie::Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_colour, m_colour, colourFade);
	aie::Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, m_colour, colourFade, colourFade);
}

void Plane::resetPosition()
{
}

void Plane::resolveCollision(RigidBody* actor2, vec2 contact)
{
	float elasticity = 1;

	float j = dot(-(1 + elasticity) * (actor2->getVelocity()), m_normal) / (1 / actor2->getMass());

	vec2 force = m_normal * j;

	float kePre = actor2->getKineticEnergy();

	actor2->applyForce(force, contact - actor2->getPosition());

	float kePost = actor2->getKineticEnergy();

	float deltaKE = kePost - kePre;

	if (deltaKE > kePost * 0.01f)
	{
		cout << "Kinetic Energy discrepancy greater than 1% detected!!";
	}
}
