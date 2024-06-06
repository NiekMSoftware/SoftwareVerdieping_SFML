#include "Ball.h"

Ball::Ball(float startX, float startY, const State::Context& context)
: GameObject(startX, startY, context),
xVelocity(2.f),
yVelocity(2.f),
maxVelocity(50.f)
{
	// initialise ball
	mShape.setSize(sf::Vector2f(20, 20));
	mShape.setPosition(mPosition);
}

void Ball::updateObject() {
	// add velocity to the ball's relative position
	mPosition.x += xVelocity;
	mPosition.y += yVelocity;

	// check for boundaries and correct velocity
	if (mPosition.y < 0) {
		mPosition.y = 0;
		yVelocity = -yVelocity;
	}

	if (mPosition.y + mShape.getSize().y > 600) {
		mPosition.y = 600 - mShape.getSize().y;
		yVelocity = -yVelocity;
	}

	// clamp the max velocity
	if (xVelocity > maxVelocity) xVelocity = maxVelocity;
	if (xVelocity < -maxVelocity) xVelocity = -maxVelocity;
	if (yVelocity > maxVelocity) yVelocity = maxVelocity;
	if (yVelocity < -maxVelocity) yVelocity = -maxVelocity;

	mShape.setPosition(mPosition);
}

void Ball::reboundSides()
{
	yVelocity = -yVelocity;
}

void Ball::reboundBatOrTop()
{
	xVelocity = -xVelocity;
	if (xVelocity < 0)
		xVelocity -= 0.6f;
	else
		xVelocity += 0.6f;
}

void Ball::reset(float startX, float startY)
{
	// reset the ball's position
	mPosition.x = startX;
	mPosition.y = startY;
	mShape.setPosition(mPosition);

	// reset velocity
	xVelocity = 2.f;
	yVelocity = 2.f;
}