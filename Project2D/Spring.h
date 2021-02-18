#pragma once
#include "RigidBody.h"

class Spring : public PhysicsObject
{
public:
	Spring(RigidBody* body1, RigidBody* body2, float spacing, float springForce, float damping, vec4 colour);

	RigidBody* m_body1; 
	RigidBody* m_body2;

	float getDamping() { return m_damping; }
	float getRestLength() { return m_spacing; }
	float getSpringCoefficient() { return m_springForce; }

	virtual void fixedUpdate(vec2 gravity, float timeStep);
	virtual void draw();


protected:
	float m_damping = 0.1f; //leave this alone
	float m_spacing; //length of spring
	float m_springForce; //restoring force
};

