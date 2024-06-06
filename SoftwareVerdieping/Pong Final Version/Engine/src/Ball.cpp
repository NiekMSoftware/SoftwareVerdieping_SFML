#include "Ball.h"

Ball::Ball(float startX, float startY)
: xVelocity(1.3f),
yVelocity(1.3f),
maxVelocity(12.f) {
	// initialise position
	mPosition.x = startX;
	mPosition.y = startY;

	// initialise ball
	mShape.setRadius(10);
	mShape.setPosition(mPosition);
}

sf::CircleShape Ball::getShape() const {
	return mShape;
}

void Ball::fixedUpdate() {
	// add velocity to the ball's relative position
	mPosition.x += xVelocity;
	mPosition.y += yVelocity;

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
		xVelocity -= 0.3f;
	else
		xVelocity += 0.3f;
}

void Ball::reset(float startX, float startY)
{
	// reset the ball's position
	mPosition.x = startX;
	mPosition.y = startY;
	mShape.setPosition(mPosition);

	// reset velocity
	xVelocity = 1.3f;
	yVelocity = 1.3f;
}
