#pragma once
#include "Paddle.h"
#include "State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Label.hpp"

class GameOver : public State
{
public:
	GameOver(StateStack& stack, const Context& context);

	void Draw() const override;
	bool Update(sf::Time deltaTime) override;
	bool FixedUpdate(sf::Time fixedDeltaTime) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	void InitializeLabels();

private:
	sf::RenderWindow* mWindow;

	// labels
	GUI::Label mGameOverText;

	std::shared_ptr<GUI::Label> mEscInstruction;
	std::shared_ptr<GUI::Label> mBar;
	std::shared_ptr<GUI::Label> mSpaceInstruction;

	GUI::Container mContainer;
};
