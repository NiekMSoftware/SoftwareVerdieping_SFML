#pragma once
#include "State.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time dt) override;
	bool FixedUpdate(sf::Time fixedDt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	sf::RenderWindow* mWindow;
};
