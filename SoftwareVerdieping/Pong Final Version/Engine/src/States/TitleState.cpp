#include "States/TitleState.h"

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

	// Calculate the position to center the title text
	sf::FloatRect titleBounds = mTitleText.getLocalBounds();
	mTitleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.f);
	mTitleText.setPosition(mWorldBounds.left + mWorldBounds.width / 2.f, 100);

	// Calculate position to center main text
	sf::FloatRect textBounds = mText.getLocalBounds();
	mText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	mText.setPosition(mWorldBounds.left + mWorldBounds.width / 2.f, 280);
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

	// Show the mShowText once it is set to true.
	if (mShowText)
		mWindow->draw(mText);

	mWindow->display();
}