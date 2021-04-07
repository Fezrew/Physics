#pragma once
#include "RigidBody.h"

/// <summary>
/// A class that creates a line between two objects and holds them at a set distance
/// </summary>
class Spring : public PhysicsObject
{
public:
	/// <summary>
	/// A constructor that connects two RigidBodies
	/// </summary>
	/// <param name="body1">The first object being connected</param>
	/// <param name="body2">The second object being connected</param>
	/// <param name="spacing">The desired distance between both objects</param>
	/// <param name="springForce">The restoring force of the spring</param>
	/// <param name="damping">The drag slowing down the restoring force of the spring</param>
	/// <param name="colour">The colour of the spring</param>
	Spring(RigidBody* body1, RigidBody* body2, float spacing, float springForce, float damping, vec4 colour);

	/// <summary>
	/// The first object being connected by the spring
	/// </summary>
	RigidBody* m_body1; 
	/// <summary>
	/// The second object being connected by the spring
	/// </summary>
	RigidBody* m_body2;

	float getDamping() { return m_damping; }
	float getRestLength() { return m_spacing; }
	float getSpringCoefficient() { return m_springForce; }

	bool getLinkStatus() { return m_isLink; }
	void setLinkStatus(bool state) { m_isLink = state; }

	/// <summary>
	/// An update called independantly regardless of frame rate
	/// </summary>
	/// <param name="gravity">The gravity of the physics application</param>
	/// <param name="timeStep">The time between every fixed update</param>
	virtual void fixedUpdate(vec2 gravity, float timeStep);

	virtual float getMass() { return 0.0f; }
	virtual void setPosition(vec2 position) {}
	virtual vec2 getPosition() { return vec2(0, 0); }

	/// <summary>
	/// A pure virtual function that spring doesn't override
	/// </summary>
	virtual void shipMove(vec2 force) {}
	/// <summary>
	/// A pure virtual function that spring doesn't override
	/// </summary>
	virtual void shipContact(vec2 contact) {}
	/// <summary>
	/// A pure virtual function that spring doesn't override
	/// </summary>
	virtual void shipBreak() {}

	/// <summary>
	/// draws a line between both objects being connected
	/// </summary>
	virtual void draw();

protected:
	/// <summary>
	/// The drag slowing down the restoring force of the spring
	/// </summary>
	float m_damping = 0.1f;
	/// <summary>
	/// The desired distance between both objects being connected
	/// </summary>
	float m_spacing;
	/// <summary>
	/// The restoring force of the spring
	/// </summary>
	float m_springForce;

	/// <summary>
	/// Says if the spring a part of a rope
	/// </summary>
	bool m_isLink = false;
};

