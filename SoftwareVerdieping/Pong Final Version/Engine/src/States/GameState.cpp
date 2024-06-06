#include "States/GameState.h"

GameState::GameState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window),
mPlayer1(50, 300),
mPlayer2(740, 300),
mBall(400, 300)
{ }

void GameState::Draw() const {
	mWindow->clear(sf::Color(33, 44, 54));

	mWindow->draw(mPlayer1.getShape());
	mWindow->draw(mPlayer2.getShape());
	mWindow->draw(mBall.getShape());

	// Render this state only when the game isn't paused.
	if (!mIsPaused)
		mWindow->display();
}

bool GameState::Update(sf::Time dt) {
	// Stop updating the state if the game is paused.
	if (mIsPaused)
		return false;

	// once either players have 5 points, stop the game
	if (mPlayerOneScore >= 5 || mPlayerTwoScore >= 5) {
		RequestStackPop();
		RequestStackPush(States::TITLE);
	}

	return true;
}

bool GameState::FixedUpdate(sf::Time fixedDt) {
	// Stop updating the state if the game is paused.
	if (mIsPaused)
		return false;

	// player one moving up and down
	if (mPlayerOneUp) mPlayer1.moveUp();
	if (mPlayerOneDown) mPlayer1.moveDown();

	// player two moving up and down
	if (mPlayerTwoUp) mPlayer2.moveUp();
	if (mPlayerTwoDown) mPlayer2.moveDown();

	// update players
	mPlayer1.fixedUpdate();
	mPlayer2.fixedUpdate();

	handleBallCollision();

	// update ball
	mBall.fixedUpdate();

	return true;
}

bool GameState::HandleEvent(const sf::Event& event) {
	// Handle the window closing event
	if (event.type == sf::Event::Closed) {
		RequestStateClear();
		return true;
	}

	// Handle key presses
	if (event.type == sf::Event::KeyPressed) {
		HandlePlayerInput(event.key.code, true);

		// Handle pausing the game
		if (event.key.code == sf::Keyboard::Escape) {
			// set the paused flag to true
			mIsPaused = true;

			// Push in the pause state.
			RequestStackPush(States::PAUSE);

			return true;
		}
	} else if (event.type == sf::Event::KeyReleased) {
		HandlePlayerInput(event.key.code, false);
	}

	return false;
}

void GameState::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::W) {
		mPlayerOneUp = isPressed;
	}

	if (key == sf::Keyboard::S) {
		mPlayerOneDown = isPressed;
	}

	if (key == sf::Keyboard::Up) {
		mPlayerTwoUp = isPressed;
	}

	if (key == sf::Keyboard::Down) {
		mPlayerTwoDown = isPressed;
	}
}

void GameState::handleBallCollision()
{
	// Handle collision with paddles
	if (mBall.getShape().getGlobalBounds().intersects(mPlayer1.getShape().getGlobalBounds())) {
		mBall.reboundBatOrTop();
		mBall.fixedUpdate();

		// reset the ball if it gets stuck
		if (mBall.getShape().getGlobalBounds().intersects(mPlayer1.getShape().getGlobalBounds())) {
			mBall.reset(mPlayer1.getShape().getPosition().x + mPlayer1.getShape().getSize().x + mBall.getShape().getRadius(), mBall.getShape().getPosition().y);
		}
	}

	if (mBall.getShape().getGlobalBounds().intersects(mPlayer2.getShape().getGlobalBounds())) {
		mBall.reboundBatOrTop();
		mBall.fixedUpdate();

		// reset the ball if it gets stuck
		if (mBall.getShape().getGlobalBounds().intersects(mPlayer2.getShape().getGlobalBounds())) {
			mBall.reset(mPlayer2.getShape().getPosition().x - mBall.getShape().getRadius() * 2, mBall.getShape().getPosition().y);
		}
	}

	// Handle collision with top and bottom
	if (mBall.getShape().getPosition().y < 0 || mBall.getShape().getPosition().y + mBall.getShape().getRadius() * 2 > 600) {
		mBall.reboundSides();
	}

	// Handle scoring
	if (mBall.getShape().getPosition().x < 0) {
		mPlayerTwoScore++;
		mBall.reset(400, 300);
	}

	if (mBall.getShape().getPosition().x + mBall.getShape().getRadius() * 2 > 800) {
		mPlayerOneScore++;
		mBall.reset(400, 300);
	}
}
