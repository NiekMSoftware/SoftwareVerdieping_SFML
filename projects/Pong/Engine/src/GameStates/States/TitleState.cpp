#include <GameStates/States/TitleState.h>
#include <SFML/Window/Event.hpp>

#include "ResourceIdentifiers.inl"
TitleState::TitleState(StateStack& stack, const Context& context)
: State(stack, context),
mWorldView(context.window->getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y),
mShowText(true)
{
	// Load in the resources
	LoadResources(context);
}

void TitleState::LoadResources(const Context& context)
{
	// Load in the texture of the background
	sf::Texture& texture = context.textures->Get(Textures::Title);
	const sf::IntRect textureRect(mWorldBounds);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setTextureRect(textureRect);
	texture.setRepeated(true);

	// Load in the Text and Font
	sf::Font& font = context.fonts->Get(Fonts::Default);
	mText.setFont(font);
	mText.setString("Press any Key...");
	mText.setOutlineColor(sf::Color::Black);
	mText.setOutlineThickness(2.f);
	mText.setCharacterSize(32);

	// Set up the title text
	mTitleText.setFont(font);
	mTitleText.setString("Pongseki Bibounce");
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

void TitleState::Draw() const
{
	// Get the window
	auto window = GetContext().window;
	
	window->clear();

	// draw out elements
	window->draw(mBackgroundSprite);
	window->draw(mTitleText);

	// Blink the mText variable
	if (mShowText)
		window->draw(mText);
	
	window->display();
}

bool TitleState::Update(sf::Time dt)
{
	mTextEffectTime += dt;

	// A timer for blinking the mText variable.
	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	
	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		RequestStackPush(States::Game);
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