#include <GameStates/States/TitleState.h>
#include <SFML/Window/Event.hpp>
TitleState::TitleState(StateStack& stack, const Context& context)
: State(stack, context),
mWorldView(context.window->getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y),
mShowText(true)
{
	printf("\nCreated the Title!\n");
}
void TitleState::Draw() const
{
	// Get the window
	auto window = GetContext().window;
	
	window->clear();
	
	window->display();
}

bool TitleState::Update(sf::Time dt)
{
	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		// Request a new Push of State
		return false;
	}

	// handle event close button
	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return false;
	}

	return true;
}
