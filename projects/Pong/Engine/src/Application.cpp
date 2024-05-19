#include "../lib/Application.hpp"

Application::Application()
: mWindow(sf::VideoMode(800, 600), "Pong"),
mTimePerFrame(sf::seconds(1.f / 60))
{
	LoadTextures();
}

void Application::LoadTextures()
{
	// Load in the textures
	mTextureHolder.Load(Textures::DEFAULT, "Engine/assets/textures/default_texture.png");

	// Load in the fonts
	mFontHolder.Load(Fonts::DEFAULT, "Engine/assets/fonts/pixel.ttf");
}


void Application::Run()
{
	sf::Clock clock;

	// Elspased time since last frame, used for regular DeltaTime.
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Elapsed time since last frame in a fixed interval, used for fixed DeltaTime.
	sf::Time timeSinceLastFixedUpdate =  sf::Time::Zero;
	
	// Keep running whilst the Window is active.
	while (mWindow.isOpen())
	{
		// Handle any incoming events.
		HandleEvents();

		// Elapsedtime since the clock has restarted.
		sf::Time elapsedTime = clock.restart();
		
		// Calculate the fixed update interval
		timeSinceLastFixedUpdate += elapsedTime;

		// Calculate the update interval
		timeSinceLastUpdate += elapsedTime;

		// Calculate the Fixed Update interval
		while (timeSinceLastFixedUpdate > mTimePerFrame)
		{
			// Update any fixed logic, typically used for Physics simulation or manipulation.
			timeSinceLastFixedUpdate -= mTimePerFrame;

			// Update the Engine on a fixed interval.
			FixedUpdate(mTimePerFrame);
		}

		// Update the Engine with deltaTime
		Update(timeSinceLastUpdate);
		timeSinceLastUpdate = sf::Time::Zero;

		// Display whatever would be needed.
		Display();
	}
}

void Application::Update(sf::Time deltaTime)
{
	
}

void Application::FixedUpdate(sf::Time fixedDeltaTime)
{
	
}

void Application::HandleEvents()
{
	
}

void Application::Display()
{
	mWindow.clear();
	
	mWindow.display();
}