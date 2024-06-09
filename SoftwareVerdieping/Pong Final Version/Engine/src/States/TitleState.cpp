#include "States/TitleState.h"

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window),
mWorldView(context.window->getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y),
mShowText(true)
{
	LoadResources(context);
}

void TitleState::LoadResources(const Context& context)
{
	// Load in the Text and Font
	sf::Font& font = context.fonts->get(Fonts::DEFAULT_FONT);
	mText.setFont(font);
	mText.setString("Press a key...");
	mText.setOutlineColor(sf::Color::Black);
	mText.setOutlineThickness(2.f);
	mText.setCharacterSize(32);

	// Set up the title text
	mTitleText.setFont(font);
	mTitleText.setString("Pong");
	mTitleText.setOutlineColor(sf::Color::Black);
	mTitleText.setOutlineThickness(2.f);
	mTitleText.setCharacterSize(48);

	// Set up the labels
	mPlayer1Instruction = std::make_shared<GUI::Label>("Player 1: W/S to move", *GetContext().fonts);
	mBar = std::make_shared<GUI::Label>("|", *GetContext().fonts);
	mPlayer2Instruction = std::make_shared<GUI::Label>("Player 2: Up/Down to move", *GetContext().fonts);

	// Set size of labels
	mPlayer1Instruction->SetSize(20);
	mBar->SetSize(30);
	mPlayer2Instruction->SetSize(20);

	// Center origins
	CenterOrigin(mPlayer1Instruction->GetText());
	CenterOrigin(mBar->GetText());
	CenterOrigin(mPlayer2Instruction->GetText());

	// Set position of labels
	mPlayer1Instruction->setPosition(sf::Vector2f(-140, 0));
	mBar->setPosition(0, 0);
	mPlayer2Instruction->setPosition(sf::Vector2f(160, 0));

	// Calculate the position to center the title text
	sf::FloatRect titleBounds = mTitleText.getLocalBounds();
	mTitleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.f);
	mTitleText.setPosition(mWorldBounds.left + mWorldBounds.width / 2.f, 100);

	// Calculate position to center main text
	sf::FloatRect textBounds = mText.getLocalBounds();
	mText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	mText.setPosition(mWorldBounds.left + mWorldBounds.width / 2.f, 280);

	// Pack up the labels
	mContainer.Pack(mPlayer1Instruction);
	mContainer.Pack(mBar);
	mContainer.Pack(mPlayer2Instruction);

	// Set position of container
	mContainer.setPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y - 20.f);
}

bool TitleState::Update(sf::Time dt)
{
	mTextTimer += dt;

	// A timer for blinking the mText var
	if (mTextTimer >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextTimer = sf::Time::Zero;
	}

	return false;
}

bool TitleState::FixedUpdate(sf::Time fixedDt)
{
	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		RequestStackPush(States::GAME);
		return false;
	}

	if (event.type == sf::Event::Closed)
	{
		RequestStateClear();
		return false;
	}

	return true;
}

void TitleState::Draw() const
{
	mWindow->clear();
	mWindow->draw(mTitleText);
	mWindow->draw(mContainer);

	// Show the mShowText once it is set to true.
	if (mShowText)
		mWindow->draw(mText);

	mWindow->display();
}