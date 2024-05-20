#include "States/PauseState.h"

#include "Utility.hpp"
#include "GUI/Button.h"

PauseState::PauseState(StateStack& stack, const Context& context)
: State(stack, context),
mLabel("", *context.fonts)
{
	sf::Vector2f windowSize(context.window->getSize());

	mLabel.SetText("PAUSED");
	mLabel.SetSize(50);
	CenterOrigin(mLabel.GetText());
	mLabel.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 80);

	// set up return button
	auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	returnButton->setPosition( windowSize.x/ 2.f, windowSize.y / 2.f + 80);
	returnButton->SetText("Resume");
	returnButton->SetToggle(true);
	returnButton->SetCallback([this]()
	{
		mIsPaused = false;
		RequestStackPop();
	});

	// set up quit button
	auto quitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	quitButton->setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 160);
	quitButton->SetText("Quit");
	quitButton->SetToggle(true);
	quitButton->SetCallback([this]()
	{
		mIsPaused = false;
		RequestStateClear();
		RequestStackPush(States::TITLE);
	});
	
	// pack up the container
	mButtonContainer.Pack(returnButton);
	mButtonContainer.Pack(quitButton);
}

void PauseState::Draw() const
{
	sf::RenderWindow& window = *GetContext().window;

	// Set the background shape
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 50));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	backgroundShape.setPosition(0, 0);

	window.draw(backgroundShape);
	
	window.draw(mLabel);
	window.draw(mButtonContainer);

	window.display();
}

bool PauseState::Update(sf::Time dt)
{
	return false;
}

bool PauseState::FixedUpdate(sf::Time fixedDt)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		printf("Closing window.");
		RequestStateClear();
		return false;
	}
	
	// handle the events for the container.
	mButtonContainer.HandleEvent(event);
	
	return true;
}
