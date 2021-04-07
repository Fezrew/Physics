#pragma once
#include "RigidBody.h"

/// <summary>
/// A rigidbody with four edges
/// </summary>
class Box : public RigidBody
{
public:
	/// <summary>
	/// Constructs the box and gives it all the values written in the parameters
	/// </summary>
	/// <param name="position">The global position of the box's centre</param>
	/// <param name="velocity">The starting velocity of the object</param>
	/// <param name="angularVelocity">The starting rotational velocity of the object</param>
	/// <param name="orientation">The starting rotation of the object</param>
	/// <param name="mass">The weight of the object</param>
	/// <param name="colour">The colour of the object</param>
	/// <param name="width">The width of the box</param>
	/// <param name="height">The width of the box</param>
	Box(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, vec4 colour, float width, float height);
	~Box();

	vec2 getExtents() { return m_extents; }
	float getWidth() { return m_extents.x * 2; }
	float getHeight() { return m_extents.y * 2; }

	/// <summary>
	/// Calculates the result of a collision between boxes
	/// </summary>
	/// <param name="box">The other box being collided with</param>
	/// <param name="contact">The point of contact bwtween boxes</param>
	/// <param name="numContacts">The amount of positions of contact</param>
	/// <param name="pen">The amount one object has penetrated the other</param>
	/// <param name="edgeNormal">The normal of the edge being collided with</param>
	bool checkBoxCorners(const Box& box, vec2& contact, int& numContacts, float &pen, vec2& edgeNormal);

	/// <summary>
	/// Draws the box by finding the corners with its extents
	/// </summary>
	void draw();

protected:
	/// <summary>
	/// The vector between the centre and a corner of the box
	/// </summary>
	vec2 m_extents;

};

