#include <Application.hpp>

// State inclusions
#include "GameStates/States/TitleState.h"

Application::Application()
: mWindow(sf::VideoMode(640, 480), "Pong"),
TimePerFrame(sf::seconds(1.f / 60)),
mStateStack(State::Context(mWindow))
{
	RegisterStates();

	// Push in the Title State
	mStateStack.PushState(States::Title);
	mStateStack.ApplyPendingChanges();
}

void Application::RegisterStates()
{
	mStateStack.RegisterState<TitleState>(States::Title);	
}

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

		// Close once the stack is empty
		if (mStateStack.IsEmpty())
			mWindow.close();
	}
}

void Application::ProcessInput()
{
	sf::Event event;

	while(mWindow.pollEvent(event))
	{
		// Let the Stack handle any events.
		mStateStack.HandleEvent(event);
	}
}

void Application::Update(sf::Time deltaTime)
{
	// Update the Stack.
	mStateStack.Update(deltaTime);
}

void Application::Display()
{
	// Display the Stack.
	mStateStack.Display();
}
