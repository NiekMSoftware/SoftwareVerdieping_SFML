#include "States/PauseState.h"

PauseState::PauseState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window)
{ /* Load any resources */ }

void PauseState::Draw() const
{
	sf::RenderWindow& window = *GetContext().window;

	// Set the background shape
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	backgroundShape.setPosition(0, 0);

	window.draw(backgroundShape);

	window.display();
}

bool PauseState::Update(sf::Time deltaTime)
{
	return true;
}

bool PauseState::FixedUpdate(sf::Time fixedDeltaTime)
{
	return true;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	return false;
}
