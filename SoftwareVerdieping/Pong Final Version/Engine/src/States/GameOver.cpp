#include "States/GameOver.h"

#include "Utility.hpp"

GameOver::GameOver(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window),
mGameOverText("GAME OVER", *context.fonts),
mEscInstruction(std::make_shared<GUI::Label>("ESC: Exit", *context.fonts)),
mBar(std::make_shared<GUI::Label>("|", *context.fonts)),
mSpaceInstruction(std::make_shared<GUI::Label>("SPACE: Play again", *context.fonts))
{
	InitializeLabels();
}

void GameOver::InitializeLabels()
{
	// set up the text of the label
	mGameOverText.SetFont(*GetContext().fonts, Fonts::DEFAULT_BOLD);

	// set up the size of the labels
	mGameOverText.SetSize(50);
	mEscInstruction->SetSize(20);
	mBar->SetSize(20);
	mSpaceInstruction->SetSize(20);

	// center the origin of the labels
	CenterOrigin(mGameOverText.GetText());
	CenterOrigin(mEscInstruction->GetText());
	CenterOrigin(mBar->GetText());
	CenterOrigin(mSpaceInstruction->GetText());

	// set the position of the labels
	sf::Vector2f viewSize = mWindow->getDefaultView().getSize();
	mGameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 130);
	mEscInstruction->setPosition(viewSize.x / 2.f - 100.f, viewSize.y);
	mBar->setPosition(viewSize.x / 2.f, viewSize.y);
	mSpaceInstruction->setPosition(viewSize.x / 2.f + 140.f, viewSize.y);

	// pack up the labels
	mContainer.Pack(mEscInstruction);
	mContainer.Pack(mBar);
	mContainer.Pack(mSpaceInstruction);

	// set position of the container
	mContainer.setPosition(sf::Vector2f(0, -20));
}

void GameOver::Draw() const
{
	mWindow->clear();

	// draw out elements to the state
	mWindow->draw(mGameOverText);
	mWindow->draw(mContainer);

	mWindow->display();
}

bool GameOver::Update(sf::Time deltaTime)
{
	return false;
}

bool GameOver::FixedUpdate(sf::Time fixedDeltaTime)
{
	return false;
}

bool GameOver::HandleEvent(const sf::Event& event)
{
	// handle closing window event
	if (event.type == sf::Event::Closed)
	{
		// Clear out the states
		RequestStateClear();
		return true;
	}

	// Handle key press events
	if (event.type == sf::Event::KeyPressed)
	{
		// Handle ESC key being pressed.
		if (event.key.code == sf::Keyboard::Escape)
		{
			// Return to the title screen
			RequestStackPop();
			RequestStackPush(States::TITLE);
			return true;
		}

		// Handle space bar being pressed
		if (event.key.code == sf::Keyboard::Space)
		{
			// Play a new game of pong
			RequestStateClear();
			RequestStackPush(States::GAME);
			return true;
		}
	}

	return false;
}
