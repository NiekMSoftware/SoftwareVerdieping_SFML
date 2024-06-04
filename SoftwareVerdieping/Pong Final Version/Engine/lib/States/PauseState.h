#pragma once
#include "State.hpp"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time deltaTime) override;
	bool FixedUpdate(sf::Time fixedDeltaTime) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	sf::RenderWindow* mWindow;
};
