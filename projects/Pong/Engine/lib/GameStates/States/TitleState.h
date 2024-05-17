#pragma once

#include "GameStates/State.h"
#include <SFML/Graphics.hpp>

class TitleState : public State
{
public:
	TitleState(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	void LoadResources(const Context& context);

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mTitleText;
	sf::Text mText;
	
	sf::View mWorldView;
	sf::FloatRect mWorldBounds;
	
	bool mShowText;
	sf::Time mTextEffectTime;
};