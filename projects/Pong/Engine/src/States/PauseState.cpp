#include "States/PauseState.h"

PauseState::PauseState(StateStack& stack, const Context& context)
: State(stack, context)
{
	sf::Font& font = context.fonts->Get(Fonts::DEFAULT);
	sf::Vector2f windowSize(context.window->getSize());

}

void PauseState::Draw() const
{

}

bool PauseState::Update(sf::Time dt)
{
	return true;
}

bool PauseState::FixedUpdate(sf::Time fixedDt)
{
	return true;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	return true;
}
