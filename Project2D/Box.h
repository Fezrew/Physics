#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, vec4 colour, float width, float height);
	~Box();

	vec2 getExtents() { return m_extents; }

	float getWidth() { return m_extents.x * 2; }
	float getHeight() { return m_extents.y * 2; }

	bool checkBoxCorners(const Box& box, vec2& contact, int& numContacts, float &pen, vec2& edgeNormal);
	void draw();

protected:
	vec2 m_extents;

};

