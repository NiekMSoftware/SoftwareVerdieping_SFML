#pragma once

#include <SFML/Graphics.hpp>

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

private:
	// sfml properties required.
	sf::RenderWindow mWindow; //!< The window of the Application.
	sf::Time TimePerFrame; //!< Time for how long a frame should take.
};
