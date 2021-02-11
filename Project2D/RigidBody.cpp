#include "RigidBody.h"
#include "PhysicsScene.h"

RigidBody::RigidBody(ShapeType shapeID, vec2 position, vec2 velocity, float angularVelocity, float moment, float orientation, float mass, vec4 colour) : PhysicsObject(shapeID, colour), m_position(position), m_mass(mass), m_velocity(velocity), m_angularVelocity(angularVelocity), m_orientation(orientation), m_moment(moment)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	applyForce(gravity * m_mass * timeStep, {0, 0});

	m_orientation += m_angularVelocity * timeStep;
}

void RigidBody::applyForce(vec2 force, vec2 pos)
{
	m_velocity += force / getMass(); 
	m_angularVelocity += (force.y * pos.x - force.x * pos.y) / getMoment();
}

void RigidBody::resolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal)
{
	vec2 normal = normalize(collisionNormal ? *collisionNormal : actor2->m_position - m_position);
	vec2 perp(normal.y, -normal.x);
	
	float r1 = dot(contact - m_position, -perp);
	float r2 = dot(contact - actor2->m_position, perp);

	float v1 = dot(m_velocity, normal) - r1 * m_angularVelocity;
	float v2 = dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity;

	if (v1 > v2)
	{
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);

		float elasticity = 1;

		vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		float kePre = getKineticEnergy() + actor2->getKineticEnergy();

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
