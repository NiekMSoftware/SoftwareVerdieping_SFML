#pragma once

#include <SFML/Graphics.hpp>

#include "GameStates/StateStack.hpp"

class Application
{
public:
	Application();
	void Run();

private:
	void ProcessInput();
	void Update(sf::Time deltaTime);
	void Display();

	void RegisterStates();
	
private:
	// SFML Callbacks
	sf::RenderWindow mWindow;
	sf::Time TimePerFrame;

	// The Stack of States for the application.
	StateStack mStateStack;
};
