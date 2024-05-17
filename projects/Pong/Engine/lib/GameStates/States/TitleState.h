#pragma once
#include "GameStates/State.h"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	// sf::Sprite mBackgroundSprite;
	// sf::Text mTitleText;
	// sf::Text mText;
	//
	sf::View mWorldView;
	sf::FloatRect mWorldBounds;
	
	bool mShowText;
	sf::Time mTextEffectTime;
};