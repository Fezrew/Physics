#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Plane.h"

using namespace std;
using namespace glm;

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene() { m_gravity = vec2(0, 0); m_timeStep = 0.01f; }
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void draw();

	void setGravity(const vec2 gravity) { m_gravity = gravity; }
	static vec2 getGravity() { return m_gravity; }
	float getTotalEnergy();

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	static bool plane2Plane(PhysicsObject*, PhysicsObject*); 
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool plane2Box(PhysicsObject*, PhysicsObject*);
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool sphere2Box(PhysicsObject*, PhysicsObject*);
	static bool box2Plane(PhysicsObject*, PhysicsObject*);
	static bool box2Sphere(PhysicsObject*, PhysicsObject*);
	static bool box2Box(PhysicsObject*, PhysicsObject*);

protected:
	static vec2 m_gravity;
	float m_timeStep;
	vector<PhysicsObject*> m_actors;
};