#pragma once

#include <SFML/Graphics.hpp>

#include "GameStates/StateStack.hpp"

class Application
{
public:
	Application();
	void Run();

private:
	void LoadResources();
	
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

	// The resources of the game
	TextureHolder mTextures;
	FontHolder mFontHolder;

	// Boolean to take as reference
	bool mPaused;
};