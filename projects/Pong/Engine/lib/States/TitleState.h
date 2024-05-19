#pragma once

#include "States/State.hpp"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context& context);

	bool Update(sf::Time dt) override;
	bool FixedUpdate(sf::Time fixedDt) override;
	bool HandleEvent(const sf::Event& event) override;
	void Draw() const override;

private:
	void LoadResources(const Context& context);

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mTitleText;
	sf::Text mText;

	sf::View mWorldView;
	sf::FloatRect mWorldBounds;

	bool mShowText;
	sf::Time mTextTimer;
};
