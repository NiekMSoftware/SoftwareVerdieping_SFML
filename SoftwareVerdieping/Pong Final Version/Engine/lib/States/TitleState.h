#pragma once
#include "State.hpp"
#include "GUI/Label.hpp"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool FixedUpdate(sf::Time fixedDt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	void LoadResources(const Context& context);

private:
	sf::RenderWindow* mWindow; //!< Reference to the window of the Context.

	sf::Text mTitleText;
	sf::Text mText;

	sf::View mWorldView;
	sf::FloatRect mWorldBounds;

	bool mShowText;
	sf::Time mTextTimer;
};
