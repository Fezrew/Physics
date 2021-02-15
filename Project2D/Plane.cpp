#include "Plane.h"
#include "RigidBody.h"
#include "PhysicsScene.h"

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
	vec2 localContact = contact - actor2->getPosition();

	vec2 vRel = actor2->getVelocity() + actor2->getAngularVelocity() * vec2(-localContact.y, localContact.x);
	float velocityIntoPlane = dot(vRel, m_normal);

	float r = dot(localContact, vec2(m_normal.y, -m_normal.x));
	float mass0 = 1.0f / (1.0f / actor2->getMass() + (r * r) / actor2->getMoment());

	float elasticity = 0.925;

	float j = -(1 + elasticity) * velocityIntoPlane * mass0;

	vec2 force = m_normal * j;

	float kePre = actor2->getKineticEnergy();

	actor2->applyForce(force, contact - actor2->getPosition());

	float pen = glm::dot(contact, m_normal) - m_distanceToOrigin;
	PhysicsScene::ApplyContactForces(actor2, nullptr, m_normal, pen);

	float kePost = actor2->getKineticEnergy();

	float deltaKE = kePost - kePre;

	if (deltaKE > kePost * 0.01f)
	{
		cout << "Kinetic Energy discrepancy greater than 1% detected!!";
	}
}
