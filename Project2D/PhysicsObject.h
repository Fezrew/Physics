#pragma once
#include <vector>
#include<glm/glm.hpp>
#include "glm/ext.hpp"
#include <Gizmos.h>


using namespace glm;

enum ShapeType
{ 
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID, vec4 colour) : m_shapeID(a_shapeID), m_colour(colour) {}
	ShapeType m_shapeID;
	vec4 m_colour;

public:
	virtual void fixedUpdate(vec2 gravity, float timeStep) = 0;
	virtual void draw() = 0;
	virtual void resetPosition() {};
	virtual float getEnergy() { return 0; }
	vec4 getColour() { return m_colour; }
	ShapeType getShapeID() { return m_shapeID; }
};

