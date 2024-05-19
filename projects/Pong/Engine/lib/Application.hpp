#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"
#include "States/StateStack.hpp"

class Application
{
public:
	Application();

	void Run();

private:
	void Update(sf::Time deltaTime);
	void FixedUpdate(sf::Time fixedDeltaTime);
	void HandleEvents();
	void Display();

	void LoadTextures();
	void RegisterStates();

private:
	// sfml properties
	sf::RenderWindow mWindow; //!< The window of the Application.
	sf::Time mTimePerFrame; //!< Time for how long a frame should take.

	// The stack of States for the application.
	StateStack mStateStack;

	// Resource Holders
	TextureHolder mTextureHolder; //!< The resource holder of the textures of the engine.
	FontHolder mFontHolder; //!< The resource holder of the Fonts of the engine.

	bool mIsPaused; //!< Flag to pause the game.
};