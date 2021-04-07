#pragma once
#include "RigidBody.h"
#include "Rope.h"

/// <summary>
/// A round rigidbody class
/// </summary>
class Sphere : public RigidBody
{
public:
	/// <summary>
	/// The constructor for the sphere class that passes in all of its information through the parameters
	/// </summary>
	/// <param name="position">The starting position of the sphere's centre</param>
	/// <param name="velocity">The starting velocity of the sphere</param>
	/// <param name="angularVelocity">The starting rotational velocity of the sphere</param>
	/// <param name="orientation">The starting rotation of the sphere</param>
	/// <param name="mass">The weight of the sphere</param>
	/// <param name="radius">The distance between the centre of the sphere and its edge</param>
	/// <param name="colour">The colour of the sphere</param>
	Sphere(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, float radius, vec4 colour);
	~Sphere();

	/// <summary>
	/// Draws the sphere and a line showing its orientation
	/// </summary>
	virtual void draw();

	float getRadius() { return m_radius; }
	bool isRope() { return ropeStatus; }
	void setRope(bool status) { ropeStatus = status; }

protected:
	/// <summary>
	/// The distance between the centre of the sphere and its edge
	/// </summary>
	float m_radius;

	/// <summary>
	/// Says if the sphere a part of a rope
	/// </summary>
	bool ropeStatus = false;
};

