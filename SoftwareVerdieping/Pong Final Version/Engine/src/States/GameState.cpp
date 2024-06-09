#include "States/GameState.h"

#include "Utility.hpp"

GameState::GameState(StateStack& stack, const Context& context)
: State(stack, context),
mWindow(context.window),
mPlayer1(50, 300, context),
mPlayer2(740, 300, context),
mBall(400, 300, context),
mPlayerOneText(mPlayerOneScore, *context.fonts),
mPlayerTwoText(mPlayerTwoScore, *context.fonts),
mScoreToBeat(3)
{
	// set the texture of the ball
	mBall.setTexture(Textures::BIJOU);

	// set text to bold
	mPlayerOneText.SetFont(*context.fonts, Fonts::DEFAULT_BOLD);
	mPlayerTwoText.SetFont(*context.fonts, Fonts::DEFAULT_BOLD);

	// set size of text
	mPlayerOneText.SetSize(40);
	mPlayerTwoText.SetSize(40);

	// center origin of text
	CenterOrigin(mPlayerOneText.GetText());
	CenterOrigin(mPlayerTwoText.GetText());

	// set position of text
	mPlayerOneText.setPosition(50, 100);
	mPlayerTwoText.setPosition(740, 100);
}

void GameState::Draw() const {
	mWindow->clear(sf::Color(33, 44, 54));

	mWindow->draw(mPlayer1.getShape());
	mWindow->draw(mPlayer2.getShape());
	mWindow->draw(mBall.getShape());

	// draw out the labels
	mWindow->draw(mPlayerOneText);
	mWindow->draw(mPlayerTwoText);

	// Render this state only when the game isn't paused.
	if (!mIsPaused)
		mWindow->display();
}

bool GameState::Update(sf::Time dt) {
	// Stop updating the state if the game is paused.
	if (mIsPaused)
		return false;

	// end the game once either one of the players has got the required score
	if (mPlayerOneScore >= mScoreToBeat || mPlayerTwoScore >= mScoreToBeat) {
		RequestStackPop();
		RequestStackPush(States::GAME_OVER);
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
	mPlayer1.updateObject();
	mPlayer2.updateObject();

	handleBallCollision();

	// update ball
	mBall.updateObject();

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
		mBall.updateObject();
		if (mBall.getShape().getGlobalBounds().intersects(mPlayer1.getShape().getGlobalBounds())) {
			mBall.reset(mPlayer1.getShape().getPosition().x + mPlayer1.getShape().getSize().x + mBall.getShape().getSize().x, mBall.getShape().getPosition().y);
		}
	}

	if (mBall.getShape().getGlobalBounds().intersects(mPlayer2.getShape().getGlobalBounds())) {
		mBall.reboundBatOrTop();
		mBall.updateObject();
		if (mBall.getShape().getGlobalBounds().intersects(mPlayer2.getShape().getGlobalBounds())) {
			mBall.reset(mPlayer2.getShape().getPosition().x - mBall.getShape().getSize().x, mBall.getShape().getPosition().y);
		}
	}

	// Handle collision with top and bottom boundaries
	if (mBall.getShape().getPosition().y < 0 || mBall.getShape().getPosition().y + mBall.getShape().getSize().y > 600) {
		mBall.reboundSides();
	}

	// Handle scoring
	if (mBall.getShape().getPosition().x < 0) {
		mPlayerTwoScore++;
		mPlayerTwoText.SetText(mPlayerTwoScore);
		mBall.reset(400, 300);
	}

	if (mBall.getShape().getPosition().x + mBall.getShape().getSize().x > 800) {
		mPlayerOneScore++;
		mPlayerOneText.SetText(mPlayerOneScore);
		mBall.reset(400, 300);
	}
}
