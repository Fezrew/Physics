#include "Rope.h"
#include "Spring.h"
#include "Sphere.h"
#include "RigidBody.h"

Rope::Rope(PhysicsScene* scene, int length)
{
	m_scene = scene;
	m_length = length;
	m_spheres = new Sphere * [m_length];
}

void Rope::Build(RigidBody* obj1, RigidBody* obj2)
{
	m_colour = obj1->getColour();

	for (int i = 0; i < m_length; i++)
	{
		Sphere* sphere;
		if (i == 0)
		{
			sphere = new Sphere(vec2(obj1->getPosition().x, obj1->getPosition().y - m_spacing), vec2(), 0, 0, 0.5f, m_linkSize, m_colour);
			ropeStart = sphere;
		}
		else if (i == m_length - 1)
		{
			sphere = new Sphere(vec2(m_spheres[i - 1]->getPosition().x, m_spheres[i - 1]->getPosition().y - m_spacing), vec2(), 0, 0, 0.5f, m_linkSize, m_colour);
			ropeEnd = sphere;
		}
		else
		{
			sphere = new Sphere(vec2(m_spheres[i - 1]->getPosition().x, m_spheres[i - 1]->getPosition().y - m_spacing), vec2(), 0, 0, 0.5f, m_linkSize, m_colour);
		}
		sphere->setRope(true);
		m_spheres[i] = sphere;
		m_scene->addActor(m_spheres[i]);
	}

	for (int i = 0; i < m_length; i++)
	{
		if (i == 0)
		{
			m_scene->addActor(new Spring(obj1, ropeStart, m_spacing, m_springForce, m_damping, m_colour));
			m_scene->addActor(new Spring(m_spheres[i], m_spheres[i + 1], m_spacing, m_springForce, m_damping, m_colour));
		}
		else if (i == m_length - 1)
		{
			//m_scene->addActor(new Spring(m_spheres[i], m_spheres[i - 1], m_spacing, m_springForce, m_damping, m_colour));
			m_scene->addActor(new Spring(ropeEnd, obj2, m_spacing, m_springForce, m_damping, m_colour));
		}
		else
		{
			//m_scene->addActor(new Spring(m_spheres[i], m_spheres[i - 1], m_spacing, m_springForce, m_damping, m_colour));
			m_scene->addActor(new Spring(m_spheres[i], m_spheres[i + 1], m_spacing, m_springForce, m_damping, m_colour));
		}
	}
}