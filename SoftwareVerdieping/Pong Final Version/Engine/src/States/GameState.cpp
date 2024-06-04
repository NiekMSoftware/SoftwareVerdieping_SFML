#include "States/GameState.h"

GameState::GameState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window)
{ }

void GameState::Draw() const
{
	mWindow->clear(sf::Color(33, 44, 54));

	// Render this state only when the game isn't paused.
	if (!mIsPaused)
		mWindow->display();
}

bool GameState::Update(sf::Time dt)
{
	// Stop updating the state if the game is paused.
	if (mIsPaused)
		return false;

	return true;
}

bool GameState::FixedUpdate(sf::Time fixedDt)
{
	// Stop updating the state if the game is paused.
	if (mIsPaused)
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

	// Handle key presses
	if (event.type == sf::Event::KeyPressed)
	{
		// Handle pausing the game
		if (event.key.code == sf::Keyboard::Escape)
		{
			// set the paused flag to true
			mIsPaused = true;

			// Push in the pause state.
			RequestStackPush(States::PAUSE);

			return true;
		}
	}

	return false;
}
