#pragma once
#include "PhysicsScene.h"

class RigidBody;
class Sphere;

class Rope
{
public:

	Rope(PhysicsScene* scene, int length);
	void Build(RigidBody* obj1, RigidBody* obj2);

	float getSpacing() { return m_spacing; }
	float getLength() { return m_length; }

protected:

	PhysicsScene* m_scene;
	Sphere** m_spheres = nullptr;
	Sphere* ropeStart = nullptr;
	Sphere* ropeEnd = nullptr;
	vec4 m_colour;

	double m_spacing = 0.1f;
	float m_springForce = 100.0f;
	float m_damping = 98.0f;
	int m_length = 0;
	float m_linkSize = 0.5f;
};
