#include "RigidBody.h"
#include "PhysicsScene.h"

RigidBody::RigidBody(ShapeType shapeID, vec2 position, vec2 velocity, float orientation, float mass, vec4 colour) : PhysicsObject(shapeID, colour), m_position(position), m_mass(mass), m_velocity(velocity), m_orientation(orientation)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	applyForce(gravity * m_mass * timeStep);
}

void RigidBody::applyForce(vec2 force)
{
	m_velocity += force / m_mass;
}

// sure

void RigidBody::applyForceToActor(RigidBody* actor2, vec2 force)
{
	actor2->applyForce(-force);
	applyForce(force);
}

void RigidBody::resolveCollision(RigidBody* actor2)
{
	float elasticity = 1;
	vec2 normal = normalize(actor2->getPosition() - m_position);
	vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float j = dot(-(1 + elasticity) * (relativeVelocity), normal) /
		((1 / m_mass) + (1 / actor2->getMass()));

	vec2 force = normal * j;

	float kePre = getKineticEnergy() + actor2->getKineticEnergy();

	applyForceToActor(actor2, -force);

	float kePost = getKineticEnergy() + actor2->getKineticEnergy();

	float deltaKE = kePost - kePre;

	if (deltaKE > kePost * 0.01f)
	{
		cout << "Kinetic Energy discrepancy greater than 1% detected!!";
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
