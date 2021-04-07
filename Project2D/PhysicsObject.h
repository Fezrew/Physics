#pragma once
#include <vector>
#include<glm/glm.hpp>
#include "glm/ext.hpp"
#include <Gizmos.h>


using namespace glm;
using namespace aie;

/// <summary>
/// A value assigned to each object to determine the method of collision
/// </summary>
enum ShapeType
{ 
	SHIP = -2,
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

/// <summary>
/// An object that interacts with other physics objects
/// </summary>
class PhysicsObject
{
protected:
	/// <summary>
	/// The shape of the object
	/// </summary>
	ShapeType m_shapeID;

	/// <summary>
	/// The colour of the object
	/// </summary>
	vec4 m_colour;

public:
	/// <summary>
	/// Assigns deriving objects their shape ID and colour through their own constructors
	/// </summary>
	/// <param name="a_shapeID">The shape of the object</param>
	/// <param name="colour">The colour of the object</param>
	PhysicsObject(ShapeType a_shapeID, vec4 colour) : m_shapeID(a_shapeID), m_colour(colour) {}

	/// <summary>
	/// An update called independantly regardless of frame rate
	/// </summary>
	/// <param name="gravity">The gravity of the physics application</param>
	/// <param name="timeStep">The time between every fixed update</param>
	virtual void fixedUpdate(vec2 gravity, float timeStep) = 0;

	/// <summary>
	/// A virtual function that gets overrided by deriving classes
	/// </summary>
	virtual void draw() = 0;

	/// <summary>
	/// A virtual function that gets overrided by deriving classes
	/// </summary>
	virtual void resetPosition() {};

	/// <summary>
	/// A virtual function that gets overrided by deriving classes
	/// </summary>
	virtual void shipMove(vec2 force) = 0;

	/// <summary>
	/// A virtual function that gets overrided by the ship class
	/// </summary>
	virtual void shipContact(vec2 contact) = 0;

	/// <summary>
	/// A virtual function that gets overrided by the ship class
	/// </summary>
	virtual void shipBreak() = 0;

	virtual float getEnergy() { return 0; }
	virtual void setColour(vec4 colour) { m_colour = colour; }
	virtual float getMass() = 0;
	virtual vec2 getPosition() = 0;
	virtual void setPosition(vec2 position) = 0;
	vec4 getColour() { return m_colour; }
	ShapeType getShapeID() { return m_shapeID; }
};

