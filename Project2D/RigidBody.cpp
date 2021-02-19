#include "RigidBody.h"
#include "PhysicsScene.h"

RigidBody::RigidBody(ShapeType shapeID, vec2 position, vec2 velocity, float angularVelocity, float moment, float orientation, float mass, vec4 colour)
	: PhysicsObject(shapeID, colour), m_position(position), m_mass(mass), m_velocity(velocity), m_angularVelocity(angularVelocity), m_orientation(orientation), m_moment(moment)
{
	m_linearDrag = 0.0f;
	m_angularDrag = 0.0f;
	m_isKinematic = false;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(vec2 gravity, float timeStep)
{
	float cs = cosf(m_orientation);
	float sn = sinf(m_orientation);

	m_localX = normalize(vec2(cs, sn));
	m_localY = normalize(vec2(-sn, cs));

	if (m_isKinematic)
	{
		m_velocity = vec2(0);
		m_angularVelocity = 0;
		return;
	}

	applyForce(gravity * getMass() * timeStep, { 0, 0 });
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	m_position += m_velocity * timeStep;

	m_orientation += m_angularVelocity * timeStep;

	if (length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		if (length(m_velocity) < length(gravity) * m_linearDrag * timeStep)
		{
			m_velocity = vec2(0, 0);
		}
	}
	if (abs(m_angularVelocity) < MIN_ANGULAR_THRESHOLD)
	{
		m_angularVelocity = 0;
	}
}

void RigidBody::applyForce(vec2 force, vec2 pos)
{

	if (isShip())
	{
		m_ship->applyForce(force);
	}
	else
	{
		m_velocity += force / getMass();
		m_angularVelocity += (force.y * pos.x - force.x * pos.y) / getMoment();
	}
}

void RigidBody::resolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal, float pen)
{
	vec2 normal = normalize(collisionNormal ? *collisionNormal : actor2->m_position - m_position);
	vec2 perp(normal.y, -normal.x);

	float r1 = dot(contact - m_position, -perp);
	float r2 = dot(contact - actor2->m_position, perp);

	float v1 = dot(m_velocity, normal) - r1 * m_angularVelocity;
	float v2 = dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity;

	if (v1 > v2)
	{
		float mass1 = 1.0f / (1.0f / getMass() + (r1 * r1) / getMoment());
		float mass2 = 1.0f / (1.0f / actor2->getMass() + (r2 * r2) / actor2->getMoment());

		float elasticity = 0.925f;

		vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		float kePre = getKineticEnergy() + actor2->getKineticEnergy();

		if (pen > 0)
		{
			PhysicsScene::ApplyContactForces(this, actor2, normal, pen);
		}

		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);

		float kePost = getKineticEnergy() + actor2->getKineticEnergy();

		float deltaKE = kePost - kePre;

		if (deltaKE > kePost * 0.01f)
		{
			cout << "Kinetic Energy discrepancy greater than 1% detected!!";
		}
	}
}

float RigidBody::getPotentialEnergy()
{
	return -getMass() * dot(PhysicsScene::getGravity(), getPosition());
}
float RigidBody::getEnergy()
{
	return getKineticEnergy() + getPotentialEnergy();
}

glm::vec2 RigidBody::toWorld(vec2 localPos)
{
	return m_position + localPos.x * m_localX + localPos.y * m_localY;
}
