#pragma once
#include "RigidBody.h"

class Spring : public PhysicsObject
{
public:
	//String();
	//~String();

	RigidBody* m_body1; 
	RigidBody* m_body2;

	vec2 m_contact1;
	vec2 m_contact2;

	float getDamping() { return m_damping; }
	float getRestLength() { return m_restLength; }
	float getSpringCoefficient() { return m_springCoefficient; }

	void fixedUpdate(vec2 gravity, float timeStep);


protected:
	float m_damping;
	float m_restLength;
	float m_springCoefficient;
};

