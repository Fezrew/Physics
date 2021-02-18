#pragma once
#include "PhysicsScene.h"
#include <vector>

class SoftBody
{
public:
	static void Build(PhysicsScene* scene, vec2 position, float spacing, float springForce, float damping, vector<string>& strings, vec4 colour);
};

