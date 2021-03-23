#pragma once
#include "PhysicsScene.h"
#include "Sphere.h"
#include <vector>

class Rope
{
public:
	void Build(PhysicsScene* scene, vec2 position, float spacing, float springForce, float damping, int length, vec4 colour);

protected:
	vector<Sphere*> spheres;
};
