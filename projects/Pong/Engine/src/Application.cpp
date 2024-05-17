#include "../lib/Application.hpp"

Application::Application()
: mWindow(sf::VideoMode(800, 600), "Pong"),
TimePerFrame(sf::seconds(1.f / 60))
{ }

void Application::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Run application whilst the game is still open.
	while (mWindow.isOpen())
	{
		ProcessInput();
		timeSinceLastUpdate += clock.restart();

		// Run time call back loop
		while (timeSinceLastUpdate > TimePerFrame)
		{
			// Update the game in this callback
			timeSinceLastUpdate -= TimePerFrame;
			ProcessInput();
			Update(TimePerFrame);
		}

		// Display the game.
		Display();
	}
}

void Application::ProcessInput()
{
	sf::Event event;

	while(mWindow.pollEvent(event))
	{
		// close the window if that is being called
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::Update(sf::Time deltaTime)
{
	// nothing to update yet
}

void Application::Display()
{
	mWindow.clear();

	mWindow.display();
}
