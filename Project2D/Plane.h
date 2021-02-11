#pragma once
#include "PhysicsObject.h"

class RigidBody;

class Plane : public PhysicsObject
{
public:
	Plane(vec2 normal, float distance, vec4 colour);
	~Plane();

	virtual void fixedUpdate(vec2 gravity, float timeStep);
	virtual void draw();
	virtual void resetPosition();
	void resolveCollision(RigidBody* actor2, vec2 contact);

	vec2 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

protected:
	vec2 m_normal;
	float m_distanceToOrigin;
};

