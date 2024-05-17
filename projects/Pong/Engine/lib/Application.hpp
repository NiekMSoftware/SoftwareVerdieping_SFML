#pragma once

#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	void Run();

private:
	void ProcessInput();
	void Update(sf::Time deltaTime);
	void Display();

private:
	// SFML Callbacks
	sf::RenderWindow mWindow;
	sf::Time TimePerFrame;

	// TODO: Create a StateStack class to manage the states of the game.
};