#pragma once
#include "PhysicsScene.h"
#include <vector>

/// <summary>
/// A class that creates spheres in a shape and connects them with strings
/// </summary>
class SoftBody
{
public:
	/// <summary>
	/// Builds a softbody in a scene of your choice
	/// </summary>
	/// <param name="scene">The scene the softbody is being made in</param>
	/// <param name="position">The position of the softbody</param>
	/// <param name="spacing">The spacing between each node of the softbody</param>
	/// <param name="springForce">The restoring force of all the springs in the softbody</param>
	/// <param name="damping">The drag slowing down the restoring force of the springs</param>
	/// <param name="strings">A vector of strings that decide the shape of the softbody</param>
	/// <param name="colour">The colour of the softbody</param>
	static void Build(PhysicsScene* scene, vec2 position, float spacing, float springForce, float damping, vector<string>& strings, vec4 colour);
};

