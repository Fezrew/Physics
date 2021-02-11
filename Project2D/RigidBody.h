#pragma once
#include "PhysicsObject.h"
#include <iostream>

using namespace std;

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, vec2 position, vec2 velocity, float angularVelocity, float moment, float orientation, float mass, vec4 colour);
	~RigidBody();

	virtual void fixedUpdate(vec2 gravity, float timeStep);
	void applyForce(vec2 force, vec2 pos);
	void resolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal = nullptr);

	vec2 getPosition() { return m_position; }
	vec2 getVelocity() { return m_velocity; }
	float getOrientation() { return m_orientation; }
	float getAngularVelocity() { return m_angularVelocity; }
	float getMoment() { return m_moment; }
	float getMass() { return m_mass; }
	float getKineticEnergy() { return 0.5 * m_mass * dot(m_velocity, m_velocity); }
	float getPotentialEnergy();
	float getEnergy() override;

protected:
	vec2 m_position;
	vec2 m_velocity;
	float m_mass = 0;
	float m_orientation = 0;
	float m_angularVelocity; 
	float m_moment;
};
