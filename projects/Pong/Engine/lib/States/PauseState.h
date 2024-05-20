#pragma once
#include "State.hpp"
#include "GUI/Container.h"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool FixedUpdate(sf::Time fixedDt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	sf::Text mPauseText;
	GUI::Container mContainer;
};
