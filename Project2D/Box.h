#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, vec4 colour);
	~Box();

	vec2 m_extents;
	vec4 m_colour;

	vec2 m_localX;
	vec2 m_localY;

	void fixedUpdate(vec2 gravity, float timeStep);
	void draw();

protected:

};

