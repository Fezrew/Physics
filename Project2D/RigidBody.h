#pragma once
#include "PhysicsObject.h"
#include <iostream>

using namespace std;

/// <summary>
/// The minimum linear momentum capable before stopping completely
/// </summary>
const float MIN_LINEAR_THRESHOLD = 0.001469f;
/// <summary>
/// The minimum angular momentum capable before stopping completely
/// </summary>
const float MIN_ANGULAR_THRESHOLD = 0.4f;

/// <summary>
/// A physics object with mass, velocity, and rotation
/// </summary>
class RigidBody : public PhysicsObject
{
public:
	/// <summary>
	/// A constructor that covers the universal values of any deriving class
	/// </summary>
	/// <param name="shapeID">The shape of the object</param>
	/// <param name="position">The starting global position of the object</param>
	/// <param name="velocity">The starting velocity of the object</param>
	/// <param name="angularVelocity">The starting rotational momentum of the object</param>
	/// <param name="moment">The rotational mass of the object</param>
	/// <param name="orientation">The rotation of the object</param>
	/// <param name="mass">The weight of the object</param>
	/// <param name="colour">The colour of the object</param>
	RigidBody(ShapeType shapeID, vec2 position, vec2 velocity, float angularVelocity, float moment, float orientation, float mass, vec4 colour);
	~RigidBody();

	/// <summary>
	/// An update called independantly regardless of frame rate
	/// </summary>
	/// <param name="gravity">The gravity of the physics application</param>
	/// <param name="timeStep">The time between every fixed update</param>
	virtual void fixedUpdate(vec2 gravity, float timeStep);

	/// <summary>
	/// A pure virtual function that RigidBody doesn't override
	/// </summary>
	virtual void shipMove(vec2 force) {}

	/// <summary>
	/// A pure virtual function that RigidBody doesn't override
	/// </summary>
	virtual void shipContact(vec2 contact) {}
	/// <summary>
	/// A pure virtual function that RigidBody doesn't override
	/// </summary>
	virtual void shipBreak() {}

	/// <summary>
	/// Applies force to a colliding object
	/// </summary>
	/// <param name="force">The force behind the object colliding with the RigidBody</param>
	/// <param name="pos">The position of the object colliding with the RigidBody</param>
	void applyForce(vec2 force, vec2 pos);

	/// <summary>
	/// Executes the result of a collision between objects after the collision has been confirmed
	/// </summary>
	/// <param name="actor2">The actor colliding with the RigidBody</param>
	/// <param name="contact">The point of contact between the RigidBody and the second actor</param>
	/// <param name="collisionNormal">The direction the second actor is colliding with the RigidBody from</param>
	/// <param name="pen">The amount an object has penetrated the RigidBody</param>
	void resolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal = nullptr, float pen = 0);

#pragma region Get/Set
	void setVelocity(vec2 velocity) { m_velocity = velocity; }
	vec2 getVelocity() { return m_velocity; }
	virtual void setPosition(vec2 position) { m_position = position; }
	virtual vec2 getPosition() { return m_position; }
	float getMass() { return m_isKinematic ? INT_MAX : m_mass; }
	void setOrientation(float orientation) { m_orientation = orientation; }
	float getOrientation() { return m_orientation; }
	float getAngularVelocity() { return m_angularVelocity; }
	float getMoment() { return m_isKinematic ? INT_MAX : m_moment; }
	float getKineticEnergy() { return 0.5f * (m_mass * dot(m_velocity, m_velocity) + m_moment * m_angularVelocity * m_angularVelocity); }
	float getPotentialEnergy();
	float getEnergy() override;
	void setKinematic(bool state) { m_isKinematic = state; }
	bool isKinematic() { return m_isKinematic; }

	PhysicsObject* getShip() { return m_ship; }
	void setShip(PhysicsObject* ship) { m_ship = ship; }
	bool isShip() { return m_ship != nullptr; }
	void setShipCollided(bool state) { shipCollided = state; }
	bool getShipCollided() { return shipCollided != false; }

	void setLocalOrientation(float localOrientation) { m_localOrientation = localOrientation * (pi<float>() / 180.0f); }
	float getLocalOrientation() { return m_localOrientation; }
	void setLocalPos(vec2 localPos) { m_localPos = localPos; }
	vec2 getLocalPos() { return m_localPos; }
	vec2 getLocalX() { return m_localX; }
	vec2 getLocalY() { return m_localY; }
#pragma endregion

	/// <summary>
	/// Finds the global position of an object
	/// </summary>
	/// <param name="localPos">The local position of the object</param>
	vec2 toWorld(vec2 localPos);

protected:
	/// <summary>
	/// The position of the RigidBody
	/// </summary>
	vec2 m_position;

	/// <summary>
	/// The velocity of the RigidBody
	/// </summary>
	vec2 m_velocity;

	/// <summary>
	/// The mass of the RigidBody
	/// </summary>
	float m_mass = 0;

	/// <summary>
	/// The rotation of the RigidBody
	/// </summary>
	float m_orientation = 0;

	/// <summary>
	/// The rotational velocity of the RigidBody
	/// </summary>
	float m_angularVelocity;

	/// <summary>
	/// The rotational mass of the object
	/// </summary>
	float m_moment;

	/// <summary>
	/// The amount the RigidBody's linear velocity slows while moving
	/// </summary>
	float m_linearDrag;
	/// <summary>
	/// The amount the RigidBody's angular velocity slows while spinning
	/// </summary>
	float m_angularDrag;

	/// <summary>
	/// The RigidBody's kinematic status
	/// </summary>
	bool m_isKinematic;

	/// <summary>
	/// The RigidBody's orientation in comparison to the ship it is attached to
	/// </summary>
	float m_localOrientation;

	/// <summary>
	/// The ship the Rigidbody is attached to
	/// </summary>
	PhysicsObject* m_ship = nullptr;
	/// <summary>
	/// Has the ship you are attached to collided with anything
	/// </summary>
	bool shipCollided = false;

	/// <summary>
	/// The position of the Rigidbody in relation to the position of the ship it's attached to
	/// </summary>
	vec2 m_localPos;
	/// <summary>
	/// The x axis position of the Rigidbody in relation to the position of the ship it's attached to
	/// </summary>
	vec2 m_localX;
	/// <summary>
	/// The y axis position of the Rigidbody in relation to the position of the ship it's attached to
	/// </summary>
	vec2 m_localY;
};
