#include "States/GameState.h"

GameState::GameState(StateStack& stack, Context& context) 
: State(stack, context)
{

}

void GameState::Draw() const
{
	GetContext().window->clear(sf::Color(34,44,55));

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
	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return false;
	}
	
	return true;
}