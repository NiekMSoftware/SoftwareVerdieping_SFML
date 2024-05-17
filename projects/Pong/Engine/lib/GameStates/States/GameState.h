#pragma once

#include "GameStates/State.h"
#include "SFML/Graphics.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	void HandleInput(const sf::Event& event);
};
