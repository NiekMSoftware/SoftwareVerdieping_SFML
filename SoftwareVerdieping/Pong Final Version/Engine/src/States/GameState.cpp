#include "States/GameState.h"

GameState::GameState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window)
{ }

void GameState::Draw() const
{
	mWindow->clear(sf::Color::Red);

	if (!GetContext().paused)
		mWindow->display();
}

bool GameState::Update(sf::Time dt)
{
	// Stop updating the state if the game is paused.
	if (GetContext().paused)
		return false;

	return true;
}

bool GameState::FixedUpdate(sf::Time fixedDt)
{
	// Stop updating the state if the game is paused.
	if (GetContext().paused)
		return false;

	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	// Handle the window closing event
	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return true;
	}

	// // Stop handling the state if the game is paused.
	// if (GetContext().paused)
	// 	return false;

	// Handle key presses
	if (event.type == sf::Event::KeyPressed)
	{
		// Handle pausing the game
		if (event.key.code == sf::Keyboard::Escape)
		{
			// set the paused flag to true
			bool& paused = *GetContext().paused;
			paused = true;

			// TODO: Push in the pause state.

			return true;
		}
	}

	return false;
}
