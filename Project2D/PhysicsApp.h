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
	PhysicsApp();
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
	/// This function is called every frame
	/// </summary>
	/// <param name="deltaTime">The time between frames</param>
	virtual void update(float deltaTime);

	/// <summary>
	/// Draws all the objects in the current scene
	/// </summary>
	virtual void draw();

	/// <summary>
	/// Creates a new ship object and gives it a body
	/// </summary>
	/// <param name="position">The global position of the ship's centre</param>
	/// <param name="orientation">The starting orientation of the ship and all its parts</param>
	/// <param name="colour">The colour of the ship and all of its parts</param>
	/// <param name="inputLeft">Pressing this key turns the ship anti-clockwise</param>
	/// <param name="inputRight">Pressing this key turns the ship clockwise</param>
	/// <param name="boostInput">Pressing this key makes the ship 20% faster</param>
	void createShip(vec2 position, float orientation, vec4 colour, EInputCodes inputLeft, EInputCodes inputRight, EInputCodes boostInput);

	/// <summary>
	/// Starts a new ship-fighting scene
	/// </summary>
	void shipScene();

	/// <summary>
	/// Starts a new physics sandbox scene
	/// </summary>
	void sandboxScene();

protected:

	/// <summary>
	/// Renders all the actors in the scene
	/// </summary>
	aie::Renderer2D* m_2dRenderer;

	/// <summary>
	/// The font of all the text in the physics app
	/// </summary>
	aie::Font* m_font;

	/// <summary>
	/// The currently active physics scene
	/// </summary>
	PhysicsScene* m_physicsScene;

	/// <summary>
	/// The total amount of time passed in the application
	/// </summary>
	float m_timer;
};