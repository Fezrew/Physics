#pragma once
#include "PhysicsObject.h"

/// <summary>
/// A declaration of the RigidBody class
/// </summary>
class RigidBody;

/// <summary>
/// A kinematic one-sided wall
/// </summary>
class Plane : public PhysicsObject
{
public:
	/// <summary>
	/// A constructor that determines the direction, position, and colour of the plane
	/// </summary>
	/// <param name="normal">The direction the plane is facing</param>
	/// <param name="distance">The distance between the plane and the centre of the scene relative to the plane's normal</param>
	/// <param name="colour">The colour of the object</param>
	Plane(vec2 normal, float distance, vec4 colour);
	~Plane();

	/// <summary>
	/// An update called independantly regardless of frame rate
	/// </summary>
	/// <param name="gravity">The gravity of the physics application</param>
	/// <param name="timeStep">The time between every fixed update</param>
	virtual void fixedUpdate(vec2 gravity, float timeStep);

	/// <summary>
	/// Draws a rectangle to display the location of the plane
	/// </summary>
	virtual void draw();

	/// <summary>
	/// A pure virtual function that plane doesn't override
	/// </summary>
	virtual void resetPosition();

	/// <summary>
	/// A pure virtual function that plane doesn't override
	/// </summary>
	virtual void shipMove(vec2 force) {}

	virtual float getMass() { return 0.0f; }
	virtual vec2 getPosition() { return vec2(0, 0); }
	virtual void setPosition(vec2 position) {}

	/// <summary>
	/// A pure virtual function that plane doesn't override
	/// </summary>
	virtual void shipContact(vec2 contact) {}
	
	/// <summary>
	/// A pure virtual function that plane doesn't override
	/// </summary>
	virtual void shipBreak() {}

	/// <summary>
	/// Handles the collision once it's been detected
	/// </summary>
	/// <param name="actor2">The object colliding with the plane</param>
	/// <param name="contact">The point of the plane being collided with</param>
	void resolveCollision(RigidBody* actor2, vec2 contact);

	vec2 getNormal() { return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

protected:
	/// <summary>
	/// The direction the plane is facing
	/// </summary>
	vec2 m_normal;

	/// <summary>
	/// The distance from the centre of the application in the direction of the normal
	/// </summary>
	float m_distanceToOrigin;
};

