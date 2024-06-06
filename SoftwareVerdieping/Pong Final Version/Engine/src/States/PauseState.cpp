#include "States/PauseState.h"

#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window),
mPauseLabel("PAUSED", *context.fonts),
mEscapeInstruction(std::make_shared<GUI::Label>("ESC: Unpause", *context.fonts)),
mBar(std::make_shared<GUI::Label>("|", *context.fonts)),
mExitInstruction(std::make_shared<GUI::Label>("BACKSPACE: Exit", *context.fonts))
{
	auto view = mWindow->getDefaultView();
	sf::Vector2f viewSize = view.getSize();

	// set the font for the label
	mPauseLabel.SetFont(*context.fonts, Fonts::DEFAULT_BOLD);

	// set size of labels
	mPauseLabel.SetSize(60);
	mEscapeInstruction->SetSize(20);
	mBar->SetSize(20);
	mExitInstruction->SetSize(20);

	// center origins
	CenterOrigin(mPauseLabel.GetText());
	CenterOrigin(mEscapeInstruction->GetText());
	CenterOrigin(mBar->GetText());
	CenterOrigin(mExitInstruction->GetText());

	// set positions
	mPauseLabel.setPosition(sf::Vector2f(viewSize.x / 2.f, 150));
	mEscapeInstruction->setPosition(viewSize.x / 2.f - 100.f, viewSize.y);
	mBar->setPosition(viewSize.x / 2.f, viewSize.y);
	mExitInstruction->setPosition(viewSize.x / 2.f + 120.f, viewSize.y);

	// pack the instruction
	mInstructions.Pack(mEscapeInstruction);
	mInstructions.Pack(mBar);
	mInstructions.Pack(mExitInstruction);

	// move the instructions upwards by 20 pixels
	mInstructions.setPosition(sf::Vector2f(0, -20));
}

void PauseState::Draw() const
{
	// Set the background shape
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(mWindow->getSize()));
	backgroundShape.setPosition(0, 0);

	mWindow->draw(backgroundShape);

	// draw out the label and container
	mWindow->draw(mPauseLabel);
	mWindow->draw(mInstructions);

	mWindow->display();
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
	if (event.type == sf::Event::Closed) {
		RequestStateClear();
		return true;
	}

	// handle incoming key events
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape && event.key.code != mLastKeyPressed) {
			mLastKeyPressed = event.key.code;

			RequestStackPop();
			mIsPaused = false;
		}

		if (event.key.code == sf::Keyboard::BackSpace) {
			RequestStateClear();
			RequestStackPush(States::TITLE);
			mIsPaused = false;

			return true;
		}
	}

	return false;
}
