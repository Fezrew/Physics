#pragma once
#include "RigidBody.h"

class Sphere : public RigidBody
{
public:
	Sphere(vec2 position, vec2 velocity, float mass, float radius, vec4 colour);
	~Sphere();

	virtual void draw();

	float getRadius() { return m_radius; }

protected:
	float m_radius;
};

