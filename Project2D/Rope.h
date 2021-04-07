#pragma once
#include "PhysicsScene.h"

/// <summary>
/// A declaration of a RigidBody class
/// </summary>
class RigidBody;
/// <summary>
/// A declaration of a Sphere object
/// </summary>
class Sphere;

/// <summary>
/// A class that connects two rigidbodies by a series of springs
/// </summary>
class Rope
{
public:
	/// <summary>
	/// Places the rope in a scene with a set length
	/// </summary>
	/// <param name="scene"></param>
	/// <param name="length">The number of links in the rope</param>
	Rope(PhysicsScene* scene, int length);

	/// <summary>
	/// Connects two objects with the rope
	/// </summary>
	/// <param name="obj1">The object at the start of the rope</param>
	/// <param name="obj2">The object at the end of the rope</param>
	void Build(RigidBody* obj1, RigidBody* obj2);

	float getSpacing() { return m_spacing; }
	float getLength() { return m_length; }

protected:
	/// <summary>
	/// The scene that the rope is in
	/// </summary>
	PhysicsScene* m_scene;

	/// <summary>
	/// An array that holds a pointer to every link in the rope
	/// </summary>
	Sphere** m_spheres = nullptr;

	/// <summary>
	/// The link at the start of the rope
	/// </summary>
	Sphere* ropeStart = nullptr;
	/// <summary>
	/// The link at the end of the rope
	/// </summary>
	Sphere* ropeEnd = nullptr;

	/// <summary>
	/// The colour of the rope
	/// </summary>
	vec4 m_colour;

	/// <summary>
	/// The distance between each link
	/// </summary>
	double m_spacing = 0.75f;

	/// <summary>
	/// The restoring force of each spring in the rope
	/// </summary>
	float m_springForce = 30.0f;

	/// <summary>
	/// The drag slowing down the restoring force of the springs
	/// </summary>
	float m_damping = 10.0f;

	/// <summary>
	/// The amount of links in a rope
	/// </summary>
	int m_length = 0;

	/// <summary>
	/// The size of the links
	/// </summary>
	float m_linkRadius = 0.005f;
};
