#pragma once
#include <vector>
#include<glm/glm.hpp>
#include "glm/ext.hpp"
#include <Gizmos.h>


using namespace glm;
using namespace aie;

enum ShapeType
{ 
	SHIP = -2,
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	ShapeType m_shapeID;
	vec4 m_colour;

public:
	PhysicsObject(ShapeType a_shapeID, vec4 colour) : m_shapeID(a_shapeID), m_colour(colour) {}

	virtual void fixedUpdate(vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};
	virtual float getEnergy() { return 0; }
	virtual void setColour(vec4 colour) { m_colour = colour; }
	virtual void applyForce(vec2 force) = 0;
	virtual float getMass() = 0;
	virtual vec2 getPosition() = 0;
	virtual void setPosition(vec2 position) = 0;
	virtual void shipContact(vec2 contact) = 0;
	virtual void shipBreak() = 0;
	vec4 getColour() { return m_colour; }
	ShapeType getShapeID() { return m_shapeID; }
};

