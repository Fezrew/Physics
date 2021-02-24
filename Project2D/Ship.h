#pragma once
#include "RigidBody.h"
#include "Sphere.h"
#include <vector>
#include <math.h>
#include "Input.h"

class Ship : public PhysicsObject
{
public:
	Ship(vec2 position, float acceleration, float speedCap, float turnSpeed, float orientation, vec4 colour);
	~Ship();

	virtual void fixedUpdate(vec2 gravity, float timeStep);
	virtual void draw();
	virtual void applyForce(vec2 force);
	virtual void setPosition(vec2 position) { m_position = position; }
	virtual vec2 getPosition() { return m_position; }

	void addToShip(RigidBody* rb, vec2 localPos, float localOri);
	virtual void shipContact(vec2 contact);

	vec2 getVelocity() { return m_velocity; }
	float getSpeed() { return m_acceleration; }
	virtual float getMass() { return m_mass; }
	float getOrientation() { return m_orientation; }
	float getturnSpeed() { return m_turnSpeed; }
	vec4 getColour() { return m_colour; }

protected:
	vec2 m_position;
	vec2 m_velocity;
	float m_acceleration;
	float m_speedCap;
	float m_mass;
	float m_orientation;
	vec2 shipOrientation;
	float m_turnSpeed;
	vec4 m_colour;

	Input* input;
	Sphere* ball;
	vector<RigidBody*> shipParts;
};
