#include "Box.h"

Box::Box(vec2 position, vec2 velocity, float angularVelocity, float orientation, float mass, vec4 colour, float width, float height)
	: RigidBody(BOX, position, velocity, angularVelocity, 1.0f / 12.0f * mass * width * height, orientation, mass, colour), m_extents(width / 2.0f, height / 2.0f)
{

}

Box::~Box()
{
}

bool Box::checkBoxCorners(const Box& box, vec2& contact, int& numContacts, float& pen, vec2& edgeNormal)
{
	float minX, maxX, minY, maxY;
	float boxW = box.m_extents.x * 2;
	float boxH = box.m_extents.y * 2;
	int numLocalContacts = 0;
	vec2 localContact(0, 0);
	bool first = true;

	// loop over all corners of the other box
	for (float x = -box.m_extents.x; x < boxW; x += boxW)
	{
		for (float y = -box.m_extents.y; y < boxH; y += boxH)
		{
			// get the position in worldspace
			glm::vec2 p = box.m_position + x * box.m_localX + y * box.m_localY;
			// get the position in our box's space
			vec2 p0(dot(p - m_position, m_localX), dot(p - m_position, m_localY));

			// update the extents in each cardinal direction in our box's space
			// (ie extents along the separating axes)
			if (first || p0.x < minX) minX = p0.x;
			if (first || p0.x > maxX) maxX = p0.x;
			if (first || p0.y < minY) minY = p0.y;
			if (first || p0.y > maxY) maxY = p0.y;

			// if this corner is inside the box, add it to the list of contact points
			if (p0.x >= -m_extents.x && p0.x <= m_extents.x && p0.y >= -m_extents.y && p0.y <= m_extents.y)
			{
				numLocalContacts++;
				localContact += p0;
			}
			first = false;
		}
	}

	// if we lie entirely to one side of the box along one axis, we've found a separating axis, and we can exit
	if (maxX <= -m_extents.x || minX >= m_extents.x || maxY <= -m_extents.y || minY >= m_extents.y || numLocalContacts == 0)
	{
		return false;
	}

	bool res = false;
	contact += m_position + (localContact.x * m_localX + localContact.y * m_localY) / (float)numLocalContacts;
	numContacts++;

	// find the minimum penetration vector as a penetration amount and normal
	float pen0 = m_extents.x - minX;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = m_localX;
		pen = pen0;
		res = true;
	}
	pen0 = maxX + m_extents.x;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = -m_localX;
		pen = pen0;
		res = true;
	}
	pen0 = m_extents.y - minY;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = m_localY;
		pen = pen0;
		res = true;
	}
	pen0 = maxY + m_extents.y;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = -m_localY;
		pen = pen0;
		res = true;
	}

	return res;
}


void Box::draw()
{
	vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
	vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}
