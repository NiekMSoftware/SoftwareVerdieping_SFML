#include <Application.hpp>

// State inclusions
#include "GameStates/States/GameState.h"
#include "GameStates/States/TitleState.h"

Application::Application()
: mWindow(sf::VideoMode(640, 480), "Pong"),
TimePerFrame(sf::seconds(1.f / 60)),
mStateStack(State::Context(mWindow, mTextures, mFontHolder, mPaused)),
mPaused(false)
{
	// Load in the resources and register all states.
	LoadResources();
	RegisterStates();

	// Push in the Title State
	mStateStack.PushState(States::Title);
	mStateStack.ApplyPendingChanges();
}

void Application::LoadResources()
{
	// First load in the textures.
	printf("\nApplication::LoadResources - Textures:\n");
	mTextures.Load(Textures::Title, "Engine/assets/textures/koseki_bijou.png");

	// Load in the font
	printf("\n");
	mFontHolder.Load(Fonts::Default, "Engine/assets/fonts/pixelFont.ttf");
}

void Application::RegisterStates()
{
	mStateStack.RegisterState<TitleState>(States::Title);
	mStateStack.RegisterState<GameState>(States::Game);
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
