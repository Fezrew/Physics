#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Plane.h"

using namespace std;
using namespace glm;

/// <summary>
/// A declaration of the PhysicsObject class
/// </summary>
class PhysicsObject;

/// <summary>
/// A scene where physics objects interact with each other. You may add and remove physics objects at will.
/// The scene keeps track of all the objects and checks for collisions, determining their shape  in order to do so.
/// This class is in charge of calling all the functions inside the various other classes, and can be cleared of all objects whenever.
/// </summary>
class PhysicsScene
{
public:
	PhysicsScene() { m_gravity = vec2(0, 0); m_timeStep = 0.01f; }

	/// <summary>
	/// Deletes all actors in the scene
	/// </summary>
	~PhysicsScene();

	/// <summary>
	/// Adds a physics object to the scene as an actor
	/// </summary>
	/// <param name="actor">The object to be added</param>
	void addActor(PhysicsObject* actor);

	/// <summary>
	/// Removes a physics object from the scene
	/// </summary>
	/// <param name="actor">The object to be removed</param>
	void removeActor(PhysicsObject* actor);

	/// <summary>
	/// Updates all the actors in the scene and checks for collisions
	/// </summary>
	/// <param name="dt">The time between frames</param>
	void update(float dt);

	/// <summary>
	/// Draws all the actors in the scene's list of actors
	/// </summary>
	void draw();
	
	/// <summary>
	/// Removes all the actors in the scene's list of actors
	/// </summary>
	void clear() { m_actors.clear(); }

	static vec2 getGravity() { return m_gravity; }
	void setGravity(const vec2 gravity) { m_gravity = gravity; }
	float getTotalEnergy();
	float getTimeStep() const { return m_timeStep; }
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }

#pragma region Collisions
	/// <summary>
	/// Looks at every actor's size and position to determine collisions
	/// </summary>
	void checkForCollision();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="body1">The first body of the collision</param>
	/// <param name="body2">The second body of the collision</param>
	/// <param name="norm">The normal of the first bodies point of contact</param>
	/// <param name="pen">The amount one object has penetrated the other</param>
	static void ApplyContactForces(RigidBody* body1, RigidBody* body2, vec2 norm, float pen);

	/// <summary>
	/// The collision between planes
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between planes and spheres
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between planes and boxs
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool plane2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between spheres and planes
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between spheres
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between spheres and boxes
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between boxes and planes
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool box2Plane(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between boxes and spheres
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between boxes
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static bool box2Box(PhysicsObject* obj1, PhysicsObject* obj2);

	/// <summary>
	/// The collision between ships
	/// </summary>
	/// <param name="obj1">The first object in the collision</param>
	/// <param name="obj2">The second object in the collision</param>
	static void shipCollision(RigidBody* obj1, RigidBody* obj2);
#pragma endregion

protected:
	/// <summary>
	/// The gravity of the scene
	/// </summary>
	static vec2 m_gravity;

	/// <summary>
	/// The time between fixed updates
	/// </summary>
	float m_timeStep;

	/// <summary>
	/// The list of actors in the scene
	/// </summary>
	vector<PhysicsObject*> m_actors;
};