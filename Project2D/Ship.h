#pragma once
#include "RigidBody.h"
#include <vector>

class Ship : PhysicsObject
{
public:
	Ship(vec2 position, float acceleration, float speedCap, float orientation);
	~Ship();

	void fixedUpdate(vec2 gravity, float timeStep);
	void applyForce(vec2 force);
	void addToShip(RigidBody* rb);

	vec2 getVelocity() { return m_velocity; }
	float getSpeed() { return m_acceleration; }
	float getMass() { return m_mass; }

	vec4 getColour() { return m_colour; }

protected:
	vec2 m_position;
	vec2 m_velocity;
	float m_acceleration;
	float m_speedCap;
	float m_mass;
	float m_orientation;
	vec4 m_colour;

	vector<RigidBody*> shipParts;
};

