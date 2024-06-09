#pragma once
#include "State.hpp"
#include "GUI/Container.hpp"
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
	sf::RenderWindow* mWindow; //!< Pointer to the window of the Context.

	sf::Text mTitleText;
	sf::Text mText;

	// Instruction labels
	std::shared_ptr<GUI::Label> mPlayer1Instruction;
	std::shared_ptr<GUI::Label> mBar;
	std::shared_ptr<GUI::Label> mPlayer2Instruction;
	GUI::Container mContainer;

	sf::View mWorldView;
	sf::FloatRect mWorldBounds;

	bool mShowText;
	sf::Time mTextTimer;
};
