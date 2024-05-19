#include "States/GameState.h"

GameState::GameState(StateStack& stack, Context& context) 
: State(stack, context)
{

}

void GameState::Draw() const
{
	GetContext().window->clear(sf::Color(34,44,55));

	// display this state only if the game isn't paused.
	// this would ensure the pause state printing on top this state
	if (!mIsPaused)
		GetContext().window->display();
}

bool GameState::Update(sf::Time dt) 
{
	return true;
}

bool GameState::FixedUpdate(sf::Time fixedDt) 
{
	return true;
}

bool GameState::HandleEvent(const sf::Event& event) 
{
	if (event.type == sf::Event::KeyPressed)
	{
		mLastKeyPressed = event.key.code;

		// check if the last key that has been pressed is the ESC key
		if (mLastKeyPressed == sf::Keyboard::Escape)
		{
			// pause the game
			mIsPaused = true;

			// TODO: Push in the Paused State.
		}
	}
	
	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return false;
	}
	
	return true;
}