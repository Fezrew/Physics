#include <Gizmos.h>
#include "PhysicsApp.h"
#include "glm/ext.hpp"
#include "Texture.h"
#include "Font.h"
#include "Sphere.h"
#include "Box.h"
#include "Spring.h"
#include "SoftBody.h"
#include "Ship.h"
#include "Rope.h"

using namespace glm;
using namespace aie;

#pragma region Starting/Closing Application
PhysicsApp::PhysicsApp()
{
}
PhysicsApp::~PhysicsApp()
{

}

bool PhysicsApp::startup()
{
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(vec2(0, 0));
	m_physicsScene->setTimeStep(0.01f);
	m_timer = 0;

	//sandboxScene();
	shipScene();

	return true;
}

void PhysicsApp::shipScene()
{
	m_physicsScene->clear();

	Plane* plane = new Plane(vec2(0, 1), -55, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane);

	Plane* plane2 = new Plane(vec2(0, -1), -55, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane2);

	Plane* plane3 = new Plane(vec2(1, 0), -98, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane3);

	Plane* plane4 = new Plane(vec2(-1, 0), -98, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane4);

	createShip(vec2(-40, 0), 0, vec4(1, 0, 0, 1), EInputCodes(INPUT_KEY_A), EInputCodes(INPUT_KEY_D), EInputCodes(INPUT_KEY_W));
	createShip(vec2(40, 0), 180, vec4(0, 1, 0, 1), EInputCodes(INPUT_KEY_LEFT), EInputCodes(INPUT_KEY_RIGHT), EInputCodes(INPUT_KEY_UP));
}

void PhysicsApp::sandboxScene()
{
	m_physicsScene->clear();

	Plane* plane = new Plane(vec2(0, 1), -55, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane);

	Plane* plane2 = new Plane(vec2(0, -1), -55, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane2);

	Plane* plane3 = new Plane(vec2(1, 0), -98, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane3);

	Plane* plane4 = new Plane(vec2(-1, 0), -98, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane4);

	Sphere* ball = new Sphere(vec2(-20, 0), vec2(11.11f, 0), 0, 0, 1.7f, 2.8f, vec4(1, 0, 0, 1));
	m_physicsScene->addActor(ball);

	Sphere* ball2 = new Sphere(vec2(-40, 50), vec2(0, 800), 0, 0, 1.6f, 3, vec4(0, 1, 0, 1));
	m_physicsScene->addActor(ball2);

	Sphere* ball3 = new Sphere(vec2(-50, 30), vec2(-500, -75), 0, 0, 2000.0f, 15, vec4(0, 1, 1, 1));
	m_physicsScene->addActor(ball3);

	Sphere* ball4 = new Sphere(vec2(20, 0), vec2(0, 0), 0, 0, 1.7f, 2.8f, vec4(1, 0, 0, 1));
	m_physicsScene->addActor(ball4);
	ball4->setKinematic(true);

	Sphere* ball5 = new Sphere(vec2(40, -50), vec2(0, 0), 0, 0, 1.6f, 3, vec4(0, 1, 0, 1));
	m_physicsScene->addActor(ball5);

	m_physicsScene->addActor(new Spring(ball4, ball5, 25, 2, 0.1f, vec4(1, 0, 0, 1)));

	Box* box = new Box(vec2(0, -20), vec2(0), 0, 10, 20.0f, vec4(1, 0, 1, 1), 5, 3);
	m_physicsScene->addActor(box);

	Box* box2 = new Box(vec2(0, -40), vec2(0, 100), 200, 0, 400.0f, vec4(1, 1, 0, 1), 35, 5);
	m_physicsScene->addActor(box2);

	Box* wall = new Box(vec2(30, -10), vec2(0, 0), 0, 0, 400.0f, vec4(1, 1, 1, 1), 40, 5);
	m_physicsScene->addActor(wall);
	wall->setKinematic(true);

	Box* wall2 = new Box(vec2(90, -50), vec2(0, 0), 0, 0, 400.0f, vec4(1, 1, 1, 1), 3, 3);
	m_physicsScene->addActor(wall2);
	wall2->setKinematic(true);

	vector<std::string> sb;
	sb.push_back("0.....");
	sb.push_back("0.....");
	sb.push_back("0.....");
	sb.push_back("0.....");
	sb.push_back("0.....");
	sb.push_back("0.....");
	sb.push_back("0.....");
	SoftBody::Build(m_physicsScene, vec2(50, -30), 5.0f, 10.0f, 0.1, sb, vec4(1, 0, 0, 1));
}

void PhysicsApp::shutdown()
{
	delete m_font;
	delete m_2dRenderer;
}
#pragma endregion

void PhysicsApp::update(float deltaTime)
{

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Least Janky Game", 0, 720 - 64);

	char timer[32];
	sprintf_s(timer, 32, "Time elapsed: %i", (int)m_timer);
	m_2dRenderer->drawText(m_font, timer, 160, 720 - 32);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsApp::createShip(vec2 position, float orientation, vec4 colour, EInputCodes inputLeft, EInputCodes inputRight, EInputCodes boostInput)
{
	Ship* ship = new Ship(position, 50, 25, 1.5f, orientation, colour, inputLeft, inputRight, boostInput);
	m_physicsScene->addActor(ship);

	Box* shipBox = new Box(vec2(0, 0), vec2(0), 0, 0, 20.0f, colour, 4, 4);
	m_physicsScene->addActor(shipBox);
	ship->addToShip(shipBox, vec2(0, 0), 0);

	Box* shipBox2 = new Box(vec2(0, 0), vec2(0), 0, 0, 20.0f, colour, 2.8f, 2.8f);
	m_physicsScene->addActor(shipBox2);
	ship->addToShip(shipBox2, vec2(2, 2), 45);


	Sphere* wreckingBall = new Sphere(vec2(0, 0), vec2(0, 0), 0, 0, 40.0f, 5, colour);
	m_physicsScene->addActor(wreckingBall);
	ship->addToShip(wreckingBall, vec2(-20, -20), 0);
	ship->removeFromShip(wreckingBall);

	Rope* rope = new Rope(m_physicsScene, 12);
	rope->Build(shipBox, wreckingBall);
}


