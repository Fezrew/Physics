#include "PhysicsScene.h"
#include "Sphere.h"

vec2 PhysicsScene::m_gravity;

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	auto it = find(m_actors.begin(), m_actors.end(), actor);
	if (it != m_actors.end())
	{
		m_actors.erase(it);
	}
}

void PhysicsScene::update(float dt)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		int actorCount = m_actors.size();

		checkForCollision();
	}
}

void PhysicsScene::draw()
{
	for (auto pActor : m_actors)
	{
		pActor->draw();
	}
}

float PhysicsScene::getTotalEnergy()
{
	float total = 0;
	for (auto it = m_actors.begin(); it != m_actors.end(); it++)
	{
		PhysicsObject* obj = *it;
		total += obj->getEnergy();
	}

	return total;
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

#pragma region Collisions

static fn collisionFunctionArray[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2Box,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2Box,
	PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2Box
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	//Check for collisions against all objects but this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			//Function pointer time
			int functionIDx = (shapeID1 * SHAPE_COUNT) + shapeID2;

			fn collisionFunctionPtr = collisionFunctionArray[functionIDx];
			if (collisionFunctionPtr != nullptr)
			{
				//Did a collision occur
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// reverse the order of arguments, as obj1 is the plane and obj2 is the sphere
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if (sphere != nullptr && plane != nullptr)
	{
		vec2 collisionNormal = plane->getNormal(); 

		float sphereToPlane = dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance(); 
		float intersection = sphere->getRadius() - sphereToPlane; 
		float velocityOutOfPlane = dot(sphere->getVelocity(), plane->getNormal()); 
		
		if (intersection > 0 && velocityOutOfPlane < 0) 
		{
			plane->resolveCollision(sphere);

			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) <= sphere1->getRadius() + sphere2->getRadius())
		{
			sphere1->resolveCollision(sphere2);

			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}
#pragma endregion
