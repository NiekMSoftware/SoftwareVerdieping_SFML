#pragma once
#include "Ball.h"
#include "Paddle.h"
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
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void handleBallCollision();

private:
	sf::RenderWindow* mWindow;

	// set up pong objects
	Paddle mPlayer1;
	Paddle mPlayer2;
	Ball mBall;

	bool mPlayerOneUp = false;
	bool mPlayerOneDown = false;
	bool mPlayerTwoUp = false;
	bool mPlayerTwoDown = false;

	int mPlayerOneScore = 0;
	int mPlayerTwoScore = 0;
};
