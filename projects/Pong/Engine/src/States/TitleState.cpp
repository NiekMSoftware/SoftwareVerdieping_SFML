#include "States/TitleState.h"

TitleState::TitleState(StateStack& stack, const Context& context)
: State(stack, context),
mWorldView(context.window->getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y),
mShowText(true)
{
	LoadResources(context);
}

void TitleState::LoadResources(const Context& context)
{
	// Load in the texture of the background
	sf::Texture& texture = context.textures->Get(Textures::DEFAULT);
	const sf::IntRect textureRect(mWorldBounds);
	mBackgroundSprite.setTexture(texture);
	mBackgroundSprite.setTextureRect(textureRect);
	texture.setRepeated(true);

	// Load in the Text and Font
	sf::Font& font = context.fonts->Get(Fonts::DEFAULT);
	mText.setFont(font);
	mText.setString("Press any Key...");
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
	
	return true;
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
	GetContext().window->clear();

	GetContext().window->draw(mBackgroundSprite);
	GetContext().window->draw(mTitleText);

	// Show the mShowText once it is set to true.
	if (mShowText)
		GetContext().window->draw(mText);
	
	GetContext().window->display();
}