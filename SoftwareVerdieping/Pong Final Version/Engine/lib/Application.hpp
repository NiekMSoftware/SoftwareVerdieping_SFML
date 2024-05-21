#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"

class Application {

public:
	Application();

	void Run();

private:
	void Update(sf::Time dt);
	void FixedUpdate(sf::Time fixedDt);

	void HandleEvent();

	void Display();

	void CalculateDeltaTimes();

private:
	// SFML components
	sf::RenderWindow mWindow; //!< The window of the engine.
	sf::Time mTimePerFrame; //!< Fixed time interval.

	// DeltaTime components
	sf::Time deltaTime; //!< Normal delta Time of the engine.
	sf::Time fixedDeltaTime; //!< Fixed delta time of the engine.
	sf::Clock mClock;

	PlayerTextures mPlayerTextures;
};
