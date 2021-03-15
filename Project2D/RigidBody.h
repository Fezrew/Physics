#pragma once
#include "PhysicsObject.h"
#include <iostream>

using namespace std;

const float MIN_LINEAR_THRESHOLD = 0.001469f;
const float MIN_ANGULAR_THRESHOLD = 0.4f;

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, vec2 position, vec2 velocity, float angularVelocity, float moment, float orientation, float mass, vec4 colour);
	~RigidBody();

	virtual void fixedUpdate(vec2 gravity, float timeStep);
	virtual void applyForce(vec2 force) {}
	virtual void shipContact(vec2 contact) {}
	virtual void shipBreak() {}
	void applyForce(vec2 force, vec2 pos);
	void resolveCollision(RigidBody* actor2, vec2 contact, vec2* collisionNormal = nullptr, float pen = 0);

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

	void setLocalOrientation(float localOrientation) { m_localOrientation = localOrientation * (pi<float>() / 180.0f); }
	float getLocalOrientation() { return m_localOrientation; }
	void setLocalPos(vec2 localPos) { m_localPos = localPos; }
	vec2 getLocalPos() { return m_localPos; }
	vec2 getLocalX() { return m_localX; }
	vec2 getLocalY() { return m_localY; }
	glm::vec2 toWorld(glm::vec2 localPos);

protected:
	vec2 m_position;
	vec2 m_velocity;
	float m_mass = 0;
	float m_orientation = 0;
	float m_angularVelocity;
	float m_moment;
	float m_linearDrag;
	float m_angularDrag;
	bool m_isKinematic;
	float m_localOrientation;

	PhysicsObject* m_ship = nullptr;

	vec2 m_localPos;
	vec2 m_localX;
	vec2 m_localY;
};
