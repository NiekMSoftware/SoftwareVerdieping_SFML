#include "Paddle.h"

Paddle::Paddle(float startX, float startY)
: mPosition(startX, startY),
mShape(sf::Vector2f(20, 60)),
paddleSpeed(5) {
	// set the position of the paddle
	mShape.setPosition(mPosition);
}

sf::RectangleShape Paddle::getShape() const {
	return mShape;
}

void Paddle::moveUp() {
	if (mPosition.y > 0) {
		mPosition.y -= paddleSpeed;
	}
}

void Paddle::moveDown() {
	if (mPosition.y + mShape.getSize().y < 600) {
		mPosition.y += paddleSpeed;
	}
}

void Paddle::fixedUpdate() {
	mShape.setPosition(mPosition);
}
