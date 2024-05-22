#include "States/TitleState.h"

TitleState::TitleState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window)
{ /* Load in any necesary resources inside here. */ }

void TitleState::Draw() const
{
	mWindow->clear();

	/* Draw out the components to the State. */

	mWindow->display();
}

bool TitleState::Update(sf::Time dt)
{
	return false;
}

bool TitleState::FixedUpdate(sf::Time fixedDt)
{
	return false;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	// handle default closing event.
	if (event.type == sf::Event::Closed)
	{
		// request to clear out of all the states.
		RequestStateClear();

		return false;
	}

	// Handle on press events
	if (event.type == sf::Event::KeyPressed)
	{
		// once a key has been pressed, request to pop it.
		RequestStackPop();

		// Request to push in the new state.
		RequestStackPush(States::GAME);

		return false;
	}

	return true;
}
