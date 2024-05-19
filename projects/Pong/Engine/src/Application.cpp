#include "../lib/Application.hpp"

Application::Application()
: mWindow(sf::VideoMode(800, 600), "Pong"),
TimePerFrame(sf::seconds(1.f / 60))
{ }

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
		while (timeSinceLastFixedUpdate > TimePerFrame)
		{
			// Update any fixed logic, typically used for Physics simulation or manipulation.
			timeSinceLastFixedUpdate -= TimePerFrame;

			// Update the Engine on a fixed interval.
			FixedUpdate(TimePerFrame);
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
	
}