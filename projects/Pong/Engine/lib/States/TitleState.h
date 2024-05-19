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
};
