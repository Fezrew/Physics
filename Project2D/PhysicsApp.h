#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Input.h"

using namespace aie;

/// <summary>
/// The application class that allows swapping between scenes
/// </summary>
class PhysicsApp : public aie::Application
{
public:
	/// <summary>
	/// The constructor of the physics application
	/// </summary>
	PhysicsApp();

	/// <summary>
	/// The destructor of the physics application
	/// </summary>
	virtual ~PhysicsApp();

	/// <summary>
	/// When the application begins, this function sets the gravity, time step, and starts the ship scene
	/// </summary>
	virtual bool startup();

	/// <summary>
	/// This function deletes the font and renderer
	/// </summary>
	virtual void shutdown();

	/// <summary>
	/// /this function is called every frame
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void update(float deltaTime);

	/// <summary>
	/// 
	/// </summary>
	virtual void draw();

	/// <summary>
	/// 
	/// </summary>
	void createShip(vec2 position, float orientation, vec4 colour, EInputCodes inputLeft, EInputCodes inputRight, EInputCodes boostInput);

	/// <summary>
	/// 
	/// </summary>
	void shipScene();

	/// <summary>
	/// 
	/// </summary>
	void sandboxScene();

protected:

	/// <summary>
	/// 
	/// </summary>
	aie::Renderer2D* m_2dRenderer;

	/// <summary>
	/// 
	/// </summary>
	aie::Font* m_font;

	/// <summary>
	/// 
	/// </summary>
	PhysicsScene* m_physicsScene;

	/// <summary>
	/// 
	/// </summary>
	float m_timer;
};