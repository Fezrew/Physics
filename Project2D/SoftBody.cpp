#include "SoftBody.h"
#include "Sphere.h"
#include "Spring.h"

void SoftBody::Build(PhysicsScene* scene, vec2 position, float spacing, float springForce, float damping, vector<string>& strings, vec4 colour)
{
	int numColumns = strings.size();
	int numRows = strings[0].length();

	// traverse across the array and add balls where the ascii art says they should be
	Sphere** spheres = new Sphere* [numRows * numColumns];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (strings[j][i] == '0')
			{
				spheres[i * numColumns + j] = new Sphere(position + vec2(i, j) * spacing, glm::vec2(0, 0), 0, 0, 1.0f, 1, glm::vec4(1, 0, 0, 1));
				scene->addActor(spheres[i * numColumns + j]);
			}
			else
			{
				spheres[i * numColumns + j] = nullptr;
			}
		}
	}

	// second pass - add springs in
	for (int i = 1; i < numRows; i++)
	{
		for (int j = 1; j < numColumns; j++)
		{
			Sphere* s11 = spheres[i * numColumns + j];
			Sphere* s01 = spheres[(i - 1) * numColumns + j];
			Sphere* s10 = spheres[i * numColumns + j - 1];
			Sphere* s00 = spheres[(i - 1) * numColumns + j - 1];

			bool endOfJ = j == numColumns - 1;
			bool endOfI = i == numRows - 1;

			Sphere* s22 = (!endOfI && !endOfJ) ? spheres[(i + 1) * numColumns + (j + 1)] : nullptr;
			Sphere* s02 = !endOfJ ? spheres[(i - 1) * numColumns + (j + 1)] : nullptr;
			Sphere* s20 = !endOfI ? spheres[(i + 1) * numColumns + j - 1] : nullptr;

			// make springs to cardinal neighbours
			if (s11 && s01)
				scene->addActor(new Spring(s11, s01, spacing, springForce, damping, colour));
			if (s11 && s10)
				scene->addActor(new Spring(s11, s10, spacing, springForce, damping, colour));
			if (s10 && s00)
				scene->addActor(new Spring(s10, s00, spacing, springForce, damping, colour));
			if (s01 && s00)
				scene->addActor(new Spring(s01, s00, spacing, springForce, damping, colour));

			//diagonals
			if (s11 && s00)
				scene->addActor(new Spring(s11, s00, spacing, springForce, damping, colour));
			if (s10 && s01)
				scene->addActor(new Spring(s10, s01, spacing, springForce, damping, colour));



			if (s00 && s02)
				scene->addActor(new Spring(s00, s02, spacing, springForce, damping, colour));
			if (s00 && s20)
				scene->addActor(new Spring(s00, s20, spacing, springForce, damping, colour));
			if (s20 && s22)
				scene->addActor(new Spring(s20, s22, spacing, springForce, damping, colour));
			if (s02 && s22)
				scene->addActor(new Spring(s02, s22, spacing, springForce, damping, colour));
		}
	}
}
