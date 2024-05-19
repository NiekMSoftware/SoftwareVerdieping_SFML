#pragma once

#include "States/State.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context& context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool FixedUpdate(sf::Time fixedDt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	sf::Keyboard::Key mLastKeyPressed = sf::Keyboard::Unknown;
};

