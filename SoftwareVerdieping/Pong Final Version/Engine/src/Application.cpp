#include "Application.hpp"

// state inclusion
#include "States/GameOver.h"
#include "States/GameState.h"
#include "States/PauseState.h"
#include "States/TitleState.h"

Application::Application()
:mWindow(sf::VideoMode(800, 600), "Pong"),
mTimePerFrame(sf::seconds(1.f / 60)),
deltaTime(sf::Time::Zero),
fixedDeltaTime(sf::Time::Zero),
mStack(State::Context(mWindow, mPlayerTextures, mFontHolder, mPaused))
{
	// set frame rate to 60
	mWindow.setFramerateLimit(60);

	LoadResources();

	// get the icon
	sf::Image icon;
	if (!icon.loadFromFile("Engine/assets/textures/koseki_bijou.png"))
		throw std::runtime_error("Loading icon failed!");

	// set the icon
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	RegisterStates();

	mStack.PushState(States::TITLE);
	mStack.ApplyPendingChanges();
}

void Application::LoadResources()
{
	// load in fonts
	mFontHolder.Load(Fonts::DEFAULT_FONT, "Engine/assets/fonts/default_font.ttf");
	mFontHolder.Load(Fonts::DEFAULT_BOLD, "Engine/assets/fonts/default_bold.ttf");

	// load in textures
	mPlayerTextures.Load(Textures::BIJOU, "Engine/assets/textures/koseki_bijou.png");
}

void Application::RegisterStates()
{
	// Register the title, game and pause states.
	mStack.RegisterState<TitleState>(States::TITLE);
	mStack.RegisterState<GameState>(States::GAME);
	mStack.RegisterState<PauseState>(States::PAUSE);
	mStack.RegisterState<GameOver>(States::GAME_OVER);
}

void Application::CalculateDeltaTimes()
{
	// Define a time obejct that restarts the clock each iteration.
	sf::Time elapsedTime = mClock.restart();

	// add this elapsed time to the delta time and fixedDeltaTime
	deltaTime = elapsedTime;
	fixedDeltaTime += elapsedTime;
}

void Application::Run()
{
	// Run the application whilst the window is open
	// and there are items within the stack. This ensures the window closing
	// once there are no items in the stack left.
	while (mWindow.isOpen() && !mStack.IsEmpty())
	{
		// Handle any incoming events beforehand.
		HandleEvent();

		// Calculate all the Deltatimes
		CalculateDeltaTimes();

		// Run a loop for the fixed update.
		while (fixedDeltaTime > mTimePerFrame)
		{
			HandleEvent();
			FixedUpdate(mTimePerFrame);
			fixedDeltaTime -= mTimePerFrame;
		}

		// Update the game regurarly.
		Update(deltaTime);

		// Display the stack's content
		Display();
	}
}

void Application::Update(sf::Time dt)
{
	// Update the stack.
	mStack.Update(dt);
}

void Application::FixedUpdate(sf::Time fixedDt)
{
	// Update the stack in a fixed interval.
	mStack.FixedUpdate(fixedDt);
}

void Application::HandleEvent()
{
	sf::Event event;

	// Handle events in the stack.
	while (mWindow.pollEvent(event))
	{
		mStack.HandleEvent(event);
	}
}

void Application::Display()
{
	// Display the states of the stack.
	mStack.Display();
}
