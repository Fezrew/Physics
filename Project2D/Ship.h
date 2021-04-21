#pragma once
#include "RigidBody.h"
#include "Sphere.h"
#include <vector>
#include <math.h>
#include "Input.h"

/// <summary>
/// A physics object that can change by adding and removing different objects. 
/// Ships have multiple important features such as:
/// - The centre-most position of the ship is displayed by a sphere that doesn't interact with physics object.
/// - The ship doesn't start with any parts, so when constructed it will need seperate parts to be added to the scene and then to the ship.
/// - All rigidbodies have a pointer to a ship, both this pointer and a bool are used to determine if collisions are being made with a ship and if both pieces are from different ships.
/// - Rigidbodies can be added and removed from the ship at any point in time.
/// </summary>
class Ship : public PhysicsObject
{
public:
	/// <summary>
	/// The constructor of the ship that allows players to discern different ships and have different controls
	/// </summary>
	/// <param name="position">The position of the centre of the ship</param>
	/// <param name="acceleration">The rate at which the ship builds speed</param>
	/// <param name="speedCap">The fastest speed the ship can go</param>
	/// <param name="turnSpeed">The speed that the ship rotates at</param>
	/// <param name="orientation">The direction the ship is facing</param>
	/// <param name="colour">The colour of every object that is added to the ship</param>
	/// <param name="inputLeft">The key input used to turn the ship left</param>
	/// <param name="inputRight">The key input used to turn the ship right</param>
	/// <param name="boostInput">The key input used to make the ship 20% faster</param>
	Ship(vec2 position, float acceleration, float speedCap, float turnSpeed, float orientation, vec4 colour, aie::EInputCodes inputLeft, aie::EInputCodes inputRight, aie::EInputCodes boostInput);
	~Ship();

	/// <summary>
	/// An update called independantly regardless of frame rate
	/// </summary>
	/// <param name="gravity">The gravity of the physics application</param>
	/// <param name="timeStep">The time between every fixed update</param>
	virtual void fixedUpdate(vec2 gravity, float timeStep);

	/// <summary>
	/// Draws a sphere in the exact centre of the ship
	/// </summary>
	virtual void draw();

	/// <summary>
	/// Adds a RigidBody to the ship by making it maintain it's current position and orientation relative to the ship's
	/// </summary>
	/// <param name="rb">The RigidBody being added to the ship</param>
	/// <param name="localPos">The object's position relative to the ship's</param>
	/// <param name="localOri">The object's orientation relative to the ship's</param>
	void addToShip(RigidBody* rb, vec2 localPos, float localOri);

	/// <summary>
	/// Removes a RigidBody from the ship and turns it back to a normal object
	/// </summary>
	/// <param name="rb">The RigidBody being removed from the ship</param>
	void removeFromShip(RigidBody* rb);

	/// <summary>
	/// Continuously moves the ship with a force divided by its mass
	/// </summary>
	/// <param name="force">The acceleration of the ship multiplied by its orientation</param>
	virtual void shipMove(vec2 force);

	/// <summary>
	/// Makes sure objects in the ship stay together when a collision happens
	/// </summary>
	/// <param name="contact">The point of contact between the ship and another object</param>
	virtual void shipContact(vec2 contact);

	/// <summary>
	/// Removes all the objects in the ship when it breaks
	/// </summary>
	virtual void shipBreak();

	virtual void setPosition(vec2 position) { m_position = position; }
	virtual vec2 getPosition() { return m_position; }
	vec2 getVelocity() { return m_velocity; }
	float getSpeed() { return m_acceleration; }
	virtual float getMass() { return m_mass; }
	float getOrientation() { return m_orientation; }
	float getturnSpeed() { return m_turnSpeed; }
	vec4 getColour() { return m_colour; }

protected:

	/// <summary>
	/// The position of the centre of the ship
	/// </summary>
	vec2 m_position;

	/// <summary>
	/// The velocity of the ship
	/// </summary>
	vec2 m_velocity;

	/// <summary>
	/// The rate at which the ship builds up speed
	/// </summary>
	float m_acceleration;

	/// <summary>
	/// The fastest possible speed of the ship
	/// </summary>
	float m_speedCap;

	/// <summary>
	/// The amount of speed gained by the ship when the boost input is pressed
	/// </summary>
	float m_boostSpeed;

	/// <summary>
	/// The mass of the ship
	/// </summary>
	float m_mass;

	/// <summary>
	/// The rotation of the controller of the ship
	/// </summary>
	float m_orientation;

	/// <summary>
	/// Makes the ship parts follow the ship controller's orientation
	/// </summary>
	vec2 shipPartOrientation;

	/// <summary>
	/// The turning speed of the ship
	/// </summary>
	float m_turnSpeed;

	/// <summary>
	/// The colour of all the ship's parts
	/// </summary>
	vec4 m_colour;

	/// <summary>
	/// The input required to rotate the ship left
	/// </summary>
	aie::EInputCodes m_left;

	/// <summary>
	/// The input required to rotate the ship right
	/// </summary>
	aie::EInputCodes m_right;

	/// <summary>
	/// The input required to increase the speed of the ship
	/// </summary>
	aie::EInputCodes m_boost;

	/// <summary>
	/// Allows inputs to occur
	/// </summary>
	Input* input;

	/// <summary>
	/// The visual display of the centre of the ship
	/// </summary>
	Sphere* ball;

	/// <summary>
	/// A list of all the RigidBodies that build up the ship
	/// </summary>
	vector<RigidBody*> shipParts;

	/// <summary>
	/// Says if the ship should break as a result of a collision
	/// </summary>
	bool shipBroke = false;
};

