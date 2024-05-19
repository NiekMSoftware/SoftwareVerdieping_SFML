#include "States/TitleState.h"

TitleState::TitleState(StateStack& stack, Context& context)
: State(stack, context)
{

}

bool TitleState::Update(sf::Time dt) 
{
	return true;
}

bool TitleState::FixedUpdate(sf::Time fixedDt) 
{
	return true;
}

bool TitleState::HandleEvent(const sf::Event& event) 
{
	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return false;
	}
	
	return true;
}

void TitleState::Draw() const
{
	GetContext().window->clear();

	GetContext().window->display();
}