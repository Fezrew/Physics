#pragma once
#include "RigidBody.h"

class Spring : public PhysicsObject
{
public:
	Spring(RigidBody* body1, RigidBody* body2, float restLength, float springCoefficient, float damping, vec4 colour);

	RigidBody* m_body1; 
	RigidBody* m_body2;

	float getDamping() { return m_damping; }
	float getRestLength() { return m_restLength; }
	float getSpringCoefficient() { return m_springCoefficient; }

	virtual void fixedUpdate(vec2 gravity, float timeStep);
	virtual void draw();


protected:
	float m_damping = 0.1f; //leave this alone
	float m_restLength; //length of spring
	float m_springCoefficient; //restoring force
};

