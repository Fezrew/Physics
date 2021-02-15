#include <Gizmos.h>
#include "PhysicsApp.h"
#include "glm/ext.hpp"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Box.h"

using namespace glm;

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
	m_physicsScene->setGravity(vec2(0, -9.8));
	m_physicsScene->setTimeStep(0.01f);
	m_timer = 0;


	Sphere* ball = new Sphere(vec2(20, 0), vec2(11.11f, 0), 0, 0, 1.7f, 2.8f, vec4(1, 0, 0, 1));
	m_physicsScene->addActor(ball);

	Sphere* ball2 = new Sphere(vec2(40, 0), vec2(0), 0, 0, 1.6f, 3, vec4(0, 1, 0, 1));
	m_physicsScene->addActor(ball2);

	Sphere* ball3 = new Sphere(vec2(-50, 30), vec2(-500, -75), 0, 0, 2000.0f, 15, vec4(0, 1, 1, 1));
	m_physicsScene->addActor(ball3);

	Plane* plane = new Plane(vec2(0, 1), -55, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane);

	Plane* plane2 = new Plane(vec2(0, -1), -55, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane2);

	Plane* plane3 = new Plane(vec2(1, 0), -98, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane3);

	Plane* plane4 = new Plane(vec2(-1, 0), -98, vec4(0, 0, 1, 1));
	m_physicsScene->addActor(plane4);

	Box* box = new Box(vec2(0, -20), vec2(0), 0, 10, 20.0f, vec4(1, 0, 1, 1), 5, 3);
	m_physicsScene->addActor(box);

	Box* box2 = new Box(vec2(0, -40), vec2(0, 100), 200, 0, 400.0f, vec4(1, 1, 0, 1), 35, 5);
	m_physicsScene->addActor(box2);


	return true;
}

void PhysicsApp::shutdown()
{
	delete m_font;
	delete m_2dRenderer;
}

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