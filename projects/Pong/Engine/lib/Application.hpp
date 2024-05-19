#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.inl"

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

private:
	// sfml properties
	sf::RenderWindow mWindow; //!< The window of the Application.
	sf::Time mTimePerFrame; //!< Time for how long a frame should take.

	// Resource Holders
	TextureHolder mTextureHolder; //!< The resource holder of the textures of the engine.
	FontHolder mFontHolder; //!< The resource holder of the Fonts of the engine.

	// temp sprite
	sf::Sprite mSprite;
};