#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"
#include "States/StateStack.hpp"

class Application {

public:
	Application();

	void Run();

private:
	void Update(sf::Time dt);
	void FixedUpdate(sf::Time fixedDt);

	void HandleEvent();
	void Display();

	void LoadResources();
	void RegisterStates();
	void CalculateDeltaTimes();

private:
	// SFML components
	sf::RenderWindow mWindow; //!< The window of the engine.
	sf::Time mTimePerFrame; //!< Fixed time interval.

	// DeltaTime components
	sf::Time deltaTime; //!< Normal delta Time of the engine.
	sf::Time fixedDeltaTime; //!< Fixed delta time of the engine.
	sf::Clock mClock;

	// State stack
	StateStack mStack; //!< The stack of states, used throughout the Engine.

	// Resources
	PlayerTextures mPlayerTextures; //!< The resource holder of the Player textures.
	FontHolder mFontHolder; //!< The resource holder of the fonts.

	bool mPaused = false;
};
