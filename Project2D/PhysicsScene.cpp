#include "PhysicsScene.h"
#include "Sphere.h"
#include "Box.h"

vec2 PhysicsScene::m_gravity;
float timer = 0;

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
	timer += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		int actorCount = m_actors.size();

		if (timer > 1)
		{
			checkForCollision();
		}

		cout << "Total energy: " << getTotalEnergy() << endl;
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

			if (shapeID1 < 0 || shapeID2 < 0)
			{
				continue;
			}

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

#pragma region Resolution
void PhysicsScene::ApplyContactForces(RigidBody* body1, RigidBody* body2, vec2 norm, float pen)
{
	float body2Mass = body2 ? body2->getMass() : INT_MAX;
	float body1Factor = 0;

	if (body1->isShip())
	{
		body1Factor = body2Mass / (body1->getShip()->getMass() + body2Mass);
		body1->getShip()->shipContact(body1->getShip()->getPosition() - body1Factor * norm * pen);
	}
	else
	{
		body1Factor = body2Mass / (body1->getMass() + body2Mass);
		body1->setPosition(body1->getPosition() - body1Factor * norm * pen);
	}

	if (body2)
	{
		body2->setPosition(body2->getPosition() + (1 - body1Factor) * norm * pen);
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
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		vec2 contact(0, 0);
		float contactV = 0;

		vec2 planeOrigin = plane->getNormal() * plane->getDistance();

		for (float x = -box->getExtents().x; x < box->getWidth(); x += box->getWidth())
		{
			for (float y = -box->getExtents().y; y < box->getHeight(); y += box->getHeight())
			{
				vec2 p = box->getPosition() + x * box->getLocalX() + y * box->getLocalY();
				float distFromPlane = dot(p - planeOrigin, plane->getNormal());

				vec2 displacement = x * box->getLocalX() + y * box->getLocalY();
				vec2 pointVelocity = box->getVelocity() + box->getAngularVelocity() * vec2(-displacement.y, displacement.x);

				float velocityIntoPlane = dot(pointVelocity, plane->getNormal());

				if (distFromPlane < 0 && velocityIntoPlane <= 0)
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}

		if (numContacts > 0)
		{
			plane->resolveCollision(box, contact / (float)numContacts);
			return true;
		}
	}

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
		vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());

		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			plane->resolveCollision(sphere, contact);

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
		if (sphere1->isShip() || sphere2->isShip())
		{
			shipCollision(sphere1, sphere2);
		}
		else
		{
			float dist = distance(sphere1->getPosition(), sphere2->getPosition());
			if (dist <= sphere1->getRadius() + sphere2->getRadius())
			{
				float penetration = sphere1->getRadius() + sphere2->getRadius() - dist;
				if (penetration > 0)
				{
					sphere1->resolveCollision(sphere2, (sphere1->getPosition() + sphere2->getPosition()) * 0.5f, nullptr, penetration);
				}


				return true;
			}
		}
	}

	return false;
}
bool PhysicsScene::sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return box2Sphere(obj2, obj1);;
}

bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return plane2Box(obj2, obj1);
}
bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);

	if (box != nullptr && sphere != nullptr)
	{
		if (box->isShip() || sphere->isShip())
		{
			shipCollision(box, sphere);
		}
		else
		{
			vec2 circlePosWorld = sphere->getPosition() - box->getPosition();
			vec2 circlePosBox = vec2(dot(circlePosWorld, box->getLocalX()), dot(circlePosWorld, box->getLocalY()));

			vec2 closestPointOnBoxBox = circlePosBox;
			vec2 extents = box->getExtents();

#pragma region Clamping
			if (closestPointOnBoxBox.x < -extents.x)
			{
				closestPointOnBoxBox.x = -extents.x;
			}
			if (closestPointOnBoxBox.x > extents.x)
			{
				closestPointOnBoxBox.x = extents.x;
			}
			if (closestPointOnBoxBox.y < -extents.y)
			{
				closestPointOnBoxBox.y = -extents.y;
			}
			if (closestPointOnBoxBox.y > extents.y)
			{
				closestPointOnBoxBox.y = extents.y;
			}
#pragma endregion

			vec2 closestPointOnBoxWorld = box->getPosition() + closestPointOnBoxBox.x * box->getLocalX() + closestPointOnBoxBox.y * box->getLocalY();
			vec2 circleToBox = sphere->getPosition() - closestPointOnBoxWorld;

			float penetration = sphere->getRadius() - glm::length(circleToBox);
			if (penetration > 0)
			{
				vec2 direction = normalize(circleToBox);
				vec2 contact = closestPointOnBoxWorld;
				box->resolveCollision(sphere, contact, &direction, penetration);
			}
		}
	}

	return false;
}
bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);


	if (box1 != nullptr && box2 != nullptr)
	{
		if (box1->isShip() || box2->isShip())
		{
			shipCollision(box1, box2);
		}
		else
		{
			glm::vec2 boxPos = box2->getPosition() - box1->getPosition();
			glm::vec2 norm(0, 0);
			glm::vec2 contact(0, 0);
			float pen = 0;
			int numContacts = 0;

			box1->checkBoxCorners(*box2, contact, numContacts, pen, norm);

			if (box2->checkBoxCorners(*box1, contact, numContacts, pen, norm)) {
				norm = -norm;
			}

			if (pen > 0)
			{
				box1->resolveCollision(box2, contact / float(numContacts), &norm, pen);
			}
			return true;
		}
	}
	return false;

}

void PhysicsScene::shipCollision(RigidBody* obj1, RigidBody* obj2)
{
	if (obj1->isShip() && obj2->isShip())
	{
		if (obj1->getShip() != obj2->getShip())
		{
			if (obj1->getShip()->getMass() < obj2->getShip()->getMass())
			{
				//If ship1 is lighter than ship2
				obj1->getShip()->shipBreak();
			}
			else if (obj2->getShip()->getMass() < obj1->getShip()->getMass())
			{
				//If ship1 is heavier than ship2
				obj2->getShip()->shipBreak();
			}
			else if (obj1->getShip()->getMass() == obj2->getShip()->getMass())
			{
				//If the ships are the same weight
				obj1->getShip()->shipBreak();
				obj2->getShip()->shipBreak();
			}

		}
	}
	else if (obj1->isShip() && obj2->isShip() == false)
	{
		if (obj1->getShip()->getMass() <= obj2->getMass() || obj2->isKinematic())
		{
			//If the object is heavier or as heavy as the ship
			obj1->getShip()->shipBreak();
		}
		else
		{
			//If the object is lighter than the ship

		}
	}
	else if (obj2->isShip() && obj1->isShip() == false)
	{
		if (obj2->getShip()->getMass() <= obj1->getMass() || obj2->isKinematic())
		{
			//If the object is heavier or as heavy as the ship
			obj2->getShip()->shipBreak();
		}
		else
		{
			//If the object is lighter than the ship

		}
	}
}
#pragma endregion
#pragma endregion
