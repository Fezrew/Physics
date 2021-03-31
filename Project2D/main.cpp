#include "PhysicsApp.h"

int main() {
	
	// allocation
	auto app = new PhysicsApp();

	// initialise and loop
	app->run("Space Physics", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}