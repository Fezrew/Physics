#pragma once
#include "RigidBody.h"
#include "Rope.h"

class Sphere : public RigidBody
{
public:
	Sphere(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, float radius, vec4 colour);
	~Sphere();

	virtual void draw();

	float getRadius() { return m_radius; }
	bool isRope() { return ropeStatus; }
	void setRope(bool status) { ropeStatus = status; }

protected:
	float m_radius;
	bool ropeStatus = false;
};

