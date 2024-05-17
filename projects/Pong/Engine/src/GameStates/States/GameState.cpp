#include <GameStates/States/GameState.h>

GameState::GameState(StateStack& stack, const Context& context)
: State(stack, context)
{
	// Load any resources needed
}
void GameState::Draw() const
{
	// Get a pointer to the window
	sf::RenderWindow* window = GetContext().window;

	// Clear screen
	window->clear();

	// display screen only once mIsPaused is false
	if (!mIsPaused)
		window->display();
}

bool GameState::Update(sf::Time dt)
{
	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	// Close the game
	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return false;
	}

	// Handle Player Input
	HandleInput(event);
	return true;	
}

void GameState::HandleInput(const sf::Event& event)
{
	// TODO: Save the last pressed key to avoid an immediate pause once player presses ESC in the Title
	
	// Handle input of keys being pressed
	if (event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::Escape)
		{
			mIsPaused = true;
			// push in the pause state
		}
	}
}
