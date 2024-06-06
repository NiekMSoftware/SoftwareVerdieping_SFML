#pragma once
#include "State.hpp"
#include "GUI/Container.hpp"
#include "GUI/Label.hpp"

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

	// key to check
	sf::Keyboard::Key mLastKeyPressed = sf::Keyboard::Unknown;

	// Labels
	GUI::Label mPauseLabel;

	std::shared_ptr<GUI::Label> mEscapeInstruction;
	std::shared_ptr<GUI::Label> mBar;
	std::shared_ptr<GUI::Label> mExitInstruction;

	GUI::Container mInstructions;
};
