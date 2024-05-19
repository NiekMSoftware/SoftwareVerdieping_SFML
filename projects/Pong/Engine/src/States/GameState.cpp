#include "States/GameState.h"

GameState::GameState(StateStack& stack, Context& context) 
: State(stack, context)
{

}

void GameState::Draw() const
{

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
	return true;
}